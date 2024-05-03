#ifndef EJ426Builder_h
#define EJ426Builder_h 1

#include "VMaterialBuilder.hh"

class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EJ426Builder: public VMaterialBuilder{

  public:
    EJ426Builder(const G4String& name, 
                 const G4String& macroFilePath, 
                 G4bool enableMPT = false
                 );
                 
    virtual ~EJ426Builder();

    virtual G4Material* Build() override;
    
  private:
    G4String mProductName;
    G4String mMacroFilePath;
       
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

