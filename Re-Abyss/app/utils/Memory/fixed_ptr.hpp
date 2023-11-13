#pragma once
#include <memory>
#include <type_traits>
#include <concepts>

namespace abyss
{
    template<class... Types>
    class fixed_ptr
    {
    private:
        template<class T>
        struct icaster
        {
            virtual ~icaster() = default;
            virtual T* cast_to([[maybe_unused]] T*) const = 0;
        };
        struct base_type : icaster<Types>...
        {
            using icaster<Types>::cast_to...;

            virtual ~base_type() = default;
            virtual void* get() const = 0;
        };
        template<class T, class Head, class... Tail>
        struct holder : holder<T, Tail...>
        {
            using holder<T, Tail...>::holder;
            using holder<T, Tail...>::ptr;
            using holder<T, Tail...>::cast_to;

            Head* cast_to([[maybe_unused]] Head* _) const override
            {
                if constexpr (std::convertible_to<T*, Head*>) {
                    return static_cast<Head*>(ptr);
                } else {
                    return nullptr;
                }
            }
        };
        template<class T, class Last>
        struct holder<T, Last> : base_type
        {
            T* ptr;

            holder(T* _ptr):
                ptr(_ptr)
            {}
            ~holder()
            {
                delete ptr;
            }
            void* get() const override
            {
                return ptr;
            }

            using base_type::cast_to;

            Last* cast_to([[maybe_unused]] Last* _) const override
            {
                if constexpr (std::convertible_to<T*, Last*>) {
                    return static_cast<Last*>(ptr);
                } else {
                    return nullptr;
                }
            }
        };
    public:
        fixed_ptr() = default;
        template<class Type>
        fixed_ptr(Type* ptr) :
            m_ptr(std::make_shared<holder<Type, Types...>>(ptr))
        {}

        fixed_ptr(std::nullptr_t) :
            m_ptr(nullptr)
        {}
        void* get() const
        {
            if (!m_ptr) {
                return nullptr;
            }
            return m_ptr->get();
        }

        void release() const
        {
            m_ptr = nullptr;
        }

        template<class ToPtr>
            requires (std::same_as<std::decay_t<ToPtr>, Types*> || ...)
        ToPtr cast_to() const
        {
            if (!m_ptr) {
                return nullptr;
            }
            ToPtr p{};
            return m_ptr->cast_to(p);
        }
        explicit operator bool() const
        {
            return m_ptr != nullptr;
        }

        template<class T, class... Args>
        static fixed_ptr make_fixed(Args&&... args)
        {
            return fixed_ptr(new T(std::forward<Args>(args)...));
        }
    private:
        std::shared_ptr<base_type> m_ptr;
    };

    template<class ToPtr>
    struct fixed_dynamic_cast_impl
    {
        template<class... Types>
            requires (std::same_as<std::decay_t<ToPtr>, Types*> || ...)
        ToPtr operator()(const fixed_ptr<Types...>& ptr) const
        {
            return ptr.cast_to<ToPtr>();
        }
    };

    template<class ToPtr>
    inline constexpr auto fixed_dynamic_cast = fixed_dynamic_cast_impl<ToPtr>{};
}
