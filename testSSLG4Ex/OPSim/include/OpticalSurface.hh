#ifndef OpticalSurface_H
#define OpticalSurface_H 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"

class OpticalSurfaceMessenger;

class OpticalSurface: public G4OpticalSurface 
{
  public:
    OpticalSurface(const G4String& name, 
                   G4OpticalSurfaceModel model   = glisur,
                   G4OpticalSurfaceFinish finish = polished,
                   G4SurfaceType type            = dielectric_dielectric,
                   G4double value                = 1.0
                  );
   virtual ~OpticalSurface();
                                              
  private:
    OpticalSurfaceMessenger* fMessenger; 
    G4String fName; 

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
