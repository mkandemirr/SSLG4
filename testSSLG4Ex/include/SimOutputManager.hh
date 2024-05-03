#ifndef SimOutputManager_h
#define SimOutputManager_h 1

#include "G4AnalysisManager.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SimOutputManagerMsgr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SimOutputManager
{
  public:
    SimOutputManager();
   ~SimOutputManager();
    
    void Initialize();
    
    void BeginOfEventAction(const G4Event* event);
    void EndOfEventAction(const G4Event* event);
    
    void BeginOfRunAction(const G4Run* aRun);
    void EndOfRunAction(const G4Run* aRun);
  
  public: //UI commands
    void SetPrintMode(bool printMode);
    void AddEdep(G4double edep) { mEdep += edep; }                        
  
  private:
    void Book();
    void Save();
    void Reset();
      
    void SetStackingActionOutputs();
    
    void FillGeneralNtuple();
    void PrintGeneralOutputs();
    
    template <typename T>
    T GetHitsCollection(const G4String& name,
                        const G4Event* event
                        ) const;
    
  private: //members
    SimOutputManagerMsgr* mMessenger;
    bool mPrintMode;
        
    //General outputs
    int mEventID;
    double mEdep;
    int mEmittedScntPhotonNum;
    int mEmittedCerenkovPhotonNum;
   
    std::vector<G4double> mOPEnergyVec;
    std::vector<G4double> mOPWavelengthVec;
    std::vector<G4double> mOPTimeVec;
          
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

template <typename T>
T SimOutputManager::GetHitsCollection
(
  const G4String& name,
  const G4Event* event
) const
{
  // Get hits collections IDs (only once)
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(name);
  
  auto hitsCollection = static_cast<T>(event->GetHCofThisEvent()->GetHC(hcID));

  if (! hitsCollection) 
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

