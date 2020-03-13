#include "../helper/TestRunner/TestRunner.hpp"

void RunTest()
{
    abyss::tests::TestRunner runner;
    if (bool success = runner.run(); !success) {
        runner.waitKey();
    }
}
