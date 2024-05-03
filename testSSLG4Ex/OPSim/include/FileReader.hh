#ifndef FileReader_h
#define FileReader_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "globals.hh"
#include <vector>

//Meyers' Singleton
class FileReader
{
  public:
    static FileReader& GetInstance();
    
    //Singletons should not be cloneable.
    FileReader(const FileReader&) = delete;
    //Singletons should not be assignable.
    FileReader& operator=(const FileReader&) = delete;
  
    std::vector<G4double> ReadSingleColumnIntoAVector(const G4String &filePath);
    
    std::vector<std::pair<double,double>> ReadTwoColumnsIntoAVectorOfPairs(
      const G4String &filePath
      ); 
                                                                                                 
  protected:
    FileReader();
    virtual ~FileReader();     
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 
