#include "MaterialPropertiesTableMessenger.hh"
#include "MaterialPropertiesTable.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UnitsTable.hh" //for G4UnitDefinition
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialPropertiesTableMessenger::MaterialPropertiesTableMessenger
(
  MaterialPropertiesTable* mpt 
)
:G4UImessenger(), 
fMPT{mpt}, 
fDirectory1{nullptr}, 
fDirectory2{nullptr},
fAddPropertyCmd{nullptr},
fAddConstPropertyCmd{nullptr}
{  
  G4String rootDirectory     = "/mpt/"; 
  G4String commandDirectory  = "/mpt/"+fMPT->GetName()+"/";
  
  if(!fDirectory1)
  {
    fDirectory1 = new G4UIdirectory(rootDirectory);
    fDirectory1->SetGuidance(
      "Commands for objects of MaterialPropertiesTable class."
      );  
  }
  
  if(!fDirectory2)
  {
    fDirectory2 = new G4UIdirectory(commandDirectory);
  }
  
  //-------------Command 1---------------------------------
  G4String commandName  = "addProperty";
  G4String commandPath  = commandDirectory+commandName;
  G4String usage = "[usage] "+ commandPath + 
    " key path energyOrLengthUnit valueUnit createNewKey spline  propertyValue";
  
  fAddPropertyCmd = new G4UIcommand(commandPath,this,false);
  fAddPropertyCmd->SetGuidance("Add an energy-dependent property to the table");
  fAddPropertyCmd->SetGuidance(usage);
  fAddPropertyCmd->AvailableForStates(G4State_PreInit, G4State_Init);
  
  G4UIparameter* para = nullptr;
  
  //Add parameters to the command1.  
  para = new G4UIparameter("key",'s',false);
  fAddPropertyCmd->SetParameter(para);
  para = new G4UIparameter("path",'s',false);
  fAddPropertyCmd->SetParameter(para);
  para = new G4UIparameter("energyOrWavelengthUnit",'s',false);
  fAddPropertyCmd->SetParameter(para);
  para = new G4UIparameter("valueUnit",'s',false);
  para->SetGuidance("if the value is unitless, set it to unitless.");
  fAddPropertyCmd->SetParameter(para);
  para = new G4UIparameter("createNewKey",'b',true); //double or boolean
  fAddPropertyCmd->SetParameter(para);
  para = new G4UIparameter("spline",'b',true);
  fAddPropertyCmd->SetParameter(para);
  para = new G4UIparameter("propertyValue",'d',true);
  fAddPropertyCmd->SetParameter(para);
  
  
  //---------Command 2-------------------------------------
  commandName = "addConstProperty";
  commandPath = commandDirectory+commandName;
  usage       = "[usage] "+ commandPath + " key value unit";
  
  fAddConstPropertyCmd = new G4UIcommand(commandPath,this,false);
  fAddConstPropertyCmd->SetGuidance("Add a const property to the table");
  fAddConstPropertyCmd->SetGuidance(usage);
  fAddConstPropertyCmd->AvailableForStates(G4State_PreInit, G4State_Init);
   
  //Add parameters to the command2.
  para = new G4UIparameter("key",'s',false);
  fAddConstPropertyCmd->SetParameter(para);
  para = new G4UIparameter("properyValue",'d',false);
  fAddConstPropertyCmd->SetParameter(para);
  para = new G4UIparameter("unit",'s',true);
  fAddConstPropertyCmd->SetParameter(para);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MaterialPropertiesTableMessenger::~MaterialPropertiesTableMessenger()
{
   if(fDirectory1) delete fDirectory1;
   if(fDirectory2) delete fDirectory2;
   
   delete fAddPropertyCmd; 
   delete fAddConstPropertyCmd;      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Tokenizer.hh"
void MaterialPropertiesTableMessenger::SetNewValue
(
  G4UIcommand* command, 
  G4String newValue
)
{

  if ( command==fAddPropertyCmd )
  {
    G4Tokenizer next(newValue);
    G4String key           = next();
    G4String path          = next();
    G4String energyUnit    = next();
    G4String valueUnit     = next();
    G4String createNewKey  = next();
    G4String spline        = next();
    G4String propertyValue = next();

    if (createNewKey.empty())
    {
      fMPT->AddProperty(key,path,energyUnit,valueUnit);
      
    }else if (spline.empty()){
      fMPT->AddProperty(key,
                        path,
                        energyUnit,
                        valueUnit,
                        StoB(createNewKey)
                        );
      
    }else if (propertyValue.empty()){
      fMPT->AddProperty(key,
                        path,
                        energyUnit,
                        valueUnit,
                        StoB(createNewKey),
                        StoB(spline)
                        );
    }else{
      fMPT->AddProperty(key,
                        path,
                        energyUnit,
                        valueUnit,
                        StoB(createNewKey),
                        StoB(spline),
                        StoD(propertyValue)
                        );
    }


  }
  else if (command==fAddConstPropertyCmd){ 
    G4Tokenizer next(newValue);
    G4String key    = next();
    G4String value  = next();
    G4String unit   = next();
 
    //Define new units. They will be added to the units table.
    const G4double scntYield1  = 1./MeV;
    const G4double scntYield2  = 1./keV;
    const G4double scntYield3  = 1./GeV;
    
    new G4UnitDefinition("ScntYield1", "1/MeV", "1/Energy", scntYield1);
    new G4UnitDefinition("ScntYield2", "1/keV", "1/Energy", scntYield2);
    new G4UnitDefinition("ScntYield3", "1/GeV", "1/Energy", scntYield3);

    if ( unit.empty() )
    {
      fMPT->AddConstProperty( key,StoD(value) );
    }else if ( !G4UnitDefinition::IsUnitDefined(unit) ){ 
      G4ExceptionDescription ed;
      ed << "Undefined unit: <" <<unit<< ">. Command failed.";
      G4Exception("MaterialPropertiesTableMessenger::SetNewValue()", 
      "parameter3Error", FatalException, ed
      );
         
    }else{
      G4String r = value + " " + unit;
      G4double dimensionedDouble = fAddConstPropertyCmd->
                                    ConvertToDimensionedDouble(r);
      
      fMPT->AddConstProperty(key,dimensionedDouble); 

    }

  }
   
}

