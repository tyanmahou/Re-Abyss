#pragma once
#include <memory>
#include <type_traits>
#include <concepts>

namespace abyss
{
    template<class Base, std::derived_from<Base>... Deriveds>
    class fixed_ptr
    {
    public:
        class visitor_type
        {
            template<class T>
            struct ivisitor
            {
                virtual ~ivisitor() = default;
                virtual void* visit([[maybe_unused]] T*) const = 0;
            };

            struct base_type : ivisitor<Base>, ivisitor<Deriveds>...
            {
                using ivisitor<Base>::visit;
                using ivisitor<Deriveds>::visit...;
            };

            template<class To, class Head, class... Tail>
            struct tester : tester<To, Tail...>
            {
                constexpr void* visit([[maybe_unused]] Head* ptr) const override
                {
                    if constexpr (std::convertible_to<Head*, To*>) {
                        return static_cast<To*>(ptr);
                    } else {
                        return nullptr;
                    }
                }
            };
            template<class To, class Last>
            struct tester<To, Last> : base_type
            {
                constexpr void* visit([[maybe_unused]] Last* ptr) const override
                {
                    if constexpr (std::convertible_to<Last*, To*>) {
                        return static_cast<To*>(ptr);
                    } else {
                        return nullptr;
                    }
                }
            };
            template<class To>
            using tester_type = tester<To, Base, Deriveds...>;

        public:
            template<class To>
            visitor_type([[maybe_unused]] To*) :
                m_tester(std::make_unique<tester_type<To>>())
            {}

            template<class From>
            void* visit(From* from) const
            {
                return m_tester->visit(from);
            }
        private:
            std::unique_ptr<base_type> m_tester;
        };

    private:
        struct base_type
        {
            virtual ~base_type() = default;
            virtual Base* get() const = 0;
            virtual void* accept(const visitor_type& visitor) const = 0;
        };
        template<class T>
        struct holder_type : base_type
        {
            T* ptr;
            holder_type(T* p) :
                ptr(p)
            {}
            ~holder_type()
            {
                delete ptr;
            }
            Base* get() const
            {
                return static_cast<Base*>(ptr);
            }
            template<class U>
            void* accept2([[maybe_unused]] const visitor_type& visitor) const
            {
                if constexpr (std::convertible_to<T*, U*>) {
                    return visitor.visit(static_cast<U*>(ptr));
                } else {
                    return nullptr;
                }
            }
            void* accept(const visitor_type& visitor) const override
            {
                void* ret = nullptr;
                (ret = accept2<Base>(visitor), ret != nullptr) || ((ret = accept2<Deriveds>(visitor), ret != nullptr) || ...);
                return ret;
            }
        };
    public:
        fixed_ptr() = default;
        template<class Type>
        fixed_ptr(Type* ptr) :
            m_ptr(std::make_shared<holder_type<Type>>(ptr))
        {}

        fixed_ptr(std::nullptr_t) :
            m_ptr(nullptr)
        {}
        Base* get() const
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

        void* accept(const visitor_type& visitor) const
        {
            if (!m_ptr) {
                return nullptr;
            }
            return m_ptr->accept(visitor);
        }

        Base& operator *() const
        {
            return *get();
        }
        Base* operator ->() const
        {
            return get();
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
        template<class Base, std::derived_from<Base>... Deriveds>
        requires std::same_as<std::decay_t<ToPtr>, Base*> || (std::same_as<std::decay_t<ToPtr>, Deriveds*> || ...)
            ToPtr operator()(const fixed_ptr<Base, Deriveds...>&ptr) const
        {
            ToPtr to = nullptr;
            typename fixed_ptr<Base, Deriveds...>::visitor_type visitor = to;

            if (auto ret = ptr.accept(visitor)) {
                to = static_cast<ToPtr>(ret);
            }
            return to;
        }
    };

    template<class ToPtr>
    inline constexpr auto fixed_dynamic_cast = fixed_dynamic_cast_impl<ToPtr>{};
}