module;

#if ABYSS_DO_TEST
#define CATCH_CONFIG_RUNNER
#include <ThirdParty/Catch2/catch.hpp>
#include <Siv3D.hpp>
#endif // ABYSS_DO_TEST

export module abyss.tests.helper.TestRunner;

#if ABYSS_DO_TEST
export namespace abyss::tests
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

namespace abyss::tests
{

    TestRunner::TestRunner()
    {
        Console.open();
    }
    TestRunner::~TestRunner()
    {
    }

    bool abyss::tests::TestRunner::run() const
    {
        return Catch::Session().run() == 0;
    }

    void abyss::tests::TestRunner::waitKey() const
    {
        static_cast<void>(std::getchar());
    }

}

#endif // ABYSS_DO_TEST