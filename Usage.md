# FischertechnikSimulation
## Application Arguments

    StationSetup:
    <-s>        <--addStation>               : insert Station. This station gets insert before the last station (build reverse!)
    setup <stationKind> <unique stationName> <directionIn> <directionOut>
    <-cs>       <--currentSetup>             : print information about the current setup. Use "help --currentSetup"
    
    API:
    <-p>        <--port>                     : port for the api
    <-noAPI>    <-noAPI>                     : create no network api
    
    logging:
    <-lfn>      <--logFileName>              : change the fog file name
    <-l>        <--logLevel>                 : change the cli loglevel enum name <string> e.g -l Error
    <-lls>      <--logLevelSeparate>         : change the log level for cli and logfile separate to <string cli> <string file> e.g -lls Error DebugL3
    <-nh>       <--noHighlighting>           : disables the cli highlighting
    <-v>        <--version>                  : print build version
    
    utils:
    <-h>        <help>                       : help message or additional information's about an command e.g. "help <command>"


##Additional informations
### Section: StationSetup
#### --addStation
insert Station. This station gets insert before the last station (build reverse!)
setup <stationKind> <unique stationName> <directionIn> <directio
nOut>

with this command it is possible to define the simulation setup. There are 4 Station kinds: "conveyorbeltStation", "Mill
AndDrillStation", "PushStation" and the "BaseProductionStationto define a new setup is is necessary to the define the st
ations in reverse order for each station the command must be called with 4 arguments:
1. StationKind
2. an unique stationName
3. input direction (Up, Down, Left, Right)
4. output direction(Up, Down, Left, Right)


    short: -s
    long : --addStation

number of additional parameter: 4

allowed parameter:  conveyorbeltStation MillAndDrillStation PushStation BaseProductionStation
#### --currentSetup
print information about the current setup. Use "help --currentSetup"



    short: -cs
    long : --currentSetup

### Section: API
#### --port
port for the api

This command defines the port for the api to listen for requests

    short: -p
    long : --port

number of additional parameter: 1

#### -noAPI
create no network api

this command has the efect that the simulation does not create a api

    short: -noAPI
    long : -noAPI

### Section: logging
#### --logFileName
change the fog file name

This command defines to logfile name.

    short: -lfn
    long : --logFileName

number of additional parameter: 1

#### --logLevel
change the cli loglevel enum name <string> e.g -l Error

This command does adjust he amount of information that gets printed on the cli an and into the logfile.

    short: -l
    long : --logLevel

number of additional parameter: 1

allowed parameter:  None UserInfo CriticError Error Message Info Debug DebugL2 DebugL3
#### --logLevelSeparate
change the log level for cli and logfile separate to <string cli> <string file> e.g -lls Error DebugL3

This command does adjust he amount of information that gets printed on the cli an and into the logfile sperate.

    short: -lls
    long : --logLevelSeparate

number of additional parameter: 2

#### --noHighlighting
disables the cli highlighting



    short: -nh
    long : --noHighlighting

#### --version
print build version



    short: -v
    long : --version


#### --help
help message or additional information's about an command e.g. "help <command>"



    short: -h 
    long : help 