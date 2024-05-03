#include "SimOutputManager.hh"
#include "SimOutputManagerMsgr.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UserRunAction.hh"
#include "StackingAction.hh"
#include "G4UImanager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimOutputManager::SimOutputManager():
mMessenger{nullptr},
mPrintMode{false},
mEventID{-1},
mEdep{0.},
mEmittedScntPhotonNum{-1},
mEmittedCerenkovPhotonNum{-1}
{
  mMessenger = new SimOutputManagerMsgr(this);
  Initialize();     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SimOutputManager::~SimOutputManager()
{
  delete mMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::Initialize()
{
  //This line is necessary!
  G4UImanager::GetUIpointer()->ExecuteMacroFile("macros/simAnalysis.mac");
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::Book()
{
  /*
  The activation option (SetActivation) allows the user to activate only 
  selected histograms. When this option is activated, only the histograms 
  marked as activated are returned, filled or saved in a file. This feature is 
  intensively used in extended/electromagnetic examples where all histograms 
  are first created inactivated 
  */
  /*
  Each entry in the output files correspond to an event in the simulation. 
  Events are shared by threads.
  */
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("root");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);//enable inactivation of histos, nTuples
  analysisManager->SetFirstNtupleId(0);
  
  // Create 2nd ntuple (id = 1)  
  analysisManager->CreateNtuple("SSLG4", "Check Scintillator inputs");
  analysisManager->CreateNtupleIColumn("EventID"); //column id = 0
  analysisManager->CreateNtupleDColumn("TotalEdep");
  analysisManager->CreateNtupleIColumn("EmittedScntPhotonNum");  
  analysisManager->CreateNtupleIColumn("EmittedCerenkovPhotonNum"); 
 
  analysisManager->CreateNtupleDColumn("OPEnergyVec", mOPEnergyVec);
  analysisManager->CreateNtupleDColumn("OPWavelengthVec", mOPWavelengthVec);
  analysisManager->CreateNtupleDColumn("OPTimeVec", mOPTimeVec);
                                      
  analysisManager->FinishNtuple(0);

                                                         
  analysisManager->SetNtupleActivation(false); //all ntuples are diacticated 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::BeginOfRunAction(const G4Run* aRun)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile("output/SimOutput");
   
  G4cout << "\n----> Output file is open in "
         << analysisManager->GetFileName() << "."
         << analysisManager->GetFileType() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::BeginOfEventAction(const G4Event* event)
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::EndOfEventAction(const G4Event* event)
{
  mEventID = event->GetEventID();
  SetStackingActionOutputs();
  
  if (mPrintMode)
  {
    PrintGeneralOutputs(); 
  }
    
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  if (analysisManager->GetNtupleActivation(0))
    FillGeneralNtuple();
                                                          
  Reset();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::SetStackingActionOutputs()
{
  const G4UserStackingAction* sa = G4RunManager::GetRunManager()->
                                     GetUserStackingAction();
                                     
  const StackingAction *userSA = dynamic_cast<const StackingAction*> (sa);                                   
  
  if (userSA)
  {
    mEmittedScntPhotonNum = userSA->GetEmittedScintillationPhotonNumber();
    mEmittedCerenkovPhotonNum = userSA->GetEmittedCerenkovPhotonNumber();
    
    mOPEnergyVec     = userSA->GetOPEnergyVector();
    mOPWavelengthVec = userSA->GetOPWavelengthVector();
    mOPTimeVec       = userSA->GetOPTimeVector();
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::PrintGeneralOutputs()
{
  G4cout<<"----------General Ntuple Outputs-----------"<<G4endl;
  G4cout<<"Event ID: "<<mEventID<<G4endl;
  G4cout<<"TotalEdep: "<<mEdep<<G4endl;
  G4cout<<"EmittedScintillationPhotonNumber: "<<mEmittedScntPhotonNum<<G4endl;
  G4cout<<"EmittedCerenkovPhotonNumber: "<<mEmittedCerenkovPhotonNum<<G4endl;   
}

void SimOutputManager::FillGeneralNtuple()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
   
  analysisManager->FillNtupleIColumn(0, 0, mEventID);
  analysisManager->FillNtupleDColumn(0, 1, mEdep);
  analysisManager->FillNtupleIColumn(0, 2, mEmittedScntPhotonNum);
  analysisManager->FillNtupleIColumn(0, 3, mEmittedCerenkovPhotonNum);
 
  analysisManager->AddNtupleRow(0); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::Reset()
{
  //General
  mEventID = -1;
  mEdep = 0.;
  mEmittedScntPhotonNum = -1;
  mEmittedCerenkovPhotonNum = -1;
  
  if (mPrintMode)
    G4cout<<"All values have been reset"<<G4endl;
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::EndOfRunAction(const G4Run* aRun)
{
  G4int nofEvents = aRun->GetNumberOfEvent();
 
  Save();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::Save()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  analysisManager->Write();
  analysisManager->CloseFile();
  analysisManager->Clear();

  G4cout << "\n----> Ntuples are saved\n" << G4endl;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SimOutputManager::SetPrintMode(bool printMode)
{
  mPrintMode = printMode;
}

