#ifndef MaterialPropertiesTable_h
#define MaterialPropertiesTable_h 1

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "G4MaterialPropertiesTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Material;
class G4OpticalSurface;
class MaterialPropertiesTableMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MaterialPropertiesTable: public G4MaterialPropertiesTable {

  public:
    MaterialPropertiesTable(const G4String& name); 
    virtual ~MaterialPropertiesTable();
     
    //This function delegates FileReader class for reading 
    //energy/wavelength-value pairs from the specified file and filling the 
    //photonEnergies and propertyValues vectors.
    void AddProperty(const G4String& key, 
                     const G4String& filePath, 
                     const G4String& photonUnit, //energy or wavelength 
                     const G4String& valueUnit, 
                     G4bool createNewKey=false, 
                     G4bool spline=false
                    ); 
    
    //This function delegates FileReader class for only reading 
    //energy/wavelength values from the specified file (first column) and 
    //filling the photonEnergies vector. The vector, propertyValues, is filled 
    //with the propertyValue parameter.                    
    void AddProperty(const G4String& key, 
                     const G4String& filePath, 
                     const G4String& photonUnit, //energy or wavelength  
                     const G4String& valueUnit, 
                     G4bool createNewKey, 
                     G4bool spline,
                     G4double propertyValue
                     );
                          
    void AddPropertiesToMaterial(G4Material *mat);
    void AddPropertiesToSurface(G4OpticalSurface *optSurface);
    
    const G4String& GetName() {return fName;}
  
  private: //functions
    void CheckUnitsAndConvertToDimensionedDouble(
      const G4String& photonUnit, //energy or wavelength 
      const G4String& valueUnit, 
      G4double& pUnit, 
      G4double& vUnit
      );   
           
  private: //members
    MaterialPropertiesTableMessenger *fMessenger;   
    G4String fName;
                      
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


