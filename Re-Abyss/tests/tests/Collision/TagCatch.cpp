#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/components/Actors/Commons/Collision/Tag.hpp>

namespace abyss::tests
{

    TEST_CASE("Collision Tag")
    {
        using namespace Actor::Collision;

        SECTION("tag visit success")
        {
            TagType tag = Tag::Attacker{} | Tag::Receiver{};

            int value = 0;
            auto result = tag.visit([&](Tag::Attacker) {
                value = 1;
            });

            REQUIRE(result);
            REQUIRE(value == 1);
        }

        SECTION("tag visit failed")
        {
            TagType tag = Tag::Receiver{};

            int value = 0;
            auto result = tag.visit([&](Tag::Attacker) {
                value = 1;
            });

            REQUIRE(!result);
            REQUIRE(value == 0);
        }
    }
}
#endif