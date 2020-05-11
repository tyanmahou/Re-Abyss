#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/Duration.hpp>
#include <Siv3D/Fwd.hpp>

#include <concepts>

namespace abyss
{
    template<class Type>
    concept IsKeyType = requires(const Type& key)
    {
        { key.down() }->std::same_as<bool>;
        { key.pressed() }->std::same_as<bool>;
        { key.up() }->std::same_as<bool>;
        { key.name() }->std::same_as<s3d::String>;
    };

    class KeyGroupEx
    {
        class IKey
        {
        public:
            virtual bool down() const = 0;
            virtual bool pressed() const =0;
            virtual bool up() const = 0;
            virtual s3d::Duration pressedDuration() const = 0;
            virtual s3d::String name() const = 0;
        };
        template <IsKeyType Type>
        class KeyAny final : public IKey
        {
            Type m_key;
        public:
            KeyAny(const Type& key):
                m_key(key)
            {}
            bool down() const final
            {
                return m_key.down();
            }
            bool pressed() const final
            {
                return m_key.pressed();
            }
            bool up() const final
            {
                return m_key.up();
            }
            s3d::Duration pressedDuration() const final
            {
                return m_key.pressedDuration();
            }
            s3d::String name() const final
            {
                return m_key.name();
            }
        };
    private:
        s3d::Array<std::shared_ptr<IKey>> m_keys;

    public:
        template<IsKeyType ...Type>
        explicit KeyGroupEx(const Type& ...keys)
        {
            (m_keys.push_back(std::make_shared<KeyAny<Type>>(keys)), ...);
        }

        template<IsKeyType Type>
        KeyGroupEx& operator |=(const Type& key)
        {
            m_keys.push_back(std::make_shared<KeyAny<Type>>(key));
            return *this;
        }

        [[nodiscard]] bool down() const;

        [[nodiscard]] bool pressed() const;

        [[nodiscard]] bool up() const;

        [[nodiscard]] s3d::int32 num_pressed() const;

        [[nodiscard]] s3d::Duration pressedDuration() const;

        [[nodiscard]] s3d::String name() const;
    };
}

namespace s3d
{
    void Formatter(FormatData& formatData, const abyss::KeyGroupEx& group);

    template <class CharType>
    inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType> os, const abyss::KeyGroupEx& group)
    {
        return os << group.name();
    }
}