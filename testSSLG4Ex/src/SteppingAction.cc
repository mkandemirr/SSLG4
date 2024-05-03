#include "SteppingAction.hh"
#include "SimOutputManager.hh"
#include "G4Step.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(SimOutputManager* simMan)
: mSimOutputManager(simMan)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4ParticleDefinition* particleDef = step->GetTrack()->GetDefinition();
  if (particleDef == G4OpticalPhoton::OpticalPhotonDefinition())
    return;
  
  // get volume of the current step
  G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
                            ->GetVolume();

  // check if we are in scoring volume
  if (volume->GetName() != "scntPV") return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  mSimOutputManager->AddEdep(edepStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


