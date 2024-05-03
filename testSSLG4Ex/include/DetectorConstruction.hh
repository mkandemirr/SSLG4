#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class DetectorConstructionMsgr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct() override;
    
    //UI commands
    void SetScintillatorName(const G4String& name) { mScntName = name; }
    void SetScintillatorType(const G4String& type) { mScntType = type; }
    void SetMPTStatus(G4bool mptStatus) { mIsMPTOn = mptStatus; }
    
  private:
    G4LogicalVolume* BuildWorld();
    G4LogicalVolume* BuildScntillator();
    
    G4Material* CreateScntMaterial();
    
    G4VPhysicalVolume* PlaceScntillatorInWorld(G4LogicalVolume* scntLV,
                                               G4LogicalVolume* worldLV
                                               );
    
    G4VPhysicalVolume* PlaceWorld(G4LogicalVolume* worldLV);
    
  private:
    DetectorConstructionMsgr* mMessenger;
    G4String mScntName;
    G4String mScntType;
    G4bool mIsMPTOn; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
