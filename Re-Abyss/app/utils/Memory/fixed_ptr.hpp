#pragma once
#include <memory>
#include <type_traits>
#include <concepts>

namespace abyss
{
    template<class... Types>
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

            struct base_type : ivisitor<Types>...
            {
                using ivisitor<Types>::visit...;
            };

            template<class To, class Head, class... Tail>
            struct tester : tester<To, Tail...>
            {
                using tester<To, Tail...>::visit;
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
                using base_type::visit;
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
            using tester_type = tester<To, Types...>;

        public:
            template<class To>
            visitor_type([[maybe_unused]] To*) :
                m_tester(&std::get<tester_type<To>>(s_testers))
            {}

            template<class From>
            void* visit(From* from) const
            {
                return m_tester->visit(from);
            }
        private:
            base_type* m_tester;
            static inline std::tuple<tester_type<Types>...> s_testers;
        };

    private:
        struct base_type
        {
            virtual ~base_type() = default;
            virtual void* get() const = 0;
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
            void* get() const override
            {
                return static_cast<void*>(ptr);
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
                ((ret = accept2<Types>(visitor), ret != nullptr) || ...);
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

        void* accept(const visitor_type& visitor) const
        {
            if (!m_ptr) {
                return nullptr;
            }
            return m_ptr->accept(visitor);
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
            ToPtr to = nullptr;
            typename fixed_ptr<Types...>::visitor_type visitor = to;

            if (auto ret = ptr.accept(visitor)) {
                to = static_cast<ToPtr>(ret);
            }
            return to;
        }
    };

    template<class ToPtr>
    inline constexpr auto fixed_dynamic_cast = fixed_dynamic_cast_impl<ToPtr>{};
}
