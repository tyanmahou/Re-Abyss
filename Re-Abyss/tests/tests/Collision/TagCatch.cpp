#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/modules/Actor/base/Tag.hpp>

namespace abyss::tests
{

    TEST_CASE("Collision Tag")
    {
        using namespace Actor;

        SECTION("tag is")
        {
            Actor::TagType tag = Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{};

            REQUIRE(tag.is<Tag::Attacker>());
            REQUIRE(tag.is<Tag::Receiver>());
            REQUIRE(!tag.is<Tag::Invalid>());
            REQUIRE(!tag.is<Tag::Player>());
        }

        SECTION("tag any of")
        {
            Actor::TagType tag = Tag::Attacker{} | Tag::Receiver{};

            REQUIRE(tag.anyOf<Tag::Attacker, Tag::Player>());
            REQUIRE(!tag.anyOf<Tag::Invalid, Tag::Player>());
        }

        SECTION("tag all of")
        {
            Actor::TagType tag = Tag::Attacker{} | Tag::Receiver{};

            REQUIRE(tag.allOf<Tag::Attacker, Tag::Receiver>());
            REQUIRE(!tag.allOf<Tag::Attacker, Tag::Player>());
        }

        SECTION("tag is not")
        {
            Actor::TagType tag = Tag::Attacker{} | Tag::Receiver{};

            REQUIRE(!tag.isNot<Tag::Attacker>());
            REQUIRE(!tag.isNot<Tag::Receiver>());
            REQUIRE(tag.isNot<Tag::Invalid>());
            REQUIRE(tag.isNot<Tag::Player>());
        }
    }
}
#endif