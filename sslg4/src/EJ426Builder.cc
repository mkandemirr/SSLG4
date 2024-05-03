#include "EJ426Builder.hh"
#include "G4Material.hh"
#include "MaterialPropertiesTable.hh"
#include "G4UImanager.hh"
#include "G4NistManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EJ426Builder::EJ426Builder
(
  const G4String& name,
  const G4String& macroFilePath, 
  G4bool enableMPT
):
VMaterialBuilder(enableMPT),
mProductName{name}, 
mMacroFilePath{macroFilePath}
{
  if (IsMPTEnabled())
  {
    pMPT = new MaterialPropertiesTable(mProductName); 
    G4UImanager::GetUIpointer()->ExecuteMacroFile(mMacroFilePath);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EJ426Builder::~EJ426Builder()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* EJ426Builder::Build()          
{ 
  G4double density,a;
  G4int nComponents,Z,A;
  
  G4Element *el_F    = pNistManager->FindOrBuildElement("F"); //Flourine
  G4Element *el_Zn   = pNistManager->FindOrBuildElement("Zn");
  G4Element* el_S    = pNistManager->FindOrBuildElement("S");  
  G4Element* el_Si   = pNistManager->FindOrBuildElement("Si");
  
  //EnrichedLi  
  G4Isotope *Li6  = new G4Isotope("Li6", Z=3, A=6, a= 6.015122795*g/mole);
  G4Isotope *Li7  = new G4Isotope("Li7", Z=3, A=7, a= 7.01600455*g/mole);

  G4Element* enrichedLi_el  = new G4Element("EnrichedLithium", "Li", 
                                            nComponents=2);
  enrichedLi_el->AddIsotope(Li6, 95.*perCent);
  enrichedLi_el->AddIsotope(Li7, 5.*perCent);
  
//https://www.pnnl.gov/main/publications/external/technical_reports/pnnl-22228.pdf
//Table 23. Material input data used for IAT-Validation model of CS layers.
  G4Material *scin_mat = new G4Material(mProductName, 
                                        density=2.42*g/cm3, 
                                        nComponents = 8
                                        );
                                           
  scin_mat->AddElement(enrichedLi_el, 3.93*perCent); ////3.70(Li6) + 0.23(Li7)
  scin_mat->AddElement(el_F,  12.31*perCent);
  scin_mat->AddElement(el_Zn, 43.58*perCent);
  scin_mat->AddElement(el_S,  21.37*perCent);
  scin_mat->AddElement(el_Si, 7.69*perCent);
  scin_mat->AddElement(pNistManager->FindOrBuildElement("C"),  6.57*perCent);
  scin_mat->AddElement(pNistManager->FindOrBuildElement("H"),  0.17*perCent);
  scin_mat->AddElement(pNistManager->FindOrBuildElement("O"),  4.38*perCent);
    
  //G4cout<<"Li6 atomDensity(1/cm3): "<<(2.42*0.0393/(6.02*0.95+7.02*0.05))*
  //6.02e+23*0.95<<G4endl;
 
  /*
  //Table 24. Material Input Data used for LANL-NCCR model of CS layers. 
  //LANL(Los Alamos National Laboratory)
  G4Material *scin_mat = new G4Material("EJ-426", 
                                        density=1.5386*g/cm3, 
                                        nComponents =7
                                        );
                                        
  scin_mat->AddElement(enrichedLi_el, 4.84*perCent); //4.60(Li6) + 0.24(Li7)
  scin_mat->AddElement(el_F,  15.16*perCent);
  scin_mat->AddElement(el_Zn, 42.82*perCent);
  scin_mat->AddElement(el_S,  20.93*perCent);
  scin_mat->AddElement(fNistManager->FindOrBuildElement("C"),  9.74*perCent);
  scin_mat->AddElement(fNistManager->FindOrBuildElement("H"),  1.31*perCent);
  scin_mat->AddElement(fNistManager->FindOrBuildElement("O"),  5.19*perCent);
  */  
   
  return scin_mat;  
}

