#pragma once
#include <abyss/utils/Tag/Tag.hpp>

namespace abyss::Physics
{
    namespace Tag
    {
        using TagBase = ITag<struct PhysicsTagKind>;

        /// <summary>
        /// 無効
        /// </summary>
        struct Invalid : virtual TagBase {};

        /// <summary>
        /// 受け身者
        /// </summary>
        struct Receiver : virtual TagBase {};

        /// <summary>
        /// マップ
        /// </summary>
        struct Map : virtual TagBase {};

        /// <summary>
        /// 床
        /// </summary>
        struct Floor : Map, Receiver {};

        /// <summary>
        /// はしご
        /// </summary>
        struct Ladder : Map {};

        /// <summary>
        /// とおりぬけ床
        /// </summary>
        struct PenetrateFloor : Map {};

        using TagPtr = fixed_ptr<
            TagBase,

            Invalid,

            Receiver,

            Map,
            Floor,
            Ladder,
            PenetrateFloor
        >;
    }

    using TagType = abyss::TagType<Tag::TagPtr>;
}