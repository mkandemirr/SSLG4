
#ifndef ScintillatorBuilder_h
#define ScintillatorBuilder_h 1

#include "VMaterialBuilder.hh"

class G4Material;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ScintillatorBuilder: public VMaterialBuilder{
  private:
    
    using ElementFracVec = std::vector< std::pair<G4String, G4double> >;
    using ElementNumVec  = std::vector< std::pair<G4String, G4int> >;
     
  public: 
    //Creates material from element fractions                   
    ScintillatorBuilder(const G4String& name,                                       
                        const G4String& macroFilePath,
                        G4double density,
                        ElementFracVec elFracVec,
                        G4bool enableMPT
                       );
    
    //Creates material from element numbers
    ScintillatorBuilder(const G4String& name,                                       
                        const G4String& macroFilePath,
                        G4double density,
                        ElementNumVec elNumVec,
                        G4bool enableMPT
                       ); 
    
    //Gets the material and add MPT.                             
    ScintillatorBuilder(const G4String& name,                                       
                        const G4String& macroFilePath,
                        G4Material* mat,
                        G4bool enableMPT = true
                       );                                                                             
                              
    virtual ~ScintillatorBuilder();
    
    
  protected:
    virtual G4Material* Build() override;
  
  private:
    void DefineMPTUICommands(); //MPT = MaterialPropertiesTable
    G4Material* BuildScntFromElementFractions();
    G4Material* BuildScntFromElementNumbers();
  
  private:
    G4String mName;
    G4String mMacroFilePath;
    G4double mDensity;
    G4Material *mMaterial; 
    ElementFracVec mElementFracVec;
    ElementNumVec mElementNumVec;   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

