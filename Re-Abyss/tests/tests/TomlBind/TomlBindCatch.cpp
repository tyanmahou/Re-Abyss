#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/TomlBind/TomlBind.hpp>

namespace abyss::tests
{
    struct Item
    {
        struct Pos
        {
            TOML_BIND_BEGIN;
            TOML_BIND_PARAM(x, "x")
            double x;
            TOML_BIND_PARAM(y, "y")
            double y;
            TOML_BIND_END;
        };
        TOML_BIND_BEGIN;

        TOML_BIND_PARAM(label, "label")
        String label;
        TOML_BIND_PARAM(pos, "pos")
        Pos pos;

        TOML_BIND_END;
    };
    struct Config
    {
        struct Window
        {
            TOML_BIND_BEGIN;

            TOML_BIND_PARAM(title, "title")
            String title;

            TOML_BIND_PARAM(width, "width")
            int32 width;

            TOML_BIND_PARAM(height, "height")
            int32 height;

            TOML_BIND_PARAM(sizable, "sizable")
            bool sizable;

            TOML_BIND_END;
        };

        TOML_BIND_BEGIN;

        TOML_BIND_PARAM(window, "Window")
        Window window;

        TOML_BIND_PARAM(sceneBackGround, "Scene.background")
        ColorF sceneBackGround;

        TOML_BIND_PARAM(values, "Array.values")
        Array<int32> values;

        TOML_BIND_PARAM(items, "Items")
        Array<Item> items;
        TOML_BIND_END;
    };

    TEST_CASE("TomlBind. Test")
    {
        TOMLReader  toml(U"tests/data/TomlBind/config.toml");

        Config config = TomlBinding<Config>(toml);

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