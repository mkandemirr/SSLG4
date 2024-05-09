# SSLG4: A Novel Scintillator Simulation Library for Geant4 

With SSLG4, our goal is to enhance efficiency and accelerate progress in optical simulations within the Geant4 framework by simplifying scintillator handling and providing a rich repository of scintillators. SSLG4 enables users to quickly include predefined scintillator materials into their simulations without requiring manual definition. The library stores optical data of scintillators in ASCII files with .mac and .txt extensions, allowing users to add, remove, or modify properties of scintillators at runtime of their applications.

SSLG4 encompasses a diverse range of scintillators, including both organic and inorganic types, commonly utilized in high-energy and nuclear physics experiments. Currently, the library comprises 68 scintillators, including 58 organic and 10 inorganic types. The majority of these scintillators are sourced from the catalogs of prominent scintillator manufacturers such as Eljen and Luxium. Other scintillators are included based on their widespread usage across various physics domains.

The below table presents a complete list of the scintillators available in the library. Each scintillator in the library is assigned a unique code, as shown in the last column of the table. Users should utilize these codes to access their desired scintillators in their Geant4 applications.

| Type            | Identification                     | Name                        | Simulation Code (SC) |
|:----------------|:-----------------------------------|:----------------------------|:---------------------|
| Organic Plastic | Eljen Technology /Luxium Solutions | EJ-200/Pilot F/BC-408       | OPSC-100             |
|                 |                                    | EJ-204/NE -104/BC-404       | OPSC-101             |
|                 |                                    | EJ-208/NE -110 /BC-412      | OPSC-102             |
|                 |                                    | EJ-212/NE-102A/BC-400       | OPSC-103             |
|                 |                                    | EJ-214                      | OPSC-104             |
|                 |                                    | EJ-228/Pilot U/BC-418       | OPSC-105             |
|                 |                                    | EJ-230/Pilot U2/BC-420      | OPSC-106             |
|                 |                                    | EJ-232/NE-111A/BC-422       | OPSC-107             |
|                 |                                    | EJ-232Q-0.5                 | OPSC-108             |
|                 |                                    | EJ-232Q-1.0                 | OPSC-109             |
|                 |                                    | EJ-232Q-2.0                 | OPSC-110             |
|                 |                                    | EJ-232Q-3.0                 | OPSC-111             |
|                 |                                    | EJ-232Q-5.0                 | OPSC-112             |
|                 |                                    | EJ-240/NE-115/BC-444        | OPSC-113             |
|                 |                                    | EJ-244/BC-440               | OPSC-114             |
|                 |                                    | EJ-244M/BC-440M             | OPSC-115             |
|                 |                                    | EJ-248/BC-448               | OPSC-116             |
|                 |                                    | EJ-248M                     | OPSC-117             |
|                 |                                    | EJ-254-1pct                 | OPSC-118             |
|                 |                                    | EJ-254-2.5pct               | OPSC-119             |
|                 |                                    | EJ-254-5pct                 | OPSC-120             |
|                 |                                    | EJ-256-1.5pct               | OPSC-121             |
|                 |                                    | EJ-256-5pct                 | OPSC-122             |
|                 |                                    | EJ-260/NE-103/BC-428        | OPSC-123             |
|                 |                                    | EJ-262                      | OPSC-124             |
|                 |                                    | EJ-276D                     | OPSC-125             |
|                 |                                    | EJ-276G                     | OPSC-126             |
|                 |                                    | EJ-280                      | OPSC-127             |
|                 |                                    | EJ-282                      | OPSC-128             |
|                 |                                    | EJ-284                      | OPSC-129             |
|                 |                                    | EJ-286                      | OPSC-130             |
|                 |                                    | EJ-290/BC-490/NE-120        | OPSC-131             |
|                 |                                    | EJ-296/BC-498               | OPSC-132             |
|                 |                                    | EJ-426                      | OPSC-133             |
|                 | Nuviatech Instruments              | SP-32                       | OPSC- 200            |
|                 |                                    | SP-33                       | OPSC- 201            |
|                 | Hangzhou Shalom EO                 | SP-102                      | OPSC- 300            |
|                 | Rexon Components                   | RP-408                      | OPSC-400             |
| Organic Liquid  | Eljen Technology                   | EJ-301/NE-213/BC-501A       | OLSC-100             |
|                 |                                    | EJ-309                      | OLSC-101             |
|                 |                                    | EJ-309B-1pct                | OLSC-102             |
|                 |                                    | EJ-309B-2.5pct              | OLSC-103             |
|                 |                                    | EJ-309B-5pct                | OLSC-104             |
|                 |                                    | EJ-313/NE-226/BC-509        | OLSC-105             |
|                 |                                    | EJ-315-H/BC-537/NE-230      | OLSC-106             |
|                 |                                    | EJ-321H                     | OLSC-107             |
|                 |                                    | EJ-321L                     | OLSC-108             |
|                 |                                    | EJ-321P                     | OLSC-109             |
|                 |                                    | EJ-321S                     | OLSC-110             |
|                 |                                    | EJ-325A                     | OLSC-111             |
|                 |                                    | EJ-331-0.5pct/NE-323/BC-521 | OLSC-112             |
|                 |                                    | EJ-335-0.25pct/BC-525       | OLSC-113             |
|                 |                                    | EJ-351/NE-220/BC-573        | OLSC-114             |
|                 | HEP Materials (Neutrino Studies)   | WbLS-1pct                   | OLSC- 200            |
|                 |                                    | WbLS-1pct-gd-0.1pct         | OLSC- 201            |
|                 |                                    | WbLS- 3pct                  | OLSC- 202            |
|                 |                                    | WbLS- 3pct-gd-0.1pct        | OLSC- 203            |
|                 |                                    | WbLS-5pct                   | OLSC- 204            |
| Inorganic       | Advatech                           | BaF2                        | ISC-1000             |
|                 |                                    | CdWO4                       | ISC-1001             |
|                 | Luxium Solutions                   | BGO                         | ISC- 2000            |
|                 |                                    | CsINa                       | ISC- 2001            |
|                 |                                    | CsITI                       | ISC- 2002            |
|                 |                                    | LYSOCe                      | ISC- 2003            |
|                 |                                    | NaITI                       | ISC- 2004            |
|                 | HEP Materials (Noble gases)        | LAr                         | ISC- 3000            |
|                 |                                    | LXe                         | ISC- 3001            |
|                 |                                    | PbWO4                       | ISC- 3002            |


