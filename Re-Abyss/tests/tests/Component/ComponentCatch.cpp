#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/components/base/Components.hpp>

namespace
{
    using namespace abyss;
    class ITestInterface
    {
    public:
        virtual ~ITestInterface() = default;
    };

    class ComA : public IComponent
    {
        void setup([[maybe_unused]] Depends depends) override
        {

        }
    };
    class ComB : public IComponent
    {
        void setup([[maybe_unused]] Depends depends) override
        {
            depends.on<IComponent>().addBefore<ComA>();
        }
    };
    class ComC : 
        public IComponent,
        public ITestInterface
    {
        void setup([[maybe_unused]] Depends depends) override
        {
            depends.on<IComponent>().addAfter<ComA>();
            depends.on<IComponent>().addBefore<ComB>();
        }
    };
    class ComD : 
        public IComponent, 
        public ITestInterface
    {
        void setup([[maybe_unused]] Depends depends) override
        {
            depends.on<IComponent>().addBefore<ComA>();
            depends.on<ITestInterface>().addBefore<ComC>();
        }
    };
    class ComE :
        public IComponent,
        public ITestInterface
    {
        void setup([[maybe_unused]] Depends depends) override
        {
            depends.on<IComponent>().addBefore<ComB>();
            depends.on<IComponent>().addAfter<ComC>();
            depends.on<ITestInterface>().addAfter<ComD>();
            depends.on<ITestInterface>().addBefore<ComC>();
        }
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<ComC>
    {
        using Base = ITestInterface;
    };
    template<>
    struct ComponentTree<ComD>
    {
        using Base = ITestInterface;
    };
    template<>
    struct ComponentTree<ComE>
    {
        using Base = ITestInterface;
    };
}
namespace abyss::tests
{

    TEST_CASE("Component. Depends")
    {
        Components components;
        components.add(std::make_shared<ComA>());
        components.add(std::make_shared<ComB>());
        components.add(std::make_shared<ComC>());
        components.add(std::make_shared<ComD>());
        components.add(std::make_shared<ComE>());
        components.setup();

        SECTION("sort for all")
        {
            auto comps = components.finds<IComponent>();

            REQUIRE(comps.size() == 5);

            REQUIRE(dynamic_cast<ComD*>(comps[0].get()) != nullptr);
            REQUIRE(dynamic_cast<ComA*>(comps[1].get()) != nullptr);
            REQUIRE(dynamic_cast<ComC*>(comps[2].get()) != nullptr);
            REQUIRE(dynamic_cast<ComE*>(comps[3].get()) != nullptr);
            REQUIRE(dynamic_cast<ComB*>(comps[4].get()) != nullptr);
        }

        SECTION("sort for interface")
        {
            auto comps = components.finds<ITestInterface>();
            REQUIRE(comps.size() == 3);
            REQUIRE(dynamic_cast<ComD*>(comps[0].get()) != nullptr);
            REQUIRE(dynamic_cast<ComE*>(comps[1].get()) != nullptr);
            REQUIRE(dynamic_cast<ComC*>(comps[2].get()) != nullptr);
        }
    }
}
#endif