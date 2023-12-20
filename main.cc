//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file main.cc
/// \brief Main program of the coincidence event

#include "iostream"

//config and log
#include "yaml-cpp/yaml.h"
//#include "spdlog/spdlog.h"
//#include "spdlog/sinks/stdout_color_sinks.h"

//random stuff
#include "Randomize.hh"
#include "random"

//G4 includes
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "QBBC.hh"
//#include "ActionInitialization.hh"
//
//#include "G4UImanager.hh"
//#include "FTFP_BERT.hh"
//#include "G4StepLimiterPhysics.hh"
//
//#include "G4VisExecutive.hh"
//#include "time.h"
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int main(int argc,char** argv)
{

    /*
    // create a color multi-threaded logger
    auto console = spdlog::stdout_color_mt("console");    
    auto err_logger = spdlog::stderr_color_mt("stderr");    

    // Example of ANSI color codes
    const std::string red = "\033[31m";
    const std::string reset = "\033[0m";

    //spdlog::get("console")->info("Normal text {}red text{} normal text", red, reset);
    */

    if (argc != 3) {
        std::cerr << "Wrong input arguments! The right way is: ./main [config/config.yaml] [config/optical_property.yaml]";
    return -1;
    }

    // load config
    char* fileConfig= argv[1];
    YAML::Node rootNode = YAML::LoadFile(fileConfig);

    char* opticalConfig = argv[2];

    //spdlog::get("console")->info("Load config files {}{}{} and {}{}{}", red, fileConfig, reset, red, opticalConfig, reset);

    // set random seed
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
    std::random_device se;
    CLHEP::HepRandom::setTheSeed(se());

    // invoke G4
    //spdlog::get("console")->info("Invoke Geant4 run manager");
    G4RunManager* runManager = new G4RunManager;

    G4UIExecutive* ui = nullptr;
    ui = new G4UIExecutive(argc, argv); 

    // Set mandatory initialization classes
    auto physicsList = new QBBC;
    runManager->SetUserInitialization(new DetectorConstruction(fileConfig, opticalConfig));
    runManager->SetUserInitialization(new PhysicsList());

    bool bsession=true;
    G4VisManager* visManager=NULL;
    auto UImanager = G4UImanager::GetUIpointer();

    if (bsession)
      {
        // visualization manager
        visManager = new G4VisExecutive(argc, argv);
        visManager->Initialize();
        visManager->SetVerboseLevel("quiet");
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;

      }

    if (visManager)
      {
        delete visManager;
      }
    /*
    // Set user action classes
    runManager->SetUserInitialization(new ActionInitialization());

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/tracking/verbose 0");
    UImanager->ApplyCommand("/run/verbose      0");
    UImanager->ApplyCommand("/control/verbose  0");
    UImanager->ApplyCommand("/analysis/verbose 0");
    UImanager->ApplyCommand("/event/verbose    0");
    UImanager->ApplyCommand("/process/verbose  0");
    runManager->Initialize(); 

    G4long beamon =rootNode["BeamOn"].as<long>();
    runManager->BeamOn(beamon);
    delete runManager;

    G4RunManager* runManager = new KM3RunManager;

    // set mandatory initialization classes
    K40DetectorConstruction* Detector = new K40DetectorConstruction;
    Detector->SetOrientationTheta (90* deg );
    runManager->SetUserInitialization(Detector);
    runManager->SetUserInitialization(new KM3PhysicsList);

    KM3PrimaryGeneratorAction* PGA=new KM3PrimaryGeneratorAction;
    PGA->SetProducingVolumeRadius(Detector->GetTargetFullLength ());

    // set mandatory user action class
    runManager->SetUserAction(new KM3PrimaryGeneratorAction);
    runManager->SetUserAction(new KM3RunAction);
    runManager->SetUserAction(new KM3EventAction);
    runManager->SetUserAction(new KM3SteppingAction);

    G4UIsession* session=0;

    // get the pointer to the User Interface manager
    G4UImanager* UI = G4UImanager::GetUIpointer();
    G4String command = "/control/execute ";

    if (session)   // Define UI session for interactive mode.
      {
        UI->ApplyCommand(command+MacFileName);
        session->SessionStart();
        delete session;
      }
    else           // Batch mode
      {
        UI->ApplyCommand(command+MacFileName);
        //session->SessionStart ();
      }

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-17*2.54/2,17*2.54/2);
    */

    delete runManager;
    return 0;

}

