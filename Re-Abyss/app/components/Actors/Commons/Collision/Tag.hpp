#pragma once
#include <type_traits>
#include <memory>
#include <abyss/utils/Visitor.hpp>

namespace abyss::Actor::Collision
{
    namespace Tag
    {
        namespace detail
        {
            struct ITag
            {
                virtual ~ITag() = default;
            };
            template<class T>
            concept Tagged = std::is_base_of_v<detail::ITag, T>;

            template<Tagged... Args>
            struct Tags : virtual Args...
            {};

            template<class T>
            struct IsTags : std::false_type{};

            template<class... Args>
            struct IsTags<Tags<Args...>> : std::true_type {};
        }

        template<detail::Tagged T, detail::Tagged U>
        constexpr auto operator |(const T&, const U&)
        {
            return detail::Tags<T, U>{};
        }
        template<detail::Tagged T, detail::Tagged... Us>
        constexpr auto operator |(const T&, const detail::Tags<Us...>&)
        {
            return detail::Tags<T, Us...>{};
        }
        template<detail::Tagged... Ts, detail::Tagged U>
        constexpr auto operator |(const  detail::Tags<Ts...>&, const U&)
        {
            return detail::Tags<Ts..., U>{};
        }
        template<detail::Tagged... Ts, detail::Tagged... Us>
        constexpr auto operator |(const  detail::Tags<Ts...>&, const detail::Tags<Us...>&)
        {
            return detail::Tags<Ts..., Us...>{};
        }

        /// <summary>
        /// 無効
        /// </summary>
        struct Invalid : virtual detail::ITag {};

        /// <summary>
        /// 攻撃者
        /// </summary>
        struct Attacker : virtual Invalid {};

        /// <summary>
        /// 受け身者
        /// </summary>
        struct Receiver : virtual Invalid {};

        /// <summary>
        /// プレイヤー
        /// </summary>
        struct Player : virtual Invalid {};

        /// <summary>
        /// 敵
        /// </summary>
        struct Enemy : virtual Invalid {};

        /// <summary>
        /// マップ
        /// </summary>
        struct Map : virtual Invalid {};
        
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
        struct Gimmick : virtual Invalid {};

        /// <summary>
        /// トビラ
        /// </summary>
        struct Door : virtual Gimmick {};

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

        template<Tag::detail::Tagged T>
        struct Wrap final : Base
        {
            bool accept(const Tag::TagVisitor& visitor) const final
            {
                return visitor.visit(T{});
            }
        };
        template<Tag::detail::Tagged... Ts>
        struct Wrap<Tag::detail::Tags<Ts...>> final : Base
        {
            bool accept(const Tag::TagVisitor& visitor) const final
            {
                Tag::detail::Tags<Ts...> tag;
                return (visitor.visit(static_cast<Ts&>(tag)) || ...);
            }
        };
    public:
        TagType() = default;
        template<Tag::detail::Tagged T>
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
        template<Tag::detail::Tagged T>
        bool is()
        {
            return this->accept([]([[maybe_unused]] const T& tag) {

            });
        }
        template<Tag::detail::Tagged T>
        bool isNot()
        {
            return !is<T>();
        }
    private:
        std::unique_ptr<Base> m_tag;
    };

}