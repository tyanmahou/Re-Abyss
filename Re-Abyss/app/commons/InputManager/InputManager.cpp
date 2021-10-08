#include "InputManager.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    InputGroup& operator |=(InputGroup& a, const Input& b)
    {
        a = a | b;
        return a;
    }

    class InputManager::Impl
    {
        std::array<s3d::InputGroup, AbyssKey::MAX> m_keys;
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
                    m_keys[AbyssKey::Up] |= pad.povLeft;
                    m_keys[AbyssKey::Right] |= pad.povUp;
                    m_keys[AbyssKey::Down] |= pad.povRight;
                    m_keys[AbyssKey::Left] |= pad.povDown;
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