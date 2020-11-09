//
// Created by Sebastian Balz on 2/20/18.
//

#include <logging.h>
#include "gtest/gtest.h"


// make all private methods public
#define private public



int main(int argc, char **argv) {
    Log::setLogLevel(LogLevel::None, LogLevel::DebugL2);
    Log::advancedConf()->pintLogSrc(true);
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();


    return ret;
}

TEST(Shall_Not_Fail, init) {
    ASSERT_EQ(1, 1);
}
