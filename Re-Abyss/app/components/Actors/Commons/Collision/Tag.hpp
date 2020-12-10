#pragma once
#include <type_traits>
#include <memory>
#include <abyss/utils/Visitor.hpp>

namespace abyss::Actor::Collision
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
        struct Tags : virtual Args...
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
        /// プレイヤー
        /// </summary>
        struct Player : virtual ITag {};

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
        struct Floor : virtual Map, virtual Receiver {};

        /// <summary>
        /// はしご
        /// </summary>
        struct  Ladder : virtual Map {};

        /// <summary>
        /// とおりぬけ床
        /// </summary>
        struct PenetrateFloor : virtual Map {};

        /// <summary>
        /// ギミック
        /// </summary>
        struct Gimmick : virtual ITag {};

        /// <summary>
        /// トビラ
        /// </summary>
        struct Door : virtual Gimmick {};


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

        namespace detail
        {
            using TagVisitorBase = ConstVisitor<
                Invalid,

                Attacker,
                Receiver,

                Player,

                Enemy,

                Map,
                Floor,
                Ladder,
                PenetrateFloor,

                Gimmick,
                Door
            >;
        }

        struct TagVisitor : detail::TagVisitorBase
        {
            using detail::TagVisitorBase::Visitor;
            using detail::TagVisitorBase::visit;
            using detail::TagVisitorBase::operator=;
        };

    }

    class TagType
    {
        struct Base
        {
            virtual ~Base() = default;
            virtual bool accept(const Tag::TagVisitor& visitor) const = 0;
        };

        template<Tag::Tagged T>
        struct Wrap final : Base
        {
            bool accept(const Tag::TagVisitor& visitor) const final
            {
                return visitor.visit(T{});
            }
        };
        template<Tag::Tagged... Ts>
        struct Wrap<Tag::Tags<Ts...>> final : Base
        {
            bool accept(const Tag::TagVisitor& visitor) const final
            {
                Tag::Tags<Ts...> tag;
                return (visitor.visit(static_cast<Ts&>(tag)) || ...);
            }
        };
    public:
        TagType() = default;
        template<Tag::Tagged T>
        TagType([[maybe_unused]] const T&) :
            m_tag(std::make_unique<Wrap<T>>())
        {}
        bool accept(const Tag::TagVisitor& visitor) const
        {
            if (!m_tag) {
                return false;
            }
            return m_tag->accept(visitor);
        }
        template<Tag::Tagged T>
        bool is()
        {
            return this->accept([]([[maybe_unused]] const T& tag) {

            });
        }
        template<Tag::Tagged T>
        bool isNot()
        {
            return !is<T>();
        }
    private:
        std::unique_ptr<Base> m_tag;
    };

}