The following code snippet demonstrates how to get a scintillator from SSLG4:

```cpp
int main()
{
  G4bool isMPTOn = true;//MPT = MaterialPropertiesTable
  //Getting an organic scintillator object 
  G4String osCode = "OPSC-100"; 
  G4Material* scntMat1 = OrganicScintillatorFactory::GetInstance()->Get(osCode, isMPTOn);
  //Getting an inorganic scintillator object
  G4String isCode = "ISC-1000";
  G4Material* scntMat2 = InorganicScintillatorFactory::GetInstance()->Get(isCode, isMPTOn);
}
```

In addition, we made all the scintillator data available in the library on a dedicated page of our website to ensure convenient access for all users: https://neutrino.erciyes.edu.tr/SSLG4/ 
             
## The package structure:   

_SSLG4_: This is the root directory where all the files related to SSLG4 are located. 

_SSLG4/include_: This directory includes C++ header files for SSLG4.

_SSLG4/src_: This directory includes C++ source files for SSLG4.

_SSLG4/macros_: This directory contains macro files (files with a .mac extension) containing user interface commands for users. These files also store energy-independent properties of the scintillators. There is a macro file corresponding to each scintillator in SSLG4. These files enable users to add, remove, or modify properties of scintillators at runtime of their applications. 

_SSLG4/macros/oscnt_: This directory includes macro files for organic scintillators.

