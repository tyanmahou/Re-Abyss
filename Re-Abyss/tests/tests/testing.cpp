#if ABYSS_DO_TEST
#include "../helper/TestRunner/TestRunner.hpp"

void RunTest()
{
    abyss::tests::TestRunner runner;
    if (bool success = runner.run(); !success) {
        runner.waitKey();
    }
}

#endif ABYSS_DO_TEST