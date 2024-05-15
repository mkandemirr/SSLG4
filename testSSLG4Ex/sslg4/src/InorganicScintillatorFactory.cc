#include "InorganicScintillatorFactory.hh"
#include "ScintillatorBuilder.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

InorganicScintillatorFactory* InorganicScintillatorFactory::mInstance = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

InorganicScintillatorFactory::InorganicScintillatorFactory():
VMaterialFactory(),
mDensity{0.},
bEnableMPT{false},
mMaterial{nullptr}
{
  mMacrosDirectoryPath = "sslg4/macros/iscnt/"; //relative to CMAKE_BINARY_DIR
  
  //Available products in the factory. 
  
  // https://www.advatech-uk.co.uk/
  mProductsSet.insert("isc-1000"); //BaF2
  mProductsSet.insert("isc-1001"); //CdWO4
  
  //https://github.com/saraheno/DualTestBeam (rIndex and absLength) and
  // https://luxiumsolutions.com/
  mProductsSet.insert("isc-2000"); //BGO
  
  // https://luxiumsolutions.com/
  mProductsSet.insert("isc-2001"); //CsINa
  mProductsSet.insert("isc-2002"); //CsITI
  mProductsSet.insert("isc-2003"); //LYSOCe
  mProductsSet.insert("isc-2004"); //NaITI
  
  //HEP Materials, noble gas scintillators
  
  // https://github.com/hanswenzel/CaTS
  mProductsSet.insert("isc-3000"); //LAr
  
  //https://github.com/Geant4/geant4/tree/master/examples/advanced/underground_physics
  mProductsSet.insert("isc-3001"); //LXe
  
  //https://github.com/saraheno/DualTestBeam 
  mProductsSet.insert("isc-3002"); //PbWO4 
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

InorganicScintillatorFactory::~InorganicScintillatorFactory()
{	 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* InorganicScintillatorFactory::CreateMaterial
(
  const G4String& name, 
  G4bool enableMPT
)
{
  G4Material* mat = G4NistManager::Instance()->FindOrBuildMaterial(name);
  if (mat) return mat;
  
  mProductName   = GetStringAsLowerCase(name);
  mMacroFilePath = mMacrosDirectoryPath + mProductName + ".mac";
  bEnableMPT     = enableMPT;
  
  if (mProductsSet.find(name) == mProductsSet.end()) //not found
    return nullptr; 
  
  if (name == "isc-2004")
  {
    mDensity = 3.67*g/cm3;
    mElementFracVec = { {"Na",0.152}, {"I",0.838}, {"Tl",0.010} };
    return BuildScntFromElementFraction();
  }else if (name == "isc-2002")
  {
    mDensity = 4.51*g/cm3;
    mElementFracVec = { {"Cs",0.511}, {"I",0.488}, {"Tl",7.86e-04} };
    return BuildScntFromElementFraction();
  }else if (name == "isc-2001")
  {    
    mDensity = 4.51*g/cm3;
    mElementFracVec = { {"Cs",0.511}, {"I",0.488}, {"Na",1e-04} };
    return BuildScntFromElementFraction();
  }else if (name == "isc-2000")
  {
    mDensity = 7.13*g/cm3;
    mElementNumVec = { {"Bi",4}, {"Ge",3}, {"O",12} };
    return BuildScntFromElementNumber();      
  }else if (name == "isc-2003")
  {    
    mDensity = 7.10*g/cm3;
    mElementFracVec = { {"Lu",0.713838658203075}, {"Y",0.040302477781781}, 
                        {"Si",0.063721807284236}, {"O",0.181501252152072}, 
                        {"Ce",0.000635804578835201 }  };
    return BuildScntFromElementFraction();
  }else if ( name == "isc-1000")
  {
    mMaterial = G4NistManager::Instance()->
                FindOrBuildMaterial("G4_BARIUM_FLUORIDE");
    return BuildScntFromPredefinedMaterial();
  }else if ( name == "isc-1001")
  {
    mMaterial = G4NistManager::Instance()->
                FindOrBuildMaterial("G4_CADMIUM_TUNGSTATE");
    return BuildScntFromPredefinedMaterial();
  }else if ( name == "isc-3000")
  {
    mMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_lAr");
    return BuildScntFromPredefinedMaterial();
  }else if ( name == "isc-3002")
  {
    mMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_PbWO4");
    return BuildScntFromPredefinedMaterial();
  }else if ( name == "isc-3001")
  {
    mMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_lXe");
    return BuildScntFromPredefinedMaterial();
  }
  else
  {
    return nullptr;
  }
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

InorganicScintillatorFactory* InorganicScintillatorFactory::GetInstance()
{
  static InorganicScintillatorFactory instance;
  
  if (mInstance == nullptr)
  {
    mInstance = &instance;
  }
  return mInstance;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4String InorganicScintillatorFactory::GetStringAsLowerCase
(
  const G4String& str
)
{
  G4String temp = str;
  transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
  return temp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* InorganicScintillatorFactory::BuildScntFromElementFraction()
{
  ScintillatorBuilder builder(mProductName, 
                              mMacroFilePath,
                              mDensity,
                              mElementFracVec,
                              bEnableMPT
                              ); 
  mElementFracVec.clear();                                 
  return builder.GetProduct();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* InorganicScintillatorFactory::BuildScntFromElementNumber()
{
  ScintillatorBuilder builder(mProductName, 
                              mMacroFilePath,
                              mDensity,
                              mElementNumVec,
                              bEnableMPT
                              );
  mElementNumVec.clear();                                   
  return builder.GetProduct();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* InorganicScintillatorFactory::BuildScntFromPredefinedMaterial()
{
  ScintillatorBuilder builder(mProductName, 
                              mMacroFilePath,
                              mMaterial,
                              bEnableMPT
                              );                                                            
  return builder.GetProduct(); 
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void InorganicScintillatorFactory::PrintProducts()
{
  G4cout<<"----------InorganicScintillatorFactory products ----------"<<G4endl;
  for (auto product: mProductsSet)
  {
    G4cout<<product<<G4endl;
  }
}

