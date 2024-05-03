#include "DetectorConstruction.hh"
#include "DetectorConstructionMsgr.hh"
#include "ScintillatorBuilder.hh"
#include "MaterialPropertiesTable.hh"
#include "OrganicScintillatorFactory.hh"
#include "InorganicScintillatorFactory.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UImanager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

DetectorConstruction::DetectorConstruction():
G4VUserDetectorConstruction(),
mMessenger{nullptr},
mIsMPTOn{true}
{
  mMessenger = new DetectorConstructionMsgr(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

DetectorConstruction::~DetectorConstruction()
{
  delete mMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4LogicalVolume* scntLV  = BuildScntillator();
  G4LogicalVolume* worldLV = BuildWorld();
    
  PlaceScntillatorInWorld(scntLV, worldLV);
  
  G4cout<<*(G4Material::GetMaterialTable())<<G4endl;
  
  return PlaceWorld(worldLV);
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::BuildScntillator()
{
  G4double scntSizeX = 50*cm;
  G4double scntSizeY = 50*cm;
  G4double scntSizeZ = 50*cm;
  
  auto scntBox = new G4Box("ScntBox", 
                           scntSizeX*0.5, 
                           scntSizeY*0.5, 
                           scntSizeZ*0.5
                           );
                           
  G4Material* scntMat{nullptr};
  if (mScntType == "organic")
  {
    scntMat = OrganicScintillatorFactory::GetInstance()->
              Get(mScntName, mIsMPTOn);
    //OrganicScintillatorFactory::GetInstance()->PrintProducts();                         
  }else if (mScntType == "inorganic")
  {
    scntMat = InorganicScintillatorFactory::GetInstance()->
              Get(mScntName, mIsMPTOn);
    //OrganicScintillatorFactory::GetInstance()->PrintProducts(); 
  }  
          
  if (scntMat->GetMaterialPropertiesTable())
    scntMat->GetMaterialPropertiesTable()->DumpTable(); 
       
  return new G4LogicalVolume(scntBox, scntMat, "ScntLV");  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* DetectorConstruction::CreateScntMaterial()
{
  //Example scintillator
  G4NistManager* nistMan = G4NistManager::Instance();
  G4Material *scntMat = new G4Material("ej-200", 1.023*g/cm3, 2);
  scntMat->AddElement(nistMan->FindOrBuildElement("H"), 8.47*perCent);
  scntMat->AddElement(nistMan->FindOrBuildElement("C"), 91.45*perCent);  

  return scntMat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::BuildWorld()
{
  G4NistManager* nistMan = G4NistManager::Instance();
  G4Material* worldMat   = nistMan->FindOrBuildMaterial("G4_AIR");

  G4double worldSizeX = 100*cm;
  G4double worldSizeY = 100*cm;
  G4double worldSizeZ = 100*cm;
  auto worldBox = new G4Box("world", 
                            worldSizeX*0.5, 
                            worldSizeY*0.5, 
                            worldSizeZ*0.5
                            );
  
  auto worldLV  = new G4LogicalVolume(worldBox, worldMat,"WorldLV");  
  
  return worldLV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::PlaceScntillatorInWorld
(
  G4LogicalVolume* scntLV,
  G4LogicalVolume* worldLV
)
{                                                                             
  auto scntPV = new G4PVPlacement(nullptr,  // no rotation
                                  G4ThreeVector(), // at (0,0,0)
                                  scntLV,     // its logical volume
                                  "scntPV",   // its name
                                  worldLV,    // its mother  volume
                                  false,      // no boolean operations
                                  0,          // copy number
                                  true);      // checking overlaps
  return scntPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::PlaceWorld(G4LogicalVolume* worldLV)
{                                                                            
  auto worldPV = new G4PVPlacement(nullptr,         // no rotation
                                  G4ThreeVector(),  // at (0,0,0)
                                  worldLV,          // its logical volume
                                  "WorldPV",        // its name
                                  nullptr,          // its mother  volume
                                  false,            // no boolean operations
                                  0,                // copy number
                                  true);            // checking overlaps
  return worldPV;
}

