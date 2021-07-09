#pragma once
#include <abyss/utils/Tag/Tag.hpp>

namespace abyss::Actor
{
    namespace Tag
    {
        using TagBase = ITag<struct ActorTagKind>;

        /// <summary>
        /// 無効
        /// </summary>
        struct Invalid : virtual TagBase {};

        /// <summary>
        /// 攻撃者
        /// </summary>
        struct Attacker : virtual TagBase {};

        /// <summary>
        /// 受け身者
        /// </summary>
        struct Receiver : virtual TagBase {};

        /// <summary>
        /// 味方
        /// </summary>
        struct Hero : virtual TagBase {};

        /// <summary>
        /// プレイヤー
        /// </summary>
        struct Player : Hero, Receiver {};

        /// <summary>
        /// 敵
        /// </summary>
        struct Enemy : virtual TagBase {};

        /// <summary>
        /// マップ
        /// </summary>
        struct Map : virtual TagBase {};

        /// <summary>
        /// ギミック
        /// </summary>
        struct Gimmick : virtual TagBase {};

        /// <summary>
        /// アイテム
        /// </summary>
        struct Item : virtual TagBase {};

        using TagPtr = fixed_ptr<
            TagBase,
            
            Invalid,
            Attacker,
            Receiver,

            Hero,
            Player,

            Enemy,

            Map,

            Gimmick,

            Item
        >;
    }

    using TagType = abyss::TagType<Tag::TagPtr>;

}