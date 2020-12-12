#pragma once
#include <type_traits>
#include <memory>

namespace abyss::Actor
{
    namespace Tag
    {
        struct ITag
        {
            virtual ~ITag() = default;
        };
        template<class T>
        concept Tagged = std::is_base_of_v<ITag, T>;

        template<Tagged... Args>
        struct Tags : Args...
        {};

        /// <summary>
        /// 無効
        /// </summary>
        struct Invalid : virtual ITag {};

        /// <summary>
        /// 攻撃者
        /// </summary>
        struct Attacker : virtual ITag {};

        /// <summary>
        /// 受け身者
        /// </summary>
        struct Receiver : virtual ITag {};

        /// <summary>
        /// 味方
        /// </summary>
        struct Hero : virtual ITag {};

        /// <summary>
        /// プレイヤー
        /// </summary>
        struct Player : Hero, Receiver {};

        /// <summary>
        /// 敵
        /// </summary>
        struct Enemy : virtual ITag {};

        /// <summary>
        /// マップ
        /// </summary>
        struct Map : virtual ITag {};
        
        /// <summary>
        /// 床
        /// </summary>
        struct Floor : Map, Receiver {};

        /// <summary>
        /// はしご
        /// </summary>
        struct  Ladder : Map {};

        /// <summary>
        /// とおりぬけ床
        /// </summary>
        struct PenetrateFloor : Map {};

        /// <summary>
        /// ギミック
        /// </summary>
        struct Gimmick : virtual ITag {};

        /// <summary>
        /// トビラ
        /// </summary>
        struct Door : Gimmick {};


        template<Tagged T, Tagged U>
        constexpr auto operator |(const T&, const U&)
        {
            return Tags<T, U>{};
        }
        template<Tagged T, Tagged... Us>
        constexpr auto operator |(const T&, const Tags<Us...>&)
        {
            return Tags<T, Us...>{};
        }
        template<Tagged... Ts, Tagged U>
        constexpr auto operator |(const  Tags<Ts...>&, const U&)
        {
            return Tags<Ts..., U>{};
        }
        template<Tagged... Ts, Tagged... Us>
        constexpr auto operator |(const  Tags<Ts...>&, const Tags<Us...>&)
        {
            return Tags<Ts..., Us...>{};
        }
    }

    class TagType
    {
    public:
        TagType() :
            m_tag(std::make_unique <Tag::Invalid>())
        {}

        template<Tag::Tagged T>
        TagType([[maybe_unused]] const T&) :
            m_tag(std::make_unique<T>())
        {}

        template<Tag::Tagged T>
        bool is() const
        {
            if (!m_tag) {
                return false;
            }
            return dynamic_cast<T*>(m_tag.get()) != nullptr;
        }

        template<Tag::Tagged... T>
        bool anyOf() const
        {
            if (!m_tag) {
                return false;
            }
            return (... || (dynamic_cast<T*>(m_tag.get()) != nullptr));
        }

        template<Tag::Tagged... T>
        bool allOf() const
        {
            if (!m_tag) {
                return false;
            }
            return (... && (dynamic_cast<T*>(m_tag.get()) != nullptr));
        }

        template<Tag::Tagged T>
        bool isNot() const
        {
            return !is<T>();
        }
    private:
        std::unique_ptr<Tag::ITag> m_tag;
    };

}