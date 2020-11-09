

#include <lib/SimpleLogging/include/logging.h>

int main(int argc, char *argv[])
{
    Log::advancedConf()->setCliHighLight(false);
    Log::setLogLevel(Info,DebugL2);

    Log::log("run event Loop",Info);
    return 0;

}

