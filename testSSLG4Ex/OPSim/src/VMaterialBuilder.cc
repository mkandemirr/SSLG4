#include "VMaterialBuilder.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "MaterialPropertiesTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialBuilder::VMaterialBuilder(G4bool enableMPT) : 
pNistManager{G4NistManager::Instance()},
bEnableMPT{enableMPT},
pMPT{nullptr}
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialBuilder::~VMaterialBuilder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//Template method.
G4Material* VMaterialBuilder::GetProduct()
{
  G4Material* mat = Build();
  
  if(IsMPTEnabled())
  {
    mat->SetMaterialPropertiesTable(pMPT);
  }
    
  return mat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

