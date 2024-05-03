#ifndef OpticalSurfaceMessenger_h
#define OpticalSurfaceMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class OpticalSurface;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class OpticalSurfaceMessenger : public G4UImessenger
{
  public:
    OpticalSurfaceMessenger(OpticalSurface*);
    ~OpticalSurfaceMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    OpticalSurface*     fOptSurface;
    G4UIdirectory*      fDirectory;
    G4UIcmdWithAString* fSurfaceTypeCmd;
    G4UIcmdWithAString* fSurfaceFinishCmd;
    G4UIcmdWithAString* fSurfaceModelCmd;
    G4UIcmdWithADouble* fSurfaceSigmaAlphaCmd;
    G4UIcmdWithADouble* fSurfacePolishCmd;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
