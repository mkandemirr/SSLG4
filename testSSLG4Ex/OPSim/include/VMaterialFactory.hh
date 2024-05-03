#ifndef VMaterialFactory_h
#define VMaterialFactory_h 1

#include "globals.hh"
#include "G4Material.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class VMaterialFactory
{
  public:
    VMaterialFactory();
    virtual ~VMaterialFactory();
     
  public:     
    //This method internally invokes the factory method.                          
    G4Material* Get(const G4String& name, G4bool enableMPT = false);                            
  
  protected: 
    virtual G4Material* CreateMaterial(const G4String& name, 
                                       G4bool enableMPT
                                       ) = 0;               
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 
