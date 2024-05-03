//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "StackingAction.hh"
#include "G4OpticalPhoton.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::StackingAction() : 
G4UserStackingAction(),
mEmittedScntPhotonNum(0),
mEmittedCerenkovPhotonNum(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::~StackingAction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack
(
  const G4Track* aTrack
)
{
  if (aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  {  
    if (aTrack->GetParentID() > 0) // particle is secondary
    {
      //G4cout<<"SEMELE: "<<aTrack->GetKineticEnergy()<<G4endl; 
      //G4cout<<"SEMELE: "<<aTrack->GetGlobalTime()<<G4endl;  
      if (aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
        ++mEmittedScntPhotonNum;
      else if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")
        ++mEmittedCerenkovPhotonNum;
     
      G4double time       = aTrack->GetGlobalTime();
      G4double energy     = aTrack->GetKineticEnergy();
      G4double wavelength = (CLHEP::hbarc * CLHEP::twopi)/energy;
      //energy = (CLHEP::hbarc * CLHEP::twopi) / (wavelength); 
      
      mOPTimeVec.push_back(time); 
      mOPEnergyVec.push_back(energy);
      mOPWavelengthVec.push_back(wavelength);  
    }
  }
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingAction::NewStage()
{
   //G4cout << "Number of Scintillation photons produced in this event : "
   //       << mEmittedScntPhotonNum << G4endl;
  // G4cout << "Number of Cerenkov photons produced in this event : "
  //        << mEmittedCerenkovPhotonNum << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingAction::PrepareNewEvent()
{
  mEmittedScntPhotonNum     = 0;
  mEmittedCerenkovPhotonNum = 0;
  
  mOPEnergyVec.clear();
  mOPWavelengthVec.clear();
  mOPTimeVec.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int StackingAction::GetEmittedScintillationPhotonNumber() const
{ 
  return mEmittedScntPhotonNum; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int StackingAction::GetEmittedCerenkovPhotonNumber() const
{ 
  return mEmittedCerenkovPhotonNum; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<G4double> StackingAction::GetOPEnergyVector() const 
{ 
  return mOPEnergyVec; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
std::vector<G4double> StackingAction::GetOPWavelengthVector() const 
{ 
  return mOPWavelengthVec; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<G4double> StackingAction::GetOPTimeVector() const 
{ 
  return mOPTimeVec; 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
