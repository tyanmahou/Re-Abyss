#pragma once
#include <memory>
#include <Siv3D/Duration.hpp>
#include <abyss/utils/Singleton.hpp>

namespace abyss
{
    class AbyssKey
    {
    public:
        enum KeyType
        {
            A,
            B,

            Up,
            Right,
            Down,
            Left,

            Start,
            MAX,

            Jump = A,
            Attack = B,
        };
    private:
        KeyType m_type;
    public:
        constexpr AbyssKey(KeyType type):
            m_type(type)
        {}

        bool up() const;
        bool down() const;
        bool pressed() const;

        s3d::Duration pressedDuration() const;
    };
    class InputManager : protected Singleton<InputManager>
    {
        friend class Singleton<InputManager>;
        friend class AbyssKey;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
        InputManager();
        ~InputManager();
    public:
        static void Update();

        inline static constexpr AbyssKey A{ AbyssKey::A };
        inline static constexpr AbyssKey B{ AbyssKey::B };

        inline static constexpr AbyssKey Up{ AbyssKey::Up };
        inline static constexpr AbyssKey Right{ AbyssKey::Right };
        inline static constexpr AbyssKey Down{ AbyssKey::Down };
        inline static constexpr AbyssKey Left{ AbyssKey::Left };

        inline static constexpr AbyssKey Start{ AbyssKey::Start };

        inline static constexpr AbyssKey Jump{ AbyssKey::Jump };
        inline static constexpr AbyssKey Attack{ AbyssKey::Attack };
    };
}