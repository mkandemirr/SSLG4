#include "FileReader.hh"
#include <fstream>
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FileReader::FileReader()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FileReader::~FileReader()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//Meyers' Singleton
//With C++11, static variables with block scope have an additional guarantee; 
//they will be initialized in a thread-safe way.
FileReader& FileReader::GetInstance()
{
  static FileReader instance;
  return instance; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<G4double> FileReader::ReadSingleColumnIntoAVector
(
  const G4String &filePath
) 
{
  G4String line;
  G4double column1; //energy or wavelength
  std::vector<G4double> vect;
  
  std::ifstream myfile (filePath.c_str());

  if (myfile.is_open())
  {
  
    while (getline (myfile,line))
    {
    
      std::istringstream iss(line);
       
      if ( (iss >> column1 ) ) 
       {       
         vect.push_back(column1);
       } 
               
    }
        
    myfile.close();
  }

  else 
  {
    G4ExceptionDescription ed;
    ed << "Unable to open file: "<<filePath;
    G4Exception("FileReader::ReadSingleColumnIntoAVector()", 
                "FileReaderErr1", 
                FatalException, 
                ed
                );  
  } 
  
  return vect;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector< std::pair<double,double> > FileReader::ReadTwoColumnsIntoAVectorOfPairs
(
  const G4String &filePath
) 
{
  G4String line;
  
  G4double column1; //energy or wavelength
  G4double column2; //propertyValue
  
  std::vector<std::pair<double,double> > vect;   
  
  std::ifstream myfile (filePath.c_str() );


  if (myfile.is_open())
  {
  
    while (getline (myfile,line))
    {
      std::istringstream iss(line);
       
      //line with only two columns will be readed. otherwise skipped   
      if ( (iss >> column1 >> column2 ) ) 
      {     
        vect.push_back( std::make_pair(column1,column2) );      
      }
         
    }    
       
    myfile.close();
  }else 
  { 
    G4ExceptionDescription ed;
    ed << "Unable to open file: "<<filePath;
    G4Exception("FileReader::ReadTwoColumnsIntoAVectorOfPairs()", 
                "FileReaderErr2", 
                FatalException, 
                ed
                );  
  } 
  
  return vect;

}
