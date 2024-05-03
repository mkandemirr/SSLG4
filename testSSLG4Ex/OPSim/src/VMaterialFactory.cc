#include "VMaterialFactory.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialFactory::VMaterialFactory()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

VMaterialFactory::~VMaterialFactory()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* VMaterialFactory::Get(const G4String& name, G4bool enableMPT)
{
  //user-defined material
  G4Material* mat = CreateMaterial(name, enableMPT);
  //-----------
  if (!mat) 
  {
    std::ostringstream o;
    o << "Material " << name << " not found!";
    G4Exception("VMaterialFactory::GetMaterial()",
                "",
                FatalException,
                o.str().c_str()
                );
  }

  return mat;
}
