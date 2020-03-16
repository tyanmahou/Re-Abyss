#include "InputManager.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    class InputManager::Impl
    {
    public:
        Impl()
        {
            // Keyboard
            {
                m_jump |= KeyZ;
                m_attack |= KeyX;
                m_up |= KeyUp;
                m_down |= KeyDown;
                m_right |= KeyRight;
                m_left |= KeyLeft;
                m_start |= KeyEnter;
            }
            for (const auto& info : System::EnumerateGamepads()) {
                auto&& pad = Gamepad(info.index);
                if (JoyCon::IsJoyConR(pad)) {
                    auto joyConR = JoyCon(pad);

                    m_jump |= joyConR.button0;
                    m_attack |= joyConR.button2;

                    m_start |= joyConR.buttonPlus;
                } else if (JoyCon::IsJoyConL(pad)) {
                    auto joyConL = JoyCon(pad);

                    m_up |= joyConL.button2;
                    m_down |= joyConL.button1;
                    m_right |= joyConL.button3;
                    m_left |= joyConL.button0;
                }
            }
        }

        s3d::KeyGroup m_jump;
        s3d::KeyGroup m_attack;

        s3d::KeyGroup m_up;
        s3d::KeyGroup m_down;
        s3d::KeyGroup m_right;
        s3d::KeyGroup m_left;

        s3d::KeyGroup m_start;
    };

    InputManager::InputManager():
        m_pImpl(std::make_unique<Impl>())
    {}

    InputManager::~InputManager()
    {}

    const s3d::KeyGroup& InputManager::jump() const
    {
        return m_pImpl->m_jump;
    }

    const s3d::KeyGroup& InputManager::attack() const
    {
        return m_pImpl->m_attack;
    }

    const s3d::KeyGroup& InputManager::up() const
    {
        return m_pImpl->m_up;
    }

    const s3d::KeyGroup& InputManager::down() const
    {
        return m_pImpl->m_down;
    }

    const s3d::KeyGroup& InputManager::right() const
    {
        return m_pImpl->m_right;
    }

    const s3d::KeyGroup& InputManager::left() const
    {
        return m_pImpl->m_left;
    }

    const s3d::KeyGroup& InputManager::start() const
    {
        return m_pImpl->m_start;
    }
    const s3d::KeyGroup& InputManager::A() const
    {
        return this->jump();
    }
    const s3d::KeyGroup& InputManager::B() const
    {
        return this->attack();
    }
}