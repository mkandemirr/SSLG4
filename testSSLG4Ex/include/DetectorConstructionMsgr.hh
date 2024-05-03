#ifndef DetectorConstructionMsgr_h
#define DetectorConstructionMsgr_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4UIcmdWithAString;
class G4UIcmdWithABool;
class DetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstructionMsgr: public G4UImessenger
{
  public:
    DetectorConstructionMsgr(DetectorConstruction*);
    ~DetectorConstructionMsgr() override;

    void SetNewValue(G4UIcommand*, G4String) override;

  private:
    DetectorConstruction*  mDet = nullptr;

    G4UIcmdWithAString* mScntTypeCmd;   
    G4UIcmdWithAString* mScntNameCmd;
    G4UIcmdWithABool*   mMPTCmd;    
};


#endif
