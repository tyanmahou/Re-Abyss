#pragma once
#include <Siv3D/Gamepad.hpp>

#include <abyss/utils/Key/InputState/InputState.hpp>
#include <abyss/utils/Singleton/Singleton.hpp>

namespace abyss
{
    class KeyPovD8
    {
    public:
        enum Code : s3d::int8
        {
            Up,
            Right,
            Down,
            Left,
        };
        s3d::int8 m_userIndex{0};
        Code m_code{Code::Up};
    public:
        KeyPovD8() = default;
        constexpr KeyPovD8(s3d::int8 userIndex, Code code) noexcept:
            m_userIndex(userIndex),
            m_code(code)
        {}
        KeyPovD8(const s3d::detail::Gamepad_impl& gamepad, Code code) noexcept;

        [[nodiscard]] bool down() const;

        [[nodiscard]] bool pressed() const;

        [[nodiscard]] bool up() const;

        [[nodiscard]] s3d::Duration pressedDuration() const;

        [[nodiscard]] s3d::String name() const;
    };

    class KeyPovD8Updater : public Singleton<KeyPovD8Updater>
    {
        friend class Singleton<KeyPovD8Updater>;

        std::array<s3d::InputState, s3d::Gamepad.MaxPlayerCount * 4> m_state;
    public:
        void update();

        [[nodiscard]] bool down(s3d::int8 userIndex, KeyPovD8::Code code) const;

        [[nodiscard]] bool pressed(s3d::int8 userIndex, KeyPovD8::Code code) const;

        [[nodiscard]] bool up(s3d::int8 userIndex, KeyPovD8::Code code) const;

        [[nodiscard]] s3d::Duration pressedDuration(s3d::int8 userIndex, KeyPovD8::Code code) const;
    };
}