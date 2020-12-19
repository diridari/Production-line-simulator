//
// Created by basti on 19.12.2020.
//
#include <iostream>
#include <logging.h>
#include "ArgumentCallbackFunctions.h"
#include "version.h"
#include <sstream>

using namespace std;



int port = 5555;
bool generateAPI = true;
bool cliHighlighting = true;
BaseProductionStation *newStartStation = nullptr;


int callBackPort(int i, char **buff) {
    i++;
    port = atoi(buff[i]);
    Log::log("Parsed argument : port " + to_string(port), Message);
    return i;
}

int callBackNoAPI(int i, char **buff) {
    i++;
    port = atoi(buff[i]);
    Log::log("Parsed argument : port " + to_string(port), Message);
    return i;
}


int callBackLogFileName(int i, char *buff[]) {
    i++;
    Log::setLogFileName(buff[i]);
    return i;
}

int callBackLogLogLevel(int i, char *buff[]) {
    i++;
    Log::setLogLevel(buff[i]);
    return i;
}

int callBackLogLogLevelSeperat(int i, char *buff[]) {
    i++;
    Log::setLogLevel(buff[i], buff[i + 1]);
    return ++i;
}

static  Direction StringToDirection(string direction){
    Direction ret = Direction::noDirection;
    if(direction=="Up")
        ret = Direction::directionUp;
    else if (direction=="Down")
        ret = Direction::directionDown;
    else if (direction=="Left")
        ret = Direction::directionLeft;
    else if (direction=="Right")
        ret = Direction::directionRight;
    else{
        Log::log("could not parse direction: " + direction,Error);
    }
    return ret;
}


int insertStation(int i, char *buff[]){
    Log::log("insert new station by argument",Info);
    i++;
    string stationKind = buff[i];
    string stationName = buff[i+1];
    string inDir = buff[i+2];
    string outDir = buff[i+3];
    BaseProductionStation *s;
    //conveyorbeltStation","MillAndDrillStation","PushStation","BaseProductionStation"
    if(stationKind == "conveyorbeltStation"){
        s = new conveyorbeltStation(newStartStation,stationName);
    }else if(stationKind == "MillAndDrillStation"){
        s = new MillAndDrillStation(newStartStation,stationName);
    }else if(stationKind == "PushStation"){
        s = new PushStation(newStartStation,stationName);
    }else if(stationKind == "BaseProductionStation"){
        s = new BaseProductionStation(newStartStation,stationName);
    }else{
        Log::log("insert unknow station",Error);
    }
    s->setDirection(StringToDirection(inDir),StringToDirection(outDir));
    newStartStation = s;


    return i+3;

}

argvParser *initProgramArguments() {
    string desc = "This application intense to simulate the \"Fischertechnik-Productionline\". \r\n"
                  "This simulation was created during the Corona crisis to enable the students of the University of Applied Sciences Munich to attend the work placement  for the lecture \"Embedded Systems\". \r\n"
                  "The goal of the practical course is to control the sensors and actuators of the production line on a binary level with the help of an embedded system.\r\n"
                  "This simulation is therefore controlled on the level of the individual sensors and actuators. \r\n"
                  "For the interaction there are two different ways:\r\n"
                  "\t* In the same process: Here the internal interface can be used.\r\n"
                  "\t* Via the network: The individual sensors and actuators can be described and read out via the network.\r\n"
                  "\r\n"
                  "In the Section \"StationSetup\" are some commands to define the station setup. Here it is necessary to start with the last station";

    Log::advancedConf()->pintLogSrc(true);

    argvParser *p = new argvParser("FischertechnikSimulation", desc, true, "%#");
    p->checkForDefaulConfigFilesIn("simConf", "~/ ./ ../");

p->addSection("StationSetup");
    p->addArg("-s","--addStation","insert Station. This station gets insert before the last station (build reverse!)  \r\n \t\t\t\t"
                                  "setup <stationKind> <unique stationName> <directionIn> <directionOut>",insertStation)->numberOfParameter(4)->allowedParameter(4,"conveyorbeltStation","MillAndDrillStation","PushStation","BaseProductionStation")
                                  ->addAdditionalHelp(R"(with this command it is possible to define the simulation setup. There are 4 Station kinds: "conveyorbeltStation", "MillAndDrillStation", "PushStation" and the "BaseProductionStation)"
                                                      "to define a new setup is is necessary to the define the stations in reverse order for each station the command must be called with 4 arguments:\r\n"
                                                      "1. StationKind \r\n2. an unique stationName\r\n 3. input direction (Up, Down, Left, Right)\r\n 4. output direction(Up, Down, Left, Right)");

// API
    p->addSection("API");
    p->addArg("-p", "--port", "port for the api", callBackPort)->numberOfParameter(1)
            ->addAdditionalHelp("This command defines the port for the api to listen for requests");
    p->addArg("-noAPI","-noAPI","create no network api",callBackNoAPI)->numberOfParameter(0)
            ->addAdditionalHelp("this command has the efect that the simulation does not create a api");


// Logging
    p->addSection("logging");
    // This command defines to logfile name.
    p->addArg("-lfn", "--logFileName", "change the fog file name ", callBackLogFileName)->numberOfParameter(1)
            ->addAdditionalHelp("This command defines to logfile name.");
    // This command does adjust he amount of information that gets printed on the cli an and into the logfile.
    p->addArg("-l", "--logLevel", "change the cli loglevel enum name <string> e.g -l Error ", callBackLogLogLevel)
            ->allowedParameter(9, "None", "UserInfo", "CriticError", "Error", "Message", "Info", "Debug", "DebugL2","DebugL3")->numberOfParameter(1)
            ->addAdditionalHelp("This command does adjust he amount of information that gets printed on the cli an and into the logfile.");
    p->addArg("-lls", "--logLevelSeparate",
              "change the log level for cli and logfile separate to <string cli> <string file> e.g -lls Error DebugL3", callBackLogLogLevelSeperat)->numberOfParameter(2)
            ->addAdditionalHelp("This command does adjust he amount of information that gets printed on the cli an and into the logfile sperate.");
    p->addArg("-nh", "--noHighlighting", "disables the cli highlighting ", [] {
        Log::advancedConf()->setCliHighLight(false);
        cliHighlighting = false;
    });

    p->addArg("-v","--version","print build version",[]{cout <<"gdbManipulator version: "<< VERSION_MAJOR<<"."<<VERSION_MINOR<<"."<<VERSION_REVISION<<endl; });


    return p;
}

string getOsName()
{
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __unix || __unix__
    return "Unix";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#else
    return "Other OS ";
#endif
}


void logArgumentStatus(){
    ostringstream s;
    s<< "\nFischertechnik Produktionline simulation:\r\n\tVersion: "<< VERSION_MAJOR<<"."<<VERSION_MINOR<<"."<<VERSION_REVISION<<endl;
    s<< "\tCreateAPI                : "<< generateAPI<<endl;
    s<< "\tAPI port                 : "<< port<<endl;;
    s<< "\tcli highlighting         : "<< cliHighlighting  <<endl;
    s<< "\tsimulation is running on : " << getOsName() <<endl<<endl;

    Log::log("\n"+s.str(),Message);
}