#ifndef SimOutputManagerMsgr_h
#define SimOutputManagerMsgr_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class G4UIcmdWithABool;
class SimOutputManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class SimOutputManagerMsgr: public G4UImessenger
{
  public:
    SimOutputManagerMsgr(SimOutputManager* som);
    ~SimOutputManagerMsgr() override;

    void SetNewValue(G4UIcommand*, G4String) override;

  private:
    SimOutputManager* mSimOutputManager;

    G4UIcmdWithABool* mPrintModeCmd;

};


#endif
