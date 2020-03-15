#pragma once
#if ABYSS_DO_TEST
namespace abyss::tests
{
    class TestRunner
    {
    public:
        TestRunner();
        ~TestRunner();
        bool run() const;
        void waitKey() const;
    };
}
#endif // ABYSS_DO_TEST