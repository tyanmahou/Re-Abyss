#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/Tag/Tag.hpp>

namespace
{
    using namespace abyss;

    namespace Tag
    {
        using TagBase = ITag<struct TestTagKind>;
        struct Invalid : virtual TagBase {};
        struct Attacker : virtual TagBase {};
        struct Receiver : virtual TagBase {};
        struct Player : virtual TagBase {};
        struct Enemy : virtual TagBase {};

        using TagPtr = fixed_ptr<
            TagBase,

            Invalid,

            Attacker,
            Receiver,

            Player,
            Enemy
        >;
    }
    using TagType = abyss::TagType<Tag::TagPtr>;
}
namespace abyss::tests
{
    using TagType = ::TagType;

    TEST_CASE("Collision Tag")
    {
        SECTION("tag is")
        {
            TagType tag = Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{};

            REQUIRE(tag.is<Tag::Attacker>());
            REQUIRE(tag.is<Tag::Receiver>());
            REQUIRE(!tag.is<Tag::Invalid>());
            REQUIRE(!tag.is<Tag::Player>());
        }

        SECTION("tag any of")
        {
            TagType tag = Tag::Attacker{} | Tag::Receiver{};

            REQUIRE(tag.anyOf<Tag::Attacker, Tag::Player>());
            REQUIRE(!tag.anyOf<Tag::Invalid, Tag::Player>());
        }

        SECTION("tag all of")
        {
            TagType tag = Tag::Attacker{} | Tag::Receiver{};

            REQUIRE(tag.allOf<Tag::Attacker, Tag::Receiver>());
            REQUIRE(!tag.allOf<Tag::Attacker, Tag::Player>());
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