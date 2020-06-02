export module abyss.tests;

#if ABYSS_DO_TEST
import abyss.tests.helper.TestRunner;

export namespace abyss::tests
{
    void RunTest()
    {
        TestRunner runner;
        if (bool success = runner.run(); !success) {
            runner.waitKey();
        }
    }
}

#endif ABYSS_DO_TEST