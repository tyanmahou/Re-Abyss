#include "InputManager.hpp"
#include <Siv3D.hpp>
#include <abyss/utils/Key/KeyGroupEx/KeyGroupEx.hpp>
#include <abyss/utils/Key/KeyPovD8/KeyPovD8.hpp>

namespace abyss
{
    class InputManager::Impl
    {
        std::array<KeyGroupEx, AbyssKey::MAX> m_keys;
    public:
        Impl()
        {
            // Keyboard
            {
                m_keys[AbyssKey::A] |= KeyZ;
                m_keys[AbyssKey::B] |= KeyX;
                m_keys[AbyssKey::Up] |= KeyUp;
                m_keys[AbyssKey::Right] |= KeyRight;
                m_keys[AbyssKey::Down] |= KeyDown;
                m_keys[AbyssKey::Left] |= KeyLeft;
                m_keys[AbyssKey::Start] |= KeyEnter;
            }
            // JoyCon
            for (const auto& info : System::EnumerateGamepads()) {
                auto&& pad = Gamepad(info.playerIndex);
                if (JoyCon::IsJoyConR(pad)) {
                    auto joyConR = JoyCon(pad);

                    m_keys[AbyssKey::A] |= joyConR.button0;
                    m_keys[AbyssKey::B] |= joyConR.button2;

                    m_keys[AbyssKey::Start] |= joyConR.buttonPlus;
                } else if (JoyCon::IsJoyConL(pad)) {
                    auto joyConL = JoyCon(pad);

                    m_keys[AbyssKey::Up] |= joyConL.button2;
                    m_keys[AbyssKey::Down] |= joyConL.button1;
                    m_keys[AbyssKey::Right] |= joyConL.button3;
                    m_keys[AbyssKey::Left] |= joyConL.button0;

                    // povD8
                    m_keys[AbyssKey::Up] |= KeyPovD8(pad, KeyPovD8::Left);
                    m_keys[AbyssKey::Right] |= KeyPovD8(pad, KeyPovD8::Up);
                    m_keys[AbyssKey::Down] |= KeyPovD8(pad, KeyPovD8::Right);
                    m_keys[AbyssKey::Left] |= KeyPovD8(pad, KeyPovD8::Down);
                }
            }
        }

        bool up(AbyssKey::KeyType type) const
        {
            return m_keys[type].up();
        }

        bool down(AbyssKey::KeyType type) const
        {
            return m_keys[type].down();
        }

        bool pressed(AbyssKey::KeyType type) const
        {
            return m_keys[type].pressed();
        }

        Duration pressedDuration(AbyssKey::KeyType type) const
        {
            return m_keys[type].pressedDuration();
        }
    };

    InputManager::InputManager() :
        m_pImpl(std::make_unique<Impl>())
    {}

    InputManager::~InputManager()
    {}

    void InputManager::Update()
    {
        KeyPovD8Updater::Instance()->update();
    }
    bool AbyssKey::up() const
    {
        return InputManager::Instance()->m_pImpl->up(m_type);
    }
    bool AbyssKey::down() const
    {
        return InputManager::Instance()->m_pImpl->down(m_type);
    }
    bool AbyssKey::pressed() const
    {
        return InputManager::Instance()->m_pImpl->pressed(m_type);
    }
    Duration AbyssKey::pressedDuration() const
    {
        return InputManager::Instance()->m_pImpl->pressedDuration(m_type);
    }
}