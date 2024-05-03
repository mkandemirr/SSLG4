//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "OpticalSurfaceMessenger.hh"
#include "OpticalSurface.hh"
#include "G4StateManager.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIdirectory.hh"

#include <sstream>
#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpticalSurfaceMessenger::OpticalSurfaceMessenger(OpticalSurface* optSurface)
: G4UImessenger(), 
fOptSurface(optSurface),
fDirectory{nullptr},
fSurfaceTypeCmd{nullptr},
fSurfaceFinishCmd{nullptr},
fSurfaceModelCmd{nullptr},
fSurfaceSigmaAlphaCmd{nullptr},
fSurfacePolishCmd{nullptr}
{

  G4String rootDirectory     = "/os/"; 
  G4String commandDirectory  = "/os/"+fOptSurface->GetName()+"/";
  
  if(fDirectory)
  {
    fDirectory = new G4UIdirectory(rootDirectory);
  }
  
  //-------Command 1----------
  G4String commandName  = "type";
  G4String commandPath  = commandDirectory+commandName;
  G4String usage        = "[usage] "+ commandPath + " surfaceType";
  
  fSurfaceTypeCmd = new G4UIcmdWithAString(commandPath, this);
  fSurfaceTypeCmd->SetGuidance(usage);
  fSurfaceTypeCmd->SetParameterName(commandName,false,false);
  fSurfaceTypeCmd->AvailableForStates(G4State_PreInit, G4State_Init);
  fSurfaceTypeCmd->SetToBeBroadcasted(false);

  //-------Command 2----------
  commandName ="finish";
  commandPath = commandDirectory+commandName;
  usage       = "[usage] "+ commandPath + " surfaceFinish";
   
  fSurfaceFinishCmd = new G4UIcmdWithAString(commandPath, this);
  fSurfaceFinishCmd->SetGuidance(usage);
  fSurfaceFinishCmd->SetParameterName(commandName,false,false);
  fSurfaceFinishCmd->AvailableForStates(G4State_PreInit, G4State_Init);
  fSurfaceFinishCmd->SetToBeBroadcasted(false);
  
  //-------Command 3----------
  commandName ="model";
  commandPath = commandDirectory+commandName;
  usage       = "[usage] "+ commandPath + " surfaceModel";
   
  fSurfaceModelCmd = new G4UIcmdWithAString(commandPath, this);
  fSurfaceModelCmd->SetGuidance(usage);
  fSurfaceModelCmd->SetParameterName(commandName,false,false);
  fSurfaceModelCmd->AvailableForStates(G4State_PreInit, G4State_Init);
  fSurfaceModelCmd->SetToBeBroadcasted(false);
  
  //-------Command 4----------
  commandName ="sigmaAlpha";
  commandPath = commandDirectory+commandName;
  usage       = "[usage] "+ commandPath + " surfaceSigmaAlpha";
  
  fSurfaceSigmaAlphaCmd = new G4UIcmdWithADouble(commandPath, this);
  fSurfaceSigmaAlphaCmd->SetGuidance(usage);
  fSurfaceSigmaAlphaCmd->SetParameterName(commandName,false,false);
  fSurfaceSigmaAlphaCmd->AvailableForStates(G4State_PreInit, G4State_Init);
  fSurfaceSigmaAlphaCmd->SetToBeBroadcasted(false);
  
  //-------Command 5----------
  commandName ="polish";
  commandPath = commandDirectory+commandName;
  usage       = "[usage] "+ commandPath + " surfacePolish";
  
  fSurfacePolishCmd = new G4UIcmdWithADouble(commandPath, this);
  fSurfacePolishCmd->SetGuidance(usage);
  fSurfacePolishCmd->SetParameterName(commandName,false,false);
  fSurfacePolishCmd->SetGuidance(" parameter (for Glisur model).");
  fSurfacePolishCmd->AvailableForStates(G4State_PreInit, G4State_Init);
  fSurfacePolishCmd->SetToBeBroadcasted(false);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpticalSurfaceMessenger::~OpticalSurfaceMessenger()
{
 
  delete fSurfaceFinishCmd;
  delete fSurfaceTypeCmd;
  delete fSurfaceModelCmd;
  delete fSurfaceSigmaAlphaCmd;
  delete fSurfacePolishCmd;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpticalSurfaceMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  //    FINISH
  if(command == fSurfaceFinishCmd)
  {
    if(newValue == "polished")
    {
      fOptSurface->SetFinish(polished);
    }
    else if(newValue == "polishedfrontpainted")
    {
      fOptSurface->SetFinish(polishedfrontpainted);
    }
    else if(newValue == "polishedbackpainted")
    {
      fOptSurface->SetFinish(polishedbackpainted);
    }
    else if(newValue == "ground")
    {
      fOptSurface->SetFinish(ground);
    }
    else if(newValue == "groundfrontpainted")
    {
      fOptSurface->SetFinish(groundfrontpainted);
    }
    else if(newValue == "groundbackpainted")
    {
      fOptSurface->SetFinish(groundbackpainted);
    }
    else if(newValue == "polishedlumirrorair")
    {
      fOptSurface->SetFinish(polishedlumirrorair);
    }
    else if(newValue == "polishedlumirrorglue")
    {
      fOptSurface->SetFinish(polishedlumirrorglue);
    }
    else if(newValue == "polishedair")
    {
      fOptSurface->SetFinish(polishedair);
    }
    else if(newValue == "polishedteflonair")
    {
      fOptSurface->SetFinish(polishedteflonair);
    }
    else if(newValue == "polishedtioair")
    {
      fOptSurface->SetFinish(polishedtioair);
    }
    else if(newValue == "polishedtyvekair")
    {
      fOptSurface->SetFinish(polishedtyvekair);
    }
    else if(newValue == "polishedvm2000air")
    {
      fOptSurface->SetFinish(polishedvm2000air);
    }
    else if(newValue == "polishedvm2000glue")
    {
      fOptSurface->SetFinish(polishedvm2000glue);
    }
    else if(newValue == "etchedlumirrorair")
    {
      fOptSurface->SetFinish(etchedlumirrorair);
    }
    else if(newValue == "etchedlumirrorglue")
    {
      fOptSurface->SetFinish(etchedlumirrorglue);
    }
    else if(newValue == "etchedair")
    {
      fOptSurface->SetFinish(etchedair);
    }
    else if(newValue == "etchedteflonair")
    {
      fOptSurface->SetFinish(etchedteflonair);
    }
    else if(newValue == "etchedtioair")
    {
      fOptSurface->SetFinish(etchedtioair);
    }
    else if(newValue == "etchedtyvekair")
    {
      fOptSurface->SetFinish(etchedtyvekair);
    }
    else if(newValue == "etchedvm2000air")
    {
      fOptSurface->SetFinish(etchedvm2000air);
    }
    else if(newValue == "etchedvm2000glue")
    {
      fOptSurface->SetFinish(etchedvm2000glue);
    }
    else if(newValue == "groundlumirrorair")
    {
      fOptSurface->SetFinish(groundlumirrorair);
    }
    else if(newValue == "groundlumirrorglue")
    {
      fOptSurface->SetFinish(groundlumirrorglue);
    }
    else if(newValue == "groundair")
    {
      fOptSurface->SetFinish(groundair);
    }
    else if(newValue == "groundteflonair")
    {
      fOptSurface->SetFinish(groundteflonair);
    }
    else if(newValue == "groundtioair")
    {
      fOptSurface->SetFinish(groundtioair);
    }
    else if(newValue == "groundtyvekair")
    {
      fOptSurface->SetFinish(groundtyvekair);
    }
    else if(newValue == "groundvm2000air")
    {
      fOptSurface->SetFinish(groundvm2000air);
    }
    else if(newValue == "groundvm2000glue")
    {
      fOptSurface->SetFinish(groundvm2000glue);
    }
    // for Davis model
    else if(newValue == "Rough_LUT")
    {
      fOptSurface->SetFinish(Rough_LUT);
    }
    else if(newValue == "RoughTeflon_LUT")
    {
      fOptSurface->SetFinish(RoughTeflon_LUT);
    }
    else if(newValue == "RoughESR_LUT")
    {
      fOptSurface->SetFinish(RoughESR_LUT);
    }
    else if(newValue == "RoughESRGrease_LUT")
    {
      fOptSurface->SetFinish(RoughESRGrease_LUT);
    }
    else if(newValue == "Polished_LUT")
    {
      fOptSurface->SetFinish(Polished_LUT);
    }
    else if(newValue == "PolishedTeflon_LUT")
    {
      fOptSurface->SetFinish(PolishedTeflon_LUT);
    }
    else if(newValue == "PolishedESR_LUT")
    {
      fOptSurface->SetFinish(PolishedESR_LUT);
    }
    else if(newValue == "PolishedESRGrease_LUT")
    {
      fOptSurface->SetFinish(PolishedESRGrease_LUT);
    }
    else if(newValue == "Detector_LUT")
    {
      fOptSurface->SetFinish(Detector_LUT);
    }
    else
    {
      G4ExceptionDescription ed;
      ed << "Invalid surface finish: " << newValue;
      G4Exception("OpticalSurfaceMessenger", "OpNovice2_003", FatalException, ed);
    }
  }

  // MODEL
  else if(command == fSurfaceModelCmd)
  {
    if(newValue == "glisur")
    {
      fOptSurface->SetModel(glisur);
    }
    else if(newValue == "unified")
    {
      fOptSurface->SetModel(unified);
    }
    else if(newValue == "LUT")
    {
      fOptSurface->SetModel(LUT);
    }
    else if(newValue == "DAVIS")
    {
      fOptSurface->SetModel(DAVIS);
    }
    else if(newValue == "dichroic")
    {
      fOptSurface->SetModel(dichroic);
    }
    else
    {
      G4ExceptionDescription ed;
      ed << "Invalid surface model: " << newValue;
      G4Exception("OpticalSurfaceMessenger", 
                  "ONovice2_001", 
                  FatalException, 
                  ed
                  );
    }
  }

  // TYPE
  else if(command == fSurfaceTypeCmd)
  {
    if(newValue == "dielectric_metal")
    {
      fOptSurface->SetType(dielectric_metal);
    }
    else if(newValue == "dielectric_dielectric")
    {
      fOptSurface->SetType(dielectric_dielectric);
    }
    else if(newValue == "dielectric_LUT")
    {
      fOptSurface->SetType(dielectric_LUT);
    }
    else if(newValue == "dielectric_LUTDAVIS")
    {
      fOptSurface->SetType(dielectric_LUTDAVIS);
    }
    else
    {
      G4ExceptionDescription ed;
      ed << "Invalid surface type: " << newValue;
      G4Exception("OpticalSurfaceMessenger", 
                  "OpNovice2_002", 
                  FatalException, 
                  ed
                  );
    }
 
  }
  
  else if(command == fSurfaceSigmaAlphaCmd)
  {
    fOptSurface->SetSigmaAlpha(G4UIcmdWithADouble::GetNewDoubleValue(newValue));
  }

  else if(command == fSurfacePolishCmd)
  {
    fOptSurface->SetPolish(G4UIcmdWithADouble::GetNewDoubleValue(newValue));
  }

}
