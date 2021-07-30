#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D.hpp>

namespace
{
    struct Item
    {
        struct Pos
        {
            [[TOML_BIND(x)]]
            double x;

            [[TOML_BIND(y)]]
            double y;
        };
        [[TOML_BIND(label)]]
        String label;

        [[TOML_BIND(pos)]]
        Pos pos;
    };
    struct Config
    {
        struct Window
        {
            [[TOML_BIND(title)]]
            String title;

            [[TOML_BIND(width)]]
            int32 width;

            [[TOML_BIND(height)]]
            int32 height;

            [[TOML_BIND(sizable)]]
            bool sizable;
        };

        [[TOML_BIND(window, "Window")]]
        Window window;

        [[TOML_BIND(sceneBackGround, "Scene.background")]]
        ColorF sceneBackGround;

        [[TOML_BIND(values, "Array.values")]]
        Array<int32> values;

        [[TOML_BIND(items, "Items")]]
        Array<Item> items;
    };
}
namespace abyss::tests
{
    TEST_CASE("utils::TomlBind. Test")
    {
        TOMLReader  toml(U"tests/data/TOMLBind/config.toml");

        Config config = TOMLBinding<Config>(toml);

        SECTION("test normal")
        {
            REQUIRE(config.sceneBackGround == ColorF(0.8, 0.9, 1.0));
        }
        SECTION("test nest bind")
        {
            REQUIRE(config.window.title == U"My application");
            REQUIRE(config.window.width == 800);
            REQUIRE(config.window.height == 600);
            REQUIRE(config.window.sizable == false);
        }
        SECTION("test array")
        {
            for (int i : step(1, 5)) {
                REQUIRE(config.values[i-1] == 10*i + i);
            }
        }
        SECTION("test table array")
        {
            REQUIRE(config.items[1].label == U"Ocean");
            REQUIRE(config.items[1].pos.x == 300.0);
            REQUIRE(config.items[1].pos.y == 200.0);
        }
    }
}
#endif