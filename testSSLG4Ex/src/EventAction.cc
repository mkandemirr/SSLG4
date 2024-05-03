#include "EventAction.hh"
#include "G4Event.hh"
#include "SimOutputManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(SimOutputManager* simMan) :
mSimOutputManager{simMan}
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* event)
{
  if (mSimOutputManager)
    mSimOutputManager->BeginOfEventAction(event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  if (mSimOutputManager)
    mSimOutputManager->EndOfEventAction(event);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

