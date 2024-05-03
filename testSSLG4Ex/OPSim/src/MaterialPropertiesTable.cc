#include "MaterialPropertiesTable.hh"
#include "MaterialPropertiesTableMessenger.hh"
#include "G4Material.hh"
#include "G4OpticalSurface.hh"
#include "FileReader.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialPropertiesTable::MaterialPropertiesTable(const G4String& name) : 
G4MaterialPropertiesTable(),
fMessenger{nullptr},
fName{name}
{
  fMessenger = new MaterialPropertiesTableMessenger(this); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialPropertiesTable::~MaterialPropertiesTable()
{
  if (fMessenger) delete fMessenger;    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MaterialPropertiesTable::AddPropertiesToMaterial(G4Material* mat)
{
  G4cout<<fName<<" ---G4MaterialPropertiesTable---"<<G4endl;
  G4MaterialPropertiesTable::DumpTable();
  
  mat->SetMaterialPropertiesTable(this);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MaterialPropertiesTable::AddPropertiesToSurface
(
  G4OpticalSurface* optSurface
)
{
  G4cout<<fName<<" ---G4MaterialPropertiesTable---"<<G4endl;
  G4MaterialPropertiesTable::DumpTable();
  
  optSurface->SetMaterialPropertiesTable(this);
  optSurface->DumpInfo();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MaterialPropertiesTable::AddProperty
(
  const G4String& key, 
  const G4String& filePath, 
  const G4String& photonUnit, //energy or wavelength unit.
  const G4String& valueUnit, 
  G4bool createNewKey, 
  G4bool spline
)

{
  
  G4double pUnit{0.}; //photonUnit
  G4double vUnit{0.}; //valueUnit
  
  CheckUnitsAndConvertToDimensionedDouble(photonUnit,valueUnit,pUnit,vUnit);
  
  std::vector< std::pair<double,double> > photonVector  
   = FileReader::GetInstance().ReadTwoColumnsIntoAVectorOfPairs(filePath); 
  
  //multiply with unit.
  for_each(photonVector.begin(), photonVector.end(),
  [pUnit,vUnit](auto &pair)
  {
    pair.first  = (pair.first)*pUnit;
    pair.second = (pair.second)*vUnit;   
  });
  
  //sort photon energies in ascending order
  if (G4UnitDefinition::GetCategory(photonUnit) == "Energy")
  { 
    std::sort(photonVector.begin(), photonVector.end());
  }else if (G4UnitDefinition::GetCategory(photonUnit) == "Length")
  { 
    //sort photoWavelength in descending order
    std::sort(photonVector.rbegin(), photonVector.rend());
   
    //convert wavelength to energy
    for_each(photonVector.begin(), photonVector.end(),
    [](auto &pair)
    {
      pair.first = (CLHEP::hbarc * CLHEP::twopi) / (pair.first);
      //energy = (CLHEP::hbarc * CLHEP::twopi) / (wavelength);
    });
   
  }
  
  //split the pairs
  std::vector<G4double> photonEnergies;
  std::vector<G4double> propertyValues;
  
  for (const auto &pair: photonVector)
  {
    photonEnergies.push_back(pair.first);
    propertyValues.push_back(pair.second);
  }
  
  photonVector.clear();
   
  //Pass the filled vectors to the method of G4MaterialPropertiesTable. 
  G4MaterialPropertiesTable::AddProperty(
    key, 
    photonEnergies, 
    propertyValues, 
    createNewKey, 
    spline
    );
  
  photonEnergies.clear();
  propertyValues.clear();          

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void MaterialPropertiesTable::AddProperty
(
  const G4String& key, 
  const G4String& filePath, 
  const G4String& photonUnit, //energy or wavelength unit.
  const G4String& valueUnit, 
  G4bool createNewKey, 
  G4bool spline,
  G4double propertyValue
)

{
  
  G4double pUnit{0.}; //photonUnit
  G4double vUnit{0.}; //valueUnit

  CheckUnitsAndConvertToDimensionedDouble(photonUnit,valueUnit,pUnit,vUnit);
    
  std::vector<G4double> photonVector
   =FileReader::GetInstance().ReadSingleColumnIntoAVector(filePath);
 
  //multiply with unit.
  for_each(photonVector.begin(), photonVector.end(),
  [pUnit](auto &el)
  {
    el = el*pUnit; 
  });
 
  //sort photon energies in ascending order
  if (G4UnitDefinition::GetCategory(photonUnit) == "Energy")
  { 
    std::sort(photonVector.begin(), photonVector.end());
  }
  
  //sort photoWavelength in descending order, then convert energy
  if (G4UnitDefinition::GetCategory(photonUnit) == "Length")
  { 
    std::sort(photonVector.rbegin(), photonVector.rend());
   
    for_each(photonVector.begin(), photonVector.end(),
    [](auto &el)
    {
      el = (CLHEP::hbarc * CLHEP::twopi) / (el);
      //wavelength = (CLHEP::hbarc * CLHEP::twopi) / (wavelength);
    });
   
  }
 
  std::vector<G4double> propertyValues; 
  propertyValues.insert(propertyValues.end(), 
                        photonVector.size(), 
                        propertyValue*vUnit
                        );   
  
  //Pass the filled vectors to the method of G4MaterialPropertiesTable. 
  G4MaterialPropertiesTable::AddProperty(
    key, 
    photonVector, 
    propertyValues, 
    createNewKey, 
    spline
    );
  
  photonVector.clear();
  propertyValues.clear();          

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//This function first checks the validity of the units and then converts the
//string units into the dimensionedDouble.
void MaterialPropertiesTable::CheckUnitsAndConvertToDimensionedDouble
(
  const G4String& photonUnit, 
  const G4String& valueUnit, 
  G4double& pUnit, 
  G4double& vUnit
)
{

  if (!G4UnitDefinition::IsUnitDefined(photonUnit))
  {
    G4ExceptionDescription ed;
    ed << "Undefined unit: <" <<photonUnit<< ">. Command failed.";
    G4Exception(
      "MaterialPropertiesTable::CheckUnitsAndConvertToDimensionedDouble()", 
      "matPropError0", 
      FatalException, 
      ed
      );
  }
  
  if (G4UnitDefinition::GetCategory(photonUnit) != "Energy")
  {    
    if (G4UnitDefinition::GetCategory(photonUnit) != "Length")
    {
      G4ExceptionDescription ed;
      ed << "Undefined energy or length unit: <" <<photonUnit<< 
        ">. Command failed.";
        
      G4Exception(
        "MaterialPropertiesTable::CheckUnitsAndConvertToDimensionedDouble()", 
        "matPropError1", 
        FatalException, 
        ed
        );
      
    }
    
  }

  if (!G4UnitDefinition::IsUnitDefined(valueUnit) && valueUnit != "unitless")
  {
    G4ExceptionDescription ed;
    ed << "Undefined property value unit: <" <<valueUnit<< 
      ">. Command failed.";
      
    G4Exception(
      "MaterialPropertiesTable::CheckUnitsAndConvertToDimensionedDouble()", 
      "matPropError2", FatalException, ed
      );
  }

  //convert the string photonUnit to the dimensionedDouble.
  G4String one   = "1";
  G4String r1    = one + " " + photonUnit;
  
  pUnit = G4UIcommand::ConvertToDimensionedDouble(r1);
   
  //convert the string valueUnit to the dimensionedDouble.
  if (valueUnit == "unitless")
  {
    vUnit = 1.;   
  }else
  {
    G4String r2 = one + " " + valueUnit;
    vUnit       = G4UIcommand::ConvertToDimensionedDouble(r2);  
  }

}
