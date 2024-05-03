#ifndef VMaterialBuilder_h
#define VMaterialBuilder_h 1

#include "G4SystemOfUnits.hh"
#include "globals.hh"

class G4Material;
class MaterialPropertiesTable;
class G4NistManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class VMaterialBuilder{

  public:
    VMaterialBuilder(G4bool enableMPT = false); 
    virtual ~VMaterialBuilder();

    G4Material* GetProduct();
  
    MaterialPropertiesTable* GetMaterialPropertiesTable() const  
      {return pMPT; }
    
    G4bool IsMPTEnabled() {return bEnableMPT;}
    
  protected:
    virtual G4Material* Build() = 0;    
    
    G4NistManager* pNistManager;  
    G4bool bEnableMPT;
    MaterialPropertiesTable* pMPT;   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

