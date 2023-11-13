#pragma once
#include <memory>
#include <type_traits>
#include <tuple>
#include <concepts>

namespace abyss
{
    template<class... Types>
    class fixed_ptr
    {
    public:
        using base_type = std::tuple_element_t<0, std::tuple<Types...>>;
    private:
        template<class T>
        struct icaster
        {
            virtual ~icaster() = default;
            virtual T* cast_to([[maybe_unused]] T*) const noexcept = 0;
        };
        struct holder_base : icaster<Types>...
        {
            using icaster<Types>::cast_to...;

            virtual ~holder_base() = default;
            virtual base_type* get() const noexcept = 0;
        };
        template<class T, class Head, class... Tail>
        struct holder : holder<T, Tail...>
        {
            using holder<T, Tail...>::holder;
            using holder<T, Tail...>::ptr;
            using holder<T, Tail...>::cast_to;

            Head* cast_to([[maybe_unused]] Head* _) const noexcept override
            {
                if constexpr (std::convertible_to<T*, Head*>) {
                    return static_cast<Head*>(ptr);
                } else {
                    return nullptr;
                }
            }
        };
        template<class T, class Last>
        struct holder<T, Last> : holder_base
        {
            T* ptr;

            holder(T* _ptr):
                ptr(_ptr)
            {}
            ~holder()
            {
                delete ptr;
            }
            base_type* get() const noexcept override
            {
                return ptr;
            }

            using holder_base::cast_to;

            Last* cast_to([[maybe_unused]] Last* _) const noexcept override
            {
                if constexpr (std::convertible_to<T*, Last*>) {
                    return static_cast<Last*>(ptr);
                } else {
                    return nullptr;
                }
            }
        };
    public:
        fixed_ptr() noexcept = default;
        template<class Type> requires std::derived_from<Type, base_type>
        fixed_ptr(Type* ptr) :
            m_ptr(std::make_shared<holder<Type, Types...>>(ptr))
        {}
        fixed_ptr(const fixed_ptr& other) noexcept :
            m_ptr(other.m_ptr)
        {}
        fixed_ptr(fixed_ptr&& other) noexcept :
            m_ptr(std::move(other.m_ptr))
        {}
        fixed_ptr(std::nullptr_t) noexcept :
            m_ptr(nullptr)
        {}
        base_type* get() const noexcept
        {
            if (!m_ptr) {
                return nullptr;
            }
            return m_ptr->get();
        }
        base_type* operator ->() const noexcept
        {
            return get();
        }
        base_type& operator *() const noexcept
        {
            return *get();
        }
        template<class ToPtr>
            requires (std::same_as<std::decay_t<ToPtr>, Types*> || ...)
        ToPtr cast_to() const noexcept
        {
            if (!m_ptr) {
                return nullptr;
            }
            ToPtr p{};
            return m_ptr->cast_to(p);
        }
        void reset() 
        {
            m_ptr = nullptr;
        }
        explicit operator bool() const noexcept
        {
            return get() != nullptr;
        }
        template<class Type> requires std::derived_from<Type, base_type>
        fixed_ptr& operator=(Type* ptr)
        {
            m_ptr = std::make_shared<holder<Type, Types...>>(ptr);
            return *this;
        }
        fixed_ptr& operator=(const fixed_ptr& other) noexcept
        {
            m_ptr = other.m_ptr;
            return *this;
        }
        fixed_ptr& operator=(fixed_ptr&& other) noexcept
        {
            m_ptr = std::move(other.m_ptr);
            return *this;
        }
        template<class T, class... Args>
        static fixed_ptr make_fixed(Args&&... args)
        {
            return fixed_ptr(new T(std::forward<Args>(args)...));
        }
    private:
        std::shared_ptr<holder_base> m_ptr;
    };

    template<class ToPtr>
    struct fixed_dynamic_cast_impl
    {
        template<class... Types>
            requires (std::same_as<std::decay_t<ToPtr>, Types*> || ...)
        ToPtr operator()(const fixed_ptr<Types...>& ptr) const
        {
            return ptr.template cast_to<ToPtr>();
        }
    };

    template<class ToPtr>
    inline constexpr auto fixed_dynamic_cast = fixed_dynamic_cast_impl<ToPtr>{};
}
