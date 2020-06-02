export module abyss.tests;

#if ABYSS_DO_TEST
import :helper.TestRunner;

namespace abyss::tests
{
    export void RunTest()
    {
        TestRunner runner;
        if (bool success = runner.run(); !success) {
            runner.waitKey();
        }
    }
}

#endif ABYSS_DO_TEST
