#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"
#include "SimOutputManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
  auto outputMan = new SimOutputManager();
  SetUserAction(new RunAction(outputMan));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
  auto  outputMan = new SimOutputManager();
  
  auto  runAction = new RunAction(outputMan);
  SetUserAction(runAction);  
  
  auto eventAction = new EventAction(outputMan);
  SetUserAction(eventAction);
  
  auto steppingAction = new SteppingAction(outputMan);
  SetUserAction(steppingAction);
  
  auto stackingAction = new StackingAction();
  SetUserAction(stackingAction);
  
  SetUserAction(new PrimaryGeneratorAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


