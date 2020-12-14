#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <Emaject.hpp>

using namespace emaject;

namespace
{
    class ICountUp
    {
    public:
        virtual int countUp() = 0;
    };
    class CountUp : public ICountUp
    {
    public:
        CountUp() = default;

        int countUp()
        {
            return ++a;
        }
    private:
        int a = 0;
    };

    class CountUpInstaller : public IInstaller
    {
    public:
        void onBinding(Container* c) const
        {
            c->bind<ICountUp>()
                .to<CountUp>()
                .asCache();

            c->bind<ICountUp, 1>()
                .to<CountUp>()
                .asTransient();
        }
    };
    class SampleCounter
    {
    public:
        SampleCounter() = default;

        int countUp()
        {
            if (!m_countUp) {
                return -1;
            }
            return m_countUp->countUp();
        }
    private:

        [[INJECT(m_countUp)]]
        std::shared_ptr<ICountUp> m_countUp;
    };
    class SampleCounter2
    {
    public:
        SampleCounter2() = default;

        int countUp()
        {
            if (!m_countUp) {
                return -1;
            }
            return m_countUp->countUp();
        }
    private:

        [[INJECT(m_countUp, 1)]]
        std::shared_ptr<ICountUp> m_countUp;
    };

    class CtorSampleCounter
    {
    public:
        INJECT_CTOR(CtorSampleCounter(std::shared_ptr<ICountUp> countUp)):
            m_countUp(countUp)
        {}

        int countUp()
        {
            if (!m_countUp) {
                return -1;
            }
            return m_countUp->countUp();
        }
    private:
        std::shared_ptr<ICountUp> m_countUp;
    };
}


namespace abyss::tests
{
    TEST_CASE("Di. Test")
    {
        SECTION("test cache")
        {
            Injector injector;
            injector.install<CountUpInstaller>();

            {
                auto sample = injector.resolve<SampleCounter>();
                REQUIRE(sample->countUp() == 1);
            }
            {
                auto sample = injector.resolve<SampleCounter>();
                REQUIRE(sample->countUp() == 2);
            }
        }
        SECTION("test Transient")
        {
            Injector injector;
            injector.install<CountUpInstaller>();

            {
                auto sample = injector.resolve<SampleCounter2>();
                REQUIRE(sample->countUp() == 1);
            }
            {
                auto sample = injector.resolve<SampleCounter2>();
                REQUIRE(sample->countUp() == 1);
            }
        }
        SECTION("test ctor inject")
        {
            Injector injector;
            injector.install<CountUpInstaller>();

            {
                auto sample = injector.resolve<CtorSampleCounter>();
                REQUIRE(sample->countUp() == 1);
            }
            {
                auto sample = injector.resolve<CtorSampleCounter>();
                REQUIRE(sample->countUp() == 2);
            }
        }
    }
}
#endif