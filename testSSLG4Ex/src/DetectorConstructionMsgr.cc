#include "DetectorConstructionMsgr.hh"
#include "DetectorConstruction.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstructionMsgr::DetectorConstructionMsgr
(
  DetectorConstruction* det
)
 : mDet(det),
 mScntTypeCmd{nullptr},
 mScntNameCmd{nullptr}
{
  G4String commandDirectory = "/ssl/";
 
  //-------Command 1----------
  G4String commandName  = "type";
  G4String commandPath  = commandDirectory + commandName;
  G4String usage        = "[usage] "+ commandPath + " type";
  
 	mScntTypeCmd = new G4UIcmdWithAString(commandPath, this);
  mScntTypeCmd->SetGuidance(usage);
  mScntTypeCmd->SetCandidates("organic inorganic");
  mScntTypeCmd->AvailableForStates(G4State_PreInit, G4State_Init);
  mScntTypeCmd->SetToBeBroadcasted(false);
  
  //-------Command 2----------
  commandName ="name";
  commandPath = commandDirectory+commandName;
  usage       = "[usage] "+ commandPath + " name";
  
  mScntNameCmd = new G4UIcmdWithAString(commandPath, this);
  mScntNameCmd->SetGuidance(usage);
  mScntNameCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mScntNameCmd->SetToBeBroadcasted(false);
  
  //-------Command 2----------
  commandName ="enableMPT";
  commandPath = commandDirectory+commandName;
  usage       = "[usage] "+ commandPath + " enableMPT";
  
  mMPTCmd = new G4UIcmdWithABool(commandPath, this);
  mMPTCmd->SetGuidance(usage);
  mMPTCmd->AvailableForStates(G4State_PreInit,G4State_Init);
  mMPTCmd->SetToBeBroadcasted(false);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstructionMsgr::~DetectorConstructionMsgr()
{
  delete mScntTypeCmd;
  delete mScntNameCmd;
  delete mMPTCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstructionMsgr::SetNewValue
(
  G4UIcommand* command, 
  G4String newValue
)
{
  if( command == mScntTypeCmd )
  { 
    mDet->SetScintillatorType(newValue);
  }else if (command == mScntNameCmd)
  {
    mDet->SetScintillatorName(newValue);
  }else if (command == mMPTCmd)
  {
    mDet->SetMPTStatus(mMPTCmd->GetNewBoolValue(newValue));
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

