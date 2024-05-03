#include "ScintillatorBuilder.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "MaterialPropertiesTable.hh"
#include "G4UImanager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintillatorBuilder::ScintillatorBuilder
(
  const G4String& name,                                       
  const G4String& macroFilePath,
  G4double density,
  ElementFracVec elFracVec,
  G4bool enableMPT 
):
VMaterialBuilder(enableMPT),
mName{name},
mMacroFilePath{macroFilePath},
mDensity{density},
mMaterial{nullptr}, 
mElementFracVec{elFracVec}
{
  DefineMPTUICommands();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintillatorBuilder::ScintillatorBuilder
(
  const G4String& name,                                       
  const G4String& macroFilePath,
  G4double density,
  ElementNumVec elNumVec,
  G4bool enableMPT 
):
VMaterialBuilder(enableMPT),
mName{name},
mMacroFilePath{macroFilePath},
mDensity{density},
mMaterial{nullptr}, 
mElementNumVec{elNumVec}
{
  DefineMPTUICommands(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintillatorBuilder::ScintillatorBuilder
(
  const G4String& name,                                       
  const G4String& macroFilePath,
  G4Material* mat,
  G4bool enableMPT 
):
VMaterialBuilder(enableMPT),
mName{name},
mMacroFilePath{macroFilePath},
mDensity{0.}, //will not be used for this constructor
mMaterial{mat}
{
  DefineMPTUICommands();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintillatorBuilder::~ScintillatorBuilder()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ScintillatorBuilder::DefineMPTUICommands()
{
  if (IsMPTEnabled())
  {
    pMPT = new MaterialPropertiesTable(mName);  
    G4UImanager::GetUIpointer()->ExecuteMacroFile(mMacroFilePath);
  }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* ScintillatorBuilder::Build()          
{
  if (mMaterial) //for third constructor
    return mMaterial;
  
  if(mElementFracVec.size() != 0)
    return BuildScntFromElementFractions();
  else
   return BuildScntFromElementNumbers();  
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* ScintillatorBuilder::BuildScntFromElementFractions()
{
  G4int nElements = mElementFracVec.size();
  mMaterial = new G4Material(mName, mDensity, nElements); 
  
  for (const auto& pair : mElementFracVec) 
  {
    mMaterial->AddElement(pNistManager->FindOrBuildElement(pair.first), 
                          pair.second
                          );
  }
  return mMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* ScintillatorBuilder::BuildScntFromElementNumbers()
{
  G4int nElements = mElementNumVec.size();
  mMaterial = new G4Material(mName, mDensity, nElements);
  
  for (const auto& pair : mElementNumVec) 
  {
    mMaterial->AddElement(pNistManager->FindOrBuildElement(pair.first), 
                          pair.second
                          );
  }
  return mMaterial;    
}

