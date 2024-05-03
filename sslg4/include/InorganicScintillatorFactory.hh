#ifndef InorganicScintillatorFactory_h
#define InorganicScintillatorFactory_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "VMaterialFactory.hh"
#include <set>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class VMaterialBuilder;
class G4Material;

//singleton class
class InorganicScintillatorFactory: public VMaterialFactory
{
  public:
    static InorganicScintillatorFactory* GetInstance();

    //Singletons should not be cloneable.
    InorganicScintillatorFactory(const InorganicScintillatorFactory&) = delete;

    //Singletons should not be assignable.
    InorganicScintillatorFactory& operator = 
      (const InorganicScintillatorFactory&) = delete;
    
    void PrintProducts();
       
  protected:  
    InorganicScintillatorFactory();
    virtual ~InorganicScintillatorFactory();
      
    virtual G4Material* CreateMaterial(const G4String& name, 
                                       G4bool enableOpticalProperty
                                       ) override;
  
  private:
    G4String GetStringAsLowerCase(const G4String& str);
    
    G4Material* BuildScntFromElementNumber();
    G4Material* BuildScntFromElementFraction();
    G4Material* BuildScntFromPredefinedMaterial();  
  private:
    static InorganicScintillatorFactory* mInstance;  
    std::set<G4String> mProductsSet;
    G4String mProductName;
    G4String mMacrosDirectoryPath;
    G4String mMacroFilePath;
    std::vector< std::pair<G4String, G4int> > mElementNumVec;
    std::vector< std::pair<G4String, G4double> > mElementFracVec;
    
    G4double mDensity;
    G4bool bEnableMPT; 
    G4Material* mMaterial;
      
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 
