#include <type_traits>
#include <concepts>
#include <variant>

namespace abyss
{
    template<class Base, std::derived_from<Base>... Deriveds>
    class variant_ptr
    {
    public:
        using value_type = std::variant<Base*, Deriveds*...>;
    public:
        variant_ptr() noexcept = default;
        template<class Type> requires std::same_as<Type, Base> || (std::same_as<Type, Deriveds> || ...)
            variant_ptr(Type * ptr) noexcept
        {
            *this = ptr;
        }
        variant_ptr(const variant_ptr& other) noexcept :
            m_ptr(other.m_ptr)
        {}
        variant_ptr(std::nullptr_t) noexcept :
            m_ptr()
        {}
        Base* get() const noexcept
        {
            return cast_to<Base*>();
        }
        Base* operator ->() const noexcept
        {
            return get();
        }
        Base& operator *() const noexcept
        {
            return *get();
        }
        template<class ToPtr> requires std::is_pointer_v<ToPtr> && (std::convertible_to<Base*, ToPtr> || (std::convertible_to<Deriveds*, ToPtr> || ...))
            ToPtr cast_to() const noexcept
        {
            return std::visit([]<class T>(T * ptr)->ToPtr {
                if constexpr (std::convertible_to<T*, ToPtr>) {
                    return static_cast<ToPtr>(ptr);
                } else {
                    return nullptr;
                }
            }, m_ptr);
        }
        void reset() noexcept
        {
            m_ptr = value_type{};
        }
        explicit operator bool() const noexcept
        {
            return get() != nullptr;
        }
        template<class Type> requires std::same_as<Type, Base> || (std::same_as<Type, Deriveds> || ...)
        variant_ptr& operator=(Type* ptr) noexcept
        {
            if (ptr == nullptr) {
                m_ptr = value_type{};
                return *this;
            }
            const auto& rtti = typeid(*ptr);
            if (rtti == typeid(Type)) [[likely]] {
                m_ptr = ptr;
                return *this;
                }
            Base* base = static_cast<Base*>(ptr);
            if (rtti == typeid(Base)) {
                m_ptr = base;
                return *this;
            }
            auto derived_checks = [&]<class T>(T*) {
                if (rtti == typeid(T)) {
                    if constexpr (std::convertible_to<Base*, T*>) {
                        m_ptr = static_cast<T*>(base);
                        return true;
                    } else {
                        m_ptr = dynamic_cast<T*>(base);
                        return true;
                    }
                }
                return false;
            };
            if ((derived_checks(static_cast<Deriveds*>(nullptr)) || ...)) {
                return *this;
            }
            m_ptr = ptr;
            return *this;
        }
        variant_ptr& operator=(const variant_ptr& other) noexcept
        {
            m_ptr = other.m_ptr;
            return *this;
        }
    private:
        value_type m_ptr;
    };
    template<class ToPtr>
    struct variant_dynamic_cast_impl
    {
        template<class Base, std::derived_from<Base>... Deriveds>
            requires std::is_pointer_v<ToPtr> && (std::convertible_to<Base*, ToPtr> || (std::convertible_to<Deriveds*, ToPtr> || ...))
        ToPtr operator()(const variant_ptr<Base, Deriveds...>& ptr) const noexcept
        {
            return ptr.template cast_to<ToPtr>();
        }
    };

    template<class ToPtr>
    inline constexpr auto variant_dynamic_cast = variant_dynamic_cast_impl<ToPtr>{};
}
