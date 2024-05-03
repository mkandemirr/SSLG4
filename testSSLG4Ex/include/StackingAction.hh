//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef StackingAction_h
#define StackingAction_h 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StackingAction : public G4UserStackingAction
{
 public:
  StackingAction();
  ~StackingAction();

  G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack) override;
  void NewStage() override;
  void PrepareNewEvent() override;

  G4int GetEmittedScintillationPhotonNumber() const;
  G4int GetEmittedCerenkovPhotonNumber() const;
  
  std::vector<G4double> GetOPEnergyVector() const;
  std::vector<G4double> GetOPWavelengthVector() const;
  std::vector<G4double> GetOPTimeVector() const;
    
 private:
  std::vector<G4double> mOPEnergyVec;
  std::vector<G4double> mOPWavelengthVec;
  std::vector<G4double> mOPTimeVec;
  
  G4int mEmittedScntPhotonNum;
  G4int mEmittedCerenkovPhotonNum;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
