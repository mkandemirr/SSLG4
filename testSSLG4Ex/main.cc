#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "G4RunManagerFactory.hh"

#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4OpticalPhysics.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  G4UIExecutive* ui = nullptr;
  if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv); }

  auto* runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  runManager->SetUserInitialization(new DetectorConstruction());

  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  physicsList->RegisterPhysics(opticalPhysics);
  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new ActionInitialization());

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( ! ui ) {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
