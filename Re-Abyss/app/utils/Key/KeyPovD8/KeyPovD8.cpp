#include "KeyPovD8.hpp"

using namespace s3d;
namespace
{
    bool ConvertFromPovD8(const Optional<int32>& pov, int32 offset)
    {
        if (!pov) {
            return false;
        }
        int32 tmp = (*pov + offset) % 8;
        return tmp == 0 || tmp == 1 || tmp == 2;
    }
}
namespace abyss
{
    KeyPovD8::KeyPovD8(const s3d::detail::Gamepad_impl& gamepad, Code code) noexcept :
        KeyPovD8(static_cast<uint8>(gamepad.playerIndex), code)
    {}
    bool KeyPovD8::down() const
    {
        return KeyPovD8Updater::Instance()->down(m_userIndex, m_code);
    }
    bool KeyPovD8::pressed() const
    {
        return KeyPovD8Updater::Instance()->pressed(m_userIndex, m_code);
    }
    bool KeyPovD8::up() const
    {
        return KeyPovD8Updater::Instance()->up(m_userIndex, m_code);
    }
    Duration KeyPovD8::pressedDuration() const
    {
        return KeyPovD8Updater::Instance()->pressedDuration(m_userIndex, m_code);
    }

    String KeyPovD8::name() const
    {
        if (InRange<uint8>(m_code, Up, Left)) {
            static const String names[4] =
            {
                U"Up",
                U"Right",
                U"Down",
                U"Left",
            };

            return U"Gamepad-POV-D8_" + names[m_code];
        }

        return U"Gamepad-POV-D8" + ToString(m_code);
    }

    void KeyPovD8Updater::update()
    {
        for (uint8 userIndex = 0; userIndex < Gamepad.MaxPlayerCount; ++userIndex) {
            auto&& gamepad = Gamepad(userIndex);
            if (gamepad) {
                auto&& pov = gamepad.povD8();
                for (uint8 code = 0; code < 4; ++code) {
                    m_state[userIndex * 4 + code].update(ConvertFromPovD8(pov, code * 6 + 1));
                }
            } else {
                for (uint8 code = 0; code < 4; ++code) {
                    m_state[userIndex * 4 + code].update(false);
                }
            }
        }
    }
    bool KeyPovD8Updater::down(s3d::int8 userIndex, KeyPovD8::Code code) const
    {
        return m_state[userIndex * 4 + code].down;
    }
    bool KeyPovD8Updater::pressed(s3d::int8 userIndex, KeyPovD8::Code code) const
    {
        return m_state[userIndex * 4 + code].pressed;
    }
    bool KeyPovD8Updater::up(s3d::int8 userIndex, KeyPovD8::Code code) const
    {
        return m_state[userIndex * 4 + code].up;
    }
    s3d::Duration KeyPovD8Updater::pressedDuration(s3d::int8 userIndex, KeyPovD8::Code code) const
    {
        return m_state[userIndex * 4 + code].pressedDuration;
    }
}