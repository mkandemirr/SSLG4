#ifndef OrganicScintillatorFactory_h
#define OrganicScintillatorFactory_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "VMaterialFactory.hh"
#include <set>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class VMaterialBuilder;
class G4Material;

//singleton class
class OrganicScintillatorFactory: public VMaterialFactory
{
  public:
    static OrganicScintillatorFactory* GetInstance();

    //Singletons should not be cloneable.
    OrganicScintillatorFactory(const OrganicScintillatorFactory&) = delete;

    //Singletons should not be assignable.
    OrganicScintillatorFactory& operator = 
      (const OrganicScintillatorFactory&) = delete;
  
    void PrintProducts();
         
  protected:  
    OrganicScintillatorFactory();
    virtual ~OrganicScintillatorFactory();
      
    virtual G4Material* CreateMaterial(const G4String& name, 
                                       G4bool enableOpticalProperty
                                       ) override;
  
  private:
    G4String GetStringAsLowerCase(const G4String& str);
    
    G4double GetMDFromAD(const G4String& symb, G4double ad);
    
    G4Material* BuildScintillator();
    G4Material* BuildLoadedScintillator(const G4String& symb, 
                                        G4double loadedElMF
                                        ); 
    G4Material* BuildScntFromPredefinedMaterial();
    
    //Wbls
    G4Material* BuildPPO();
    G4Material* BuildLAB();
    G4Material* BuildLoadedWbLS(G4double labFraction,
                                G4double ppoFraction,
                                G4double waterFraction,
                                const G4String& loadMatName,
                                G4double loadedMatFraction   
                                );                     
    G4Material* BuildWbLS(G4double labFraction,
                          G4double ppoFraction,
                          G4double waterFraction
                          );  
     
  private:
    static OrganicScintillatorFactory* mInstance;  
    std::set<G4String> mProductsSet;
    G4String mProductName;
    G4String mMacrosDirectoryPath;
    G4String mMacroFilePath;
     
    std::vector< std::pair<G4String, G4double> > mElementFracVec;
    
    G4double mDensity;
    G4double mHydrogenAD;
    G4double mCarbonAD;
    G4bool bEnableMPT;
    G4Material* mMaterial;      
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif 
