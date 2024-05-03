#include "OpticalSurface.hh"
#include "OpticalSurfaceMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpticalSurface::OpticalSurface(const G4String &name, 
                               G4OpticalSurfaceModel model, 
                               G4OpticalSurfaceFinish finish, 
                               G4SurfaceType type, 
                               G4double value
                               ):
G4OpticalSurface(name, model, finish, type, value),
fMessenger{nullptr},
fName{name}                                                                          
{  
  fMessenger = new OpticalSurfaceMessenger(this);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpticalSurface::~OpticalSurface()
{
  G4cout<<"OpticalSurface"<<this->GetName()<<" deleted.."<<G4endl;
  if(fMessenger) delete fMessenger;
}

