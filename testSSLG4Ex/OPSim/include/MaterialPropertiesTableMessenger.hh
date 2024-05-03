#ifndef MaterialPropertiesTableMessenger_h
#define MaterialPropertiesTableMessenger_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "G4UImessenger.hh"

class MaterialPropertiesTable;
class G4UIdirectory;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MaterialPropertiesTableMessenger: public G4UImessenger
{
  public:
    MaterialPropertiesTableMessenger(MaterialPropertiesTable* helper );
    virtual ~MaterialPropertiesTableMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    MaterialPropertiesTable  *fMPT;
    G4UIdirectory            *fDirectory1;
    G4UIdirectory            *fDirectory2;
    G4UIcommand              *fAddPropertyCmd;
    G4UIcommand              *fAddConstPropertyCmd;
                       
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
