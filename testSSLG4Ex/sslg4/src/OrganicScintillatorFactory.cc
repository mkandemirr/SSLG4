#include "OrganicScintillatorFactory.hh"
#include "ScintillatorBuilder.hh"
#include "EJ426Builder.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OrganicScintillatorFactory* OrganicScintillatorFactory::mInstance = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OrganicScintillatorFactory::OrganicScintillatorFactory():
VMaterialFactory(),
mDensity{0.},
mHydrogenAD{0.},
mCarbonAD{0.},
bEnableMPT{false},
mMaterial{nullptr}
{
  mMacrosDirectoryPath = "sslg4/macros/oscnt/"; //relative to CMAKE_BINARY_DIR
  
  //Available products in the factory. 
  //35 plastic (eljen), 3 plastic (sp), 14 liquid (Eljen), 5 liquid WbLS
  //Total 35 + 3 + 15 + 5 = 58
  
  //Plastic scintillator
  //Eljen and Luxium
  mProductsSet.insert("opsc-100"); //EJ-200/Pilot F/BC-408
  mProductsSet.insert("opsc-101"); //EJ-204/NE-104/BC-404
  mProductsSet.insert("opsc-102"); //EJ-208/NE-110/BC-412
  mProductsSet.insert("opsc-103"); //EJ-212/NE-102A/BC-400
  mProductsSet.insert("opsc-104"); //EJ-214
  mProductsSet.insert("opsc-105"); //EJ-228/Pilot U/BC-418
  mProductsSet.insert("opsc-106"); //EJ-230/Pilot U2/BC-420
  mProductsSet.insert("opsc-107"); //EJ-232/NE-111A/BC-422
  mProductsSet.insert("opsc-108"); //EJ-232Q-0.5
  mProductsSet.insert("opsc-109"); //EJ-232Q-1.0
  mProductsSet.insert("opsc-110"); //EJ-232Q-2.0
  mProductsSet.insert("opsc-111"); //EJ-232Q-3.0
  mProductsSet.insert("opsc-112"); //EJ-232Q-5.0
  mProductsSet.insert("opsc-113"); //EJ-240/NE-115/BC-444
  mProductsSet.insert("opsc-114"); //EJ-244/BC-440
  mProductsSet.insert("opsc-115"); //EJ-244M/BC-440M
  mProductsSet.insert("opsc-116"); //EJ-248/BC-448
  mProductsSet.insert("opsc-117"); //EJ-248M
  mProductsSet.insert("opsc-118"); //EJ-254-1pct
  mProductsSet.insert("opsc-119"); //EJ-254-2.5pct
  mProductsSet.insert("opsc-120"); //EJ-254-5pct
  mProductsSet.insert("opsc-121"); //EJ-256-1.5pct
  mProductsSet.insert("opsc-122"); //EJ-256-5pct
  mProductsSet.insert("opsc-123"); //EJ-260/NE-103/BC-428
  mProductsSet.insert("opsc-124"); //EJ-262
  mProductsSet.insert("opsc-125"); //EJ-276D
  mProductsSet.insert("opsc-126"); //EJ-276G
  
  // WLS plastic. ABSLENGTH property is important for these. 
  mProductsSet.insert("opsc-127"); //EJ-280
  mProductsSet.insert("opsc-128"); //EJ-282
  mProductsSet.insert("opsc-129"); //EJ-284
  mProductsSet.insert("opsc-130"); //EJ-286
  
  mProductsSet.insert("opsc-131"); //EJ-290/BC-490/NE-120
  mProductsSet.insert("opsc-132"); //EJ-296/BC-498
  
  //Thermal neutron detector
  mProductsSet.insert("opsc-133"); //EJ-426
  
  //Nuviatech Instruments
  mProductsSet.insert("opsc-200"); //SP-32
  mProductsSet.insert("opsc-201"); //SP-33
  //Hangzhou Shalom EO
  mProductsSet.insert("opsc-300"); //SP-102
  
  //Rexon Components
  mProductsSet.insert("opsc-400"); //RP-408
  
  
  //Liquid Scintillator
  mProductsSet.insert("olsc-100"); //EJ-301/NE-213/BC-501A
  mProductsSet.insert("olsc-101"); //EJ-309
  mProductsSet.insert("olsc-102"); //EJ-309B-1pct
  mProductsSet.insert("olsc-103"); //EJ-309B-2.5pct
  mProductsSet.insert("olsc-104"); //EJ-309B-5pct
  mProductsSet.insert("olsc-105"); //EJ-313/NE-226/BC-509
  mProductsSet.insert("olsc-106"); //EJ-315-H/BC-537/NE-230
  mProductsSet.insert("olsc-107"); //EJ-321H
  mProductsSet.insert("olsc-108"); //EJ-321L
  mProductsSet.insert("olsc-109"); //EJ-321P
  mProductsSet.insert("olsc-110"); //EJ-321S
  mProductsSet.insert("olsc-111"); //EJ-325A
  mProductsSet.insert("olsc-112"); //EJ-331-0.5pct/NE-323/BC-521
  mProductsSet.insert("olsc-113"); //EJ-335-0.25pct/BC-525
  mProductsSet.insert("olsc-114"); //EJ-351/NE-220/BC-573
  
  //Domain specific LS.Taken from https://github.com/rat-pac/rat-pac
  //Wbls
  mProductsSet.insert("olsc-200"); //WbLS-1pct
  mProductsSet.insert("olsc-201"); //WbLS-1pct-gd-0.1pct
  mProductsSet.insert("olsc-202"); //WbLS- 3pct
  mProductsSet.insert("olsc-203"); //WbLS- 3pct-gd-0.1pct
  mProductsSet.insert("olsc-204"); //WbLS-5pct
    
  //Dont use upper case letter when naming scintillator!!!
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OrganicScintillatorFactory::~OrganicScintillatorFactory()
{	 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* OrganicScintillatorFactory::CreateMaterial
(
  const G4String& name, 
  G4bool enableMPT
)
{
  G4Material* mat = G4NistManager::Instance()->FindOrBuildMaterial(name);
  if (mat) return mat;
  
  mProductName   = GetStringAsLowerCase(name);
  mMacroFilePath = mMacrosDirectoryPath + mProductName + ".mac";
  bEnableMPT     = enableMPT;
  
  if (mProductsSet.find(mProductName) == mProductsSet.end()) //not found
    return nullptr; 
  
  if (mProductName == "opsc-100") 
  {
    mHydrogenAD = 5.17e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-101") 
  {
    mHydrogenAD = 5.15e+22*(1./cm3);
    mCarbonAD   = 4.68e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-102")
  {
    mHydrogenAD = 5.17e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-103")
  {
    mHydrogenAD = 5.17e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-104")
  {
    mHydrogenAD = 5.18e+22*(1./cm3);
    mCarbonAD   = 4.67e+22*(1./cm3);
    G4double nitrojenAD = 4.89e+19*(1./cm3);
    G4double oxygenAD   = 2.59e+19*(1./cm3);
    mDensity = 1.02*g/cm3;  
    G4double hMD = GetMDFromAD("H", mHydrogenAD);
    G4double cMD = GetMDFromAD("C", mCarbonAD);
    G4double nMD = GetMDFromAD("N", nitrojenAD);
    G4double oMD = GetMDFromAD("O", oxygenAD);
    
    G4double hMF = hMD/mDensity;
    G4double cMF = cMD/mDensity;
    G4double nMF = nMD/mDensity;
    G4double oMF = oMD/mDensity;
    
    mElementFracVec = { {"H", hMF}, {"C", cMF}, {"N", nMF}, {"O", oMF} };
  
    ScintillatorBuilder builder(mProductName, 
                                mMacroFilePath,
                                mDensity,
                                mElementFracVec,
                                bEnableMPT
                                );
    mElementFracVec.clear();                            
    return builder.GetProduct(); 
      
  }else if (mProductName == "opsc-105")
  {
    mHydrogenAD = 5.15e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-106")
  {
    mHydrogenAD = 5.15e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-107")
  {
    mHydrogenAD = 5.13e+22*(1./cm3);
    mCarbonAD   = 4.66e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-108")
  {
    mHydrogenAD = 5.12e+22*(1./cm3);
    mCarbonAD   = 4.66e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-109")
  {
    mHydrogenAD = 5.12e+22*(1./cm3);
    mCarbonAD   = 4.66e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-110")
  {
    mHydrogenAD = 5.12e+22*(1./cm3);
    mCarbonAD   = 4.66e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-111")
  {
    mHydrogenAD = 5.12e+22*(1./cm3);
    mCarbonAD   = 4.66e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-112")
  {
    mHydrogenAD = 5.12e+22*(1./cm3);
    mCarbonAD   = 4.66e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-114")
  {
    mHydrogenAD = 5.18e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-115")
  {
    mHydrogenAD = 5.18e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-116")
  {
    mHydrogenAD = 5.18e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-117")
  {
    mHydrogenAD = 5.18e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-113")
  {
    mHydrogenAD = 5.19e+22*(1./cm3);
    mCarbonAD   = 4.68e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-118")
  {
    mHydrogenAD       = 5.16e+22*(1./cm3);
    G4String symb     = "B";
    G4double boronMF  = 1*perCent;
    mDensity          = 1.021*(g/cm3);
    return BuildLoadedScintillator(symb, boronMF);
    
  }else if (mProductName == "opsc-119")
  {
    mHydrogenAD       = 5.17e+22*(1./cm3);
    G4String symb     = "B";
    G4double boronMF  = 2.5*perCent;
    mDensity          = 1.023*(g/cm3);
    return BuildLoadedScintillator(symb, boronMF);
    
  }else if (mProductName == "opsc-120")
  {
    mHydrogenAD       = 5.18e+22*(1./cm3);
    G4String symb     = "B";
    G4double boronMF  = 5*perCent;
    mDensity          = 1.026*(g/cm3);
    return BuildLoadedScintillator(symb, boronMF);
    
  }else if (mProductName == "opsc-121")
  {
    mHydrogenAD       = 5.21e+22*(1./cm3);
    G4String symb     = "Pb";
    G4double leadMF   = 1.5*perCent;
    mDensity          = 1.037*(g/cm3);
    return BuildLoadedScintillator(symb, leadMF);
    
  }else if (mProductName == "opsc-122") //carbon ad tam uymuyor!!
  {
    mHydrogenAD       = 5.20e+22*(1./cm3);
    G4String symb     = "Pb";
    G4double leadMF   = 5*perCent;
    mDensity          = 1.081*(g/cm3);
    return BuildLoadedScintillator(symb, leadMF);
                                  
  }else if (mProductName == "opsc-123")
  {
    mHydrogenAD = 5.21e+22*(1./cm3);
    mCarbonAD   = 4.70e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-124")
  {
    mHydrogenAD = 5.20e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-125")
  {
    mHydrogenAD = 4.647e+22*(1./cm3);
    mCarbonAD   = 4.944e+22*(1./cm3);
    mDensity    = 1.099*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-126")
  {
    mHydrogenAD = 4.647e+22*(1./cm3);
    mCarbonAD   = 4.944e+22*(1./cm3);
    mDensity    = 1.099*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-127")
  {
    mHydrogenAD = 5.20e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-128")
  {
    mHydrogenAD = 5.20e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-129")
  {
    mHydrogenAD = 5.20e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-130")
  {
    mHydrogenAD = 5.20e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.023*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-131")
  {
    mHydrogenAD = 5.17e+22*(1./cm3);
    mCarbonAD   = 4.67e+22*(1./cm3);
    mDensity    = 1.02*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "opsc-132")
  {
    mHydrogenAD = 5.17e+22*(1./cm3);
    mCarbonAD   = 4.69e+22*(1./cm3);
    mDensity    = 1.02*g/cm3;
    return BuildScintillator();
  }
  
  //Liquid
  else if (mProductName == "olsc-100")
  {
    mHydrogenAD = 4.82e+22*(1./cm3);
    mCarbonAD   = 3.98e+22*(1./cm3);
    mDensity    = 0.874*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "olsc-101")
  {
    mHydrogenAD = 5.43e+22*(1./cm3);
    mCarbonAD   = 4.35e+22*(1./cm3);
    mDensity    = 0.959*g/cm3;
    return BuildScintillator();
    
  }else if (mProductName == "olsc-102")
  {
    mHydrogenAD       = 5.44e+22*(1./cm3);
    G4String symb     = "B";
    G4double boronMF  = 1*perCent;
    mDensity          = 0.965*(g/cm3);
    return BuildLoadedScintillator(symb, boronMF);
    
  }else if (mProductName == "olsc-103")
  {
    mHydrogenAD       = 5.43e+22*(1./cm3);
    G4String symb     = "B";
    G4double boronMF  = 2.5*perCent;
    mDensity          = 0.964*(g/cm3);
    return BuildLoadedScintillator(symb, boronMF);
  }else if (mProductName == "olsc-104")
  {
    mHydrogenAD       = 5.40e+22*(1./cm3);
    G4String symb     = "B";
    G4double boronMF  = 5*perCent;
    mDensity          = 0.963*(g/cm3);
    return BuildLoadedScintillator(symb, boronMF);  
  }else if (mProductName == "olsc-105")
  {
    mHydrogenAD = 1.02e+20*(1./cm3);
    mCarbonAD   = 3.15e+22*(1./cm3);
    G4double fluorineAD = 3.14e+22*(1./cm3);
    mDensity = 1.619*g/cm3;  
    G4double hMD = GetMDFromAD("H", mHydrogenAD);
    G4double cMD = GetMDFromAD("C", mCarbonAD);
    G4double fMD = GetMDFromAD("F", fluorineAD);
    
    G4double hMF = hMD/mDensity;
    G4double cMF = cMD/mDensity;
    G4double fMF = fMD/mDensity;
   
    mElementFracVec = { {"H", hMF}, {"C", cMF}, {"F", fMF} };
  
    ScintillatorBuilder builder(mProductName, 
                                mMacroFilePath,
                                mDensity,
                                mElementFracVec,
                                bEnableMPT
                                );
    mElementFracVec.clear();                            
    return builder.GetProduct(); 
        
  }else if (mProductName == "olsc-106")
  {
    mHydrogenAD = 4.04e+20*(1./cm3);
    mCarbonAD   = 4.06e+22*(1./cm3);
    mDensity    = 0.878*g/cm3;
    return BuildScintillator();
      
  }else if (mProductName == "olsc-107")
  {
    mHydrogenAD = 7.37e+22*(1./cm3);
    mCarbonAD   = 3.66e+22*(1./cm3);
    mDensity    = 0.86*g/cm3;
    return BuildScintillator();
     
  }else if (mProductName == "olsc-108")
  {
    mHydrogenAD = 7.03e+22*(1./cm3);
    mCarbonAD   = 3.72e+22*(1./cm3);
    mDensity    = 0.86*g/cm3;
    return BuildScintillator();
     
  }else if (mProductName == "olsc-109")
  {
    mHydrogenAD = 7.47e+22*(1./cm3);
    mCarbonAD   = 3.63e+22*(1./cm3);
    mDensity    = 0.85*g/cm3;
    return BuildScintillator();
     
  }else if (mProductName == "olsc-110")
  {
    mHydrogenAD = 6.48e+22*(1./cm3);
    mCarbonAD   = 3.83e+22*(1./cm3);
    mDensity    = 0.87*g/cm3;
    return BuildScintillator();
     
  }else if (mProductName == "olsc-111")
  {
    mHydrogenAD = 6.73e+22*(1./cm3);
    mCarbonAD   = 3.92e+22*(1./cm3);
    mDensity    = 0.954*g/cm3;
    return BuildScintillator();
     
  }else if (mProductName == "olsc-112")
  {
    mHydrogenAD       = 5.27e+22*(1./cm3);
    G4String symb     = "Gd";
    G4double gdMF     = 0.5*perCent;
    mDensity          = 0.90*(g/cm3);
    return BuildLoadedScintillator(symb, gdMF);
     
  }else if (mProductName == "olsc-113")
  {
    mHydrogenAD       = 6.16e+22*(1./cm3);
    G4String symb     = "Gd";
    G4double gdMF     = 0.25*perCent;
    mDensity          = 0.89*(g/cm3);
    return BuildLoadedScintillator(symb, gdMF);
   
  }else if (mProductName == "olsc-114")
  {
    mHydrogenAD = 5.32e+22*(1./cm3);
    mCarbonAD   = 3.23e+22*(1./cm3);
    G4double oxygenAD   = 1.14e+22*(1./cm3);
    mDensity = 1.036*g/cm3;  
    G4double hMD = GetMDFromAD("H", mHydrogenAD);
    G4double cMD = GetMDFromAD("C", mCarbonAD);
    G4double oMD = GetMDFromAD("O", oxygenAD);
    
    G4double hMF = hMD/mDensity;
    G4double cMF = cMD/mDensity;
    G4double oMF = oMD/mDensity;
    
    mElementFracVec = { {"H", hMF}, {"C", cMF}, {"O", oMF} };
  
    ScintillatorBuilder builder(mProductName, 
                                mMacroFilePath,
                                mDensity,
                                mElementFracVec,
                                bEnableMPT
                                );
    mElementFracVec.clear();                            
    return builder.GetProduct(); 
      
  }else if (mProductName == "olsc-200")
  {
    G4double labFraction   = 0.009977;
    G4double ppoFraction   = 2.3e-05;
    G4double waterFraction = 0.99;
    
    return BuildWbLS(labFraction, ppoFraction, waterFraction);
       
  }else if (mProductName == "olsc-202")         
  {
    G4double labFraction   = 0.029931;
    G4double ppoFraction   = 6.9e-05;
    G4double waterFraction = 0.97;
    
    return BuildWbLS(labFraction, ppoFraction, waterFraction);
      
  }else if (mProductName == "olsc-204")         
  {
    G4double labFraction   = 0.049885;
    G4double ppoFraction   = 0.000115;
    G4double waterFraction = 0.95;
    
    return BuildWbLS(labFraction, ppoFraction, waterFraction);   
    
  }else if (mProductName == "olsc-201")         
  { 
    G4double labFraction   = 0.009967;
    G4double ppoFraction   = 2.3e-05;
    G4double waterFraction = 0.98901;
    G4double gdFraction    = 0.001;
    
    return BuildLoadedWbLS(labFraction, 
                           ppoFraction, 
                           waterFraction, 
                           "G4_Gd",
                           gdFraction);
    
  }else if (mProductName == "olsc-203")         
  {   
    G4double labFraction   = 0.029901;
    G4double ppoFraction   = 6.9e-05;
    G4double waterFraction = 0.96903;
    G4double gdFraction    = 0.001;
    
    return BuildLoadedWbLS(labFraction, 
                           ppoFraction, 
                           waterFraction, 
                           "G4_Gd",
                           gdFraction); 
  }else if (mProductName == "opsc-400")
  {
    mHydrogenAD = 5.23e+22*(1./cm3);
    mCarbonAD   = 4.74e+22*(1./cm3);
    mDensity    = 1.032*g/cm3;
    return BuildScintillator();
    
  }
  
  else if (mProductName == "opsc-200" || mProductName == "opsc-201" || 
           mProductName == "opsc-300" )
  {
    mMaterial = G4NistManager::Instance()->
                FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    return BuildScntFromPredefinedMaterial();
  }
  
  else if(mProductName == "opsc-133")
  {
    EJ426Builder builder(mProductName, mMacroFilePath, bEnableMPT);
    return builder.GetProduct();
  }else
  {
    return nullptr;
  }
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OrganicScintillatorFactory* OrganicScintillatorFactory::GetInstance()
{
  static OrganicScintillatorFactory instance;
  
  if (mInstance == nullptr)
  {
    mInstance = &instance;
  }
    
  return mInstance;
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4String OrganicScintillatorFactory::GetStringAsLowerCase
(
  const G4String& str
)
{
  G4String temp = str;
  transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
  return temp;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double OrganicScintillatorFactory::GetMDFromAD
(
  const G4String& symb, 
  G4double ad
)
{
  G4double molarMass  = G4NistManager::Instance()->FindOrBuildElement(symb)->
                        GetAtomicMassAmu()*(g/mole);
                                    
  G4double massDensity = (ad/CLHEP::Avogadro)*molarMass;                                   
  
  return massDensity; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* OrganicScintillatorFactory::BuildScintillator()
{
  G4double hMD = GetMDFromAD("H", mHydrogenAD);
  G4double cMD = GetMDFromAD("C", mCarbonAD);
  
  //mDensity     = hMD+cMD; //if it is open, electron masses are ignored
  G4double hMF = hMD/mDensity;
  G4double cMF = cMD/mDensity;
  
  mElementFracVec = { {"H",hMF}, {"C", cMF} };
  
  ScintillatorBuilder builder(mProductName, 
                              mMacroFilePath,
                              mDensity,
                              mElementFracVec,
                              bEnableMPT
                              );
  mElementFracVec.clear();                           
  return builder.GetProduct();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* OrganicScintillatorFactory::BuildLoadedScintillator
(
  const G4String& symb, 
  G4double loadedElMF 
)
{
  G4double hMD = GetMDFromAD("H", mHydrogenAD);
  
  //mDensity     = hMD+cMD; #if it is open, electron masses are ignored
  G4double hMF = hMD / mDensity;
  G4double cMF = 1 - hMF - loadedElMF;
  
  /*
  { //for validity. check carbon and loaded element atom densitiy!
    G4double carbonMM = G4NistManager::Instance()->FindOrBuildElement("C")->
                        GetAtomicMassAmu()*(g/mole);
    
    G4double cAD = (mDensity*cMF/carbonMM)*CLHEP::Avogadro*cm3;
    G4cout<<"Carbon atom density (1/cm3): "<<cAD<<G4endl;
    
	  G4double loadedElMM = G4NistManager::Instance()->FindOrBuildElement(symb)
	                        ->GetAtomicMassAmu()*(g/mole);
	  
	  G4double loadedElAD = (mDensity*loadedElMF/loadedElMM)*
	                        CLHEP::Avogadro*cm3;
    
    if (symb == "B")
      loadedElAD = loadedElAD*0.199; //for B-10 isotope
     
	  G4cout<<symb <<" Atom density (1/cm3): "<<loadedElAD<<G4endl;
  }
  */
  
  mElementFracVec = { {"H", hMF}, {"C", cMF}, {symb, loadedElMF} };
  
  ScintillatorBuilder builder(mProductName, 
                              mMacroFilePath,
                              mDensity,
                              mElementFracVec,
                              bEnableMPT
                              );
  mElementFracVec.clear();                            
  return builder.GetProduct(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* OrganicScintillatorFactory::BuildWbLS
(
  G4double labFraction,
  G4double ppoFraction,
  G4double waterFraction  
)
{
  G4Material* lab = BuildLAB();
  G4Material* ppo = BuildPPO();

  G4Material* water = G4NistManager::Instance()->
                      FindOrBuildMaterial("G4_WATER");

  G4Material* mat = new G4Material(mProductName, 1.0*g/cm3, 3);
  mat->AddMaterial(lab, labFraction);
  mat->AddMaterial(ppo, ppoFraction);
  mat->AddMaterial(water, waterFraction);
  
  ScintillatorBuilder builder(mProductName,
                              mMacroFilePath,
                              mat,
                              bEnableMPT
                              );
  return builder.GetProduct();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* OrganicScintillatorFactory::BuildLoadedWbLS
(
  G4double labFraction,
  G4double ppoFraction,
  G4double waterFraction,
  const G4String& loadedMatName,
  G4double loadedMatFraction   
)
{
  
  G4Material* lab = BuildLAB();
  G4Material* ppo = BuildPPO();
  
  G4Material* water      = G4NistManager::Instance()->
                           FindOrBuildMaterial("G4_WATER");
  G4Material* loadedMat  = G4NistManager::Instance()->
                           FindOrBuildMaterial(loadedMatName);

  G4Material* mat = new G4Material(mProductName, 1.0*g/cm3, 4);
  mat->AddMaterial(lab, labFraction);
  mat->AddMaterial(ppo, ppoFraction);
  mat->AddMaterial(water, waterFraction);
  mat->AddMaterial(loadedMat, loadedMatFraction);

  ScintillatorBuilder builder(mProductName,
                              mMacroFilePath,
                              mat,
                              bEnableMPT
                             );
  return builder.GetProduct();    
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* OrganicScintillatorFactory::BuildPPO()
{
  G4NistManager* nistMan = G4NistManager::Instance();
  
  G4Material* ppo = new G4Material("PPO", 1.06*g/cm3, 4);
  ppo->AddElement(nistMan->FindOrBuildElement("C"), 0.8142);
  ppo->AddElement(nistMan->FindOrBuildElement("H"), 0.0501);
  ppo->AddElement(nistMan->FindOrBuildElement("N"), 0.0633);
  ppo->AddElement(nistMan->FindOrBuildElement("O"), 0.0723);
  
  return ppo;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* OrganicScintillatorFactory::BuildLAB()
{
  //Linear alkyl benzene (LAB)
  
  G4int nElements  = 2;
  G4double density = 0.867*g/cm3;
  
  G4NistManager* nistMan = G4NistManager::Instance();
  
  G4Material* C15H24 = new G4Material("C15H24",density,nElements);
  C15H24->AddElement(nistMan->FindOrBuildElement("H"), 24);
  C15H24->AddElement(nistMan->FindOrBuildElement("C"), 15);
  
  G4Material* C16H26 = new G4Material("C16H26",density,nElements);
  C16H26->AddElement(nistMan->FindOrBuildElement("H"), 26);
  C16H26->AddElement(nistMan->FindOrBuildElement("C"), 16);
  
  G4Material* C17H28 = new G4Material("C17H28",density,nElements);
  C17H28->AddElement(nistMan->FindOrBuildElement("H"), 28);
  C17H28->AddElement(nistMan->FindOrBuildElement("C"), 17);
  
  G4Material* C18H30 = new G4Material("C18H30",density,nElements);
  C18H30->AddElement(nistMan->FindOrBuildElement("H"), 30);
  C18H30->AddElement(nistMan->FindOrBuildElement("C"), 18);
  
  G4Material* C19H32 = new G4Material("C19H32",density,nElements);
  C19H32->AddElement(nistMan->FindOrBuildElement("H"), 32);
  C19H32->AddElement(nistMan->FindOrBuildElement("C"), 19);
  
  nElements = 5;
  G4Material* lab = new G4Material("LAB",density, nElements);
  lab->AddMaterial(C15H24, 0.012);
  lab->AddMaterial(C16H26, 0.204);
  lab->AddMaterial(C17H28, 0.432);
  lab->AddMaterial(C18H30, 0.334);
  lab->AddMaterial(C19H32, 0.018);
  
  return lab;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* OrganicScintillatorFactory::BuildScntFromPredefinedMaterial()
{
  ScintillatorBuilder builder(mProductName, 
                              mMacroFilePath,
                              mMaterial,
                              bEnableMPT
                              );
                                                                
  return builder.GetProduct(); 
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OrganicScintillatorFactory::PrintProducts()
{
  G4cout<<"----------OrganicScintillatorFactory products ----------"<<G4endl;
  for (auto product: mProductsSet)
  {
    G4cout<<product<<G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