_SSLG4/macros/iscnt_: This directory includes macro files for inorganic scintillators.

_SSLG4/data_: This directory contains all the energy-dependent properties of the scintillators included in SSLG4. There is a directory for each scintillator, and each scintillator's data is collected within its respective directory. Under each scintillator directory, there are as many txt files as there are properties defined for that scintillator. These files store energy-dependent properties in two columns, listing energy-value or wavelength-value pairs.

_SSLG4/data/oscnt_: This directory contains energy-dependent data for organic scintillators. 

_SSLG4/data/iscnt_: This directory contains energy-dependent data for inorganic scintillators.

_testSSLG4Ex_: This directory includes a Geant4 application developed to test whether the properties of scintillators defined in SSLG4 are accurately transferred to the Geant4 system. The application is entirely controlled by a macro file named _run.mac_, which contains various simulation settings. These settings include scintillator selection, primary particle control, toggling optical physics processes on and off, controlling critical optical parameters, and specifying the simulation output file type. The application outputs the following physics quantities in n-tuple format on an event-by-event basis: 

* Event ID
* Wavelength and energy spectrum of emitted photons.  
* Photon emission time spectrum. 
* Number of emitted scintillation photons. 
* Number of emitted cherenkov photons. 
* Total energy deposited. This parameter is included for confirmation, as the number of photons emitted depends on the deposited energy.

As these quantities are retrieved from the Geant4 kernel during the simulation stage and are generated based on the scintillator data provided by SSLG4, they can be used, in a sense, to check the proper functioning of the SSLG4 system.

## Tested on 

1. **Linux (Ubuntu 22.04.2 LTS)**
   - Architecture: x86_64
   - Compiler: GCC 11.3.0
   - Geant4 Version: 11.1.1

2. **macOS (Sonoma 14.4.1)**
   - Architecture: arm64
   - Compiler: Apple clang version 15.0.0
   - Geant4 Version: 11.2.1

## How to use SSLG4 in a Geant4 application? 

Copy the _sslg4_ directory to the project source directory, where your CMakeList.txt file is located. Since SSLG4 depends on [OPSim](https://github.com/mkandemirr/OPSim.git), you should also copy the _OPSim_ directory into your project source directory. Then add the following three lines of code to the appropriate place of your _CMakeList.txt_ file (for help, you can examine the _CMakeList.txt_ files in the provided _textSSLG4Ex_ application). 

Before the executable target is created:

```cmake	
   add_subdirectory(OPSim) 
   add_subdirectory(sslg4)
```
After the executable target is created:

```cmake	
   target_link_libraries(yourExecutableTarget OPSim sslg4 ${Geant4_LIBRARIES} )
```
## How to run the provided "testSSLG4Ex" application?   
  
1. Go to the directory where you installed the testSSLG4Ex directory in your system.

```bash	
   cd path/To/example
```
2. Create a directory named testSSLG4Ex-build in the same directory as testSSLG4Ex. 

```bash
   mkdir testSSLG4Ex-build
```
3. Now go inside this build directory and run CMake to generate the Makefiles needed to build the application. Two arguments are 
passed to CMake. The first argument to CMake is the path to the source directory that includes the CMakeList.txt file. The second argument is the path to the build directory where the generated make files will be located. CMake will now run to configure the build and generate Makefiles.

```bash
   cd testSSLG4Ex-build
   cmake -S ../testSSLG4Ex -B .
```
4. With the Makefile available, you can now build by simply running make: 
```bash
   make  
```
5. The application is now ready to run. If you now list the contents of your build directory, you will notice that the executable main has been created. The program can be executed in two modes: interactive and batch. To run in an interactive mode:
```bash
   ./main
```
6. To run in batch mode:

```bash
   ./main run.mac
```
## Contacts 

If you have any questions or wish to notify of updates and/or modifications please contact: \
Mustafa Kandemir (mustafa.kandemir@erdogan.edu.tr)


