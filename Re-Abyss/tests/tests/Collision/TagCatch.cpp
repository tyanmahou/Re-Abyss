#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/components/Actors/Commons/Collision/Tag.hpp>

namespace abyss::tests
{

    TEST_CASE("Collision Tag")
    {
        using namespace Actor::Collision;

        SECTION("tag is")
        {
            TagType tag = Tag::Attacker{} | Tag::Receiver{};

            REQUIRE(tag.is<Tag::Attacker>());
            REQUIRE(tag.is<Tag::Receiver>());
            REQUIRE(!tag.is<Tag::Invalid>());
            REQUIRE(!tag.is<Tag::Player>());
        }

        SECTION("tag is not")
        {
            TagType tag = Tag::Attacker{} | Tag::Receiver{};

            REQUIRE(!tag.isNot<Tag::Attacker>());
            REQUIRE(!tag.isNot<Tag::Receiver>());
            REQUIRE(tag.isNot<Tag::Invalid>());
            REQUIRE(tag.isNot<Tag::Player>());
        }
    }
}
#endif