#include "SimOutputManagerMsgr.hh"
#include "SimOutputManager.hh"
#include "G4UIcmdWithABool.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimOutputManagerMsgr::SimOutputManagerMsgr(SimOutputManager* som)
 : mSimOutputManager{som},
 mPrintModeCmd{nullptr}
{
  G4String commandDirectory = "/simOutput/";
 
  //-------Command 1----------
  G4String commandName  = "enablePrintMode";
  G4String commandPath  = commandDirectory + commandName;
  G4String usage        = "[usage] "+ commandPath + " enablePrintMode";
  
 
 	mPrintModeCmd = new G4UIcmdWithABool(commandPath, this);
  mPrintModeCmd->SetGuidance(usage);
  mPrintModeCmd->AvailableForStates(G4State_PreInit, G4State_Init);
  mPrintModeCmd->SetToBeBroadcasted(false);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimOutputManagerMsgr::~SimOutputManagerMsgr()
{
  delete mPrintModeCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManagerMsgr::SetNewValue
(
  G4UIcommand* command, 
  G4String newValue
)
{
  if( command == mPrintModeCmd )
  { 
    mSimOutputManager->SetPrintMode(mPrintModeCmd->GetNewBoolValue( newValue ));
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

