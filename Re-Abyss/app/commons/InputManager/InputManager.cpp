#include "InputManager.hpp"
#include <Siv3D.hpp>

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
namespace s3d
{
    // https://github.com/Siv3D/OpenSiv3D/blob/master/Siv3D/src/Siv3D/Key/InputState.hpp

    struct InputState
    {
        Duration _pressedDuration{ 0 };

        Stopwatch stopwatch = Stopwatch{ true };

        bool up = false;

        bool pressed = false;

        bool down = false;

        void update(bool currentPressed)
        {
            const bool previousPressed = pressed;

            pressed = currentPressed;

            down = !previousPressed && pressed;

            up = previousPressed && !pressed;

            if (down) {
                stopwatch.restart();
            } else if (up) {
                _pressedDuration = stopwatch.elapsed();

                stopwatch.reset();
            } else if (pressed) {
                _pressedDuration = stopwatch.elapsed();
            } else {
                _pressedDuration = Duration(0);
            }
        }

        void clear()
        {
            _pressedDuration = Duration(0);

            stopwatch.restart();

            up = pressed = down = false;
        }
    };
}
namespace abyss
{

    class KeyPovD8
    {
        std::function<Optional<int32>()> m_func;
        InputState m_stateUp;
        InputState m_stateDown;
        InputState m_stateLeft;
        InputState m_stateRight;

    protected:
        virtual bool pressedUp(const Optional<int32>& pov)const
        {
            return ConvertFromPovD8(pov, 1);
        }
        virtual bool pressedDown(const Optional<int32>& pov)const
        {
            return ConvertFromPovD8(pov, 5);
        }
        virtual bool pressedLeft(const Optional<int32>& pov)const
        {
            return ConvertFromPovD8(pov, 3);
        }
        virtual bool pressedRight(const Optional<int32>& pov)const
        {
            return ConvertFromPovD8(pov, 7);
        }
    public:
        KeyPovD8(const detail::Gamepad_impl& gamepad) :
            m_func([gamepad]() {return gamepad.povD8(); })
        {}
        void update()
        {
            auto current = m_func();
            m_stateUp.update(this->pressedUp(current));
            m_stateDown.update(this->pressedDown(current));
            m_stateLeft.update(this->pressedLeft(current));
            m_stateRight.update(this->pressedRight(current));
        }
        const InputState& up()const
        {
            return m_stateUp;
        }
        const InputState& down()const
        {
            return m_stateDown;
        }
        const InputState& left()const
        {
            return m_stateLeft;
        }
        const InputState& right()const
        {
            return m_stateRight;
        }
    };
    class JoyConPovD8 : public KeyPovD8
    {
    public:
        using KeyPovD8::KeyPovD8;
    protected:
        bool pressedUp(const Optional<int32>& pov)const override
        {
            return KeyPovD8::pressedLeft(pov);
        }
        bool pressedDown(const Optional<int32>& pov)const override
        {
            return KeyPovD8::pressedRight(pov);
        }
        bool pressedLeft(const Optional<int32>& pov)const override
        {
            return KeyPovD8::pressedDown(pov);
        }
        bool pressedRight(const Optional<int32>& pov)const override
        {
            return KeyPovD8::pressedUp(pov);
        }
    };

    class InputManager::Impl
    {
        s3d::KeyGroup m_jump;
        s3d::KeyGroup m_attack;

        s3d::KeyGroup m_up;
        s3d::KeyGroup m_down;
        s3d::KeyGroup m_right;
        s3d::KeyGroup m_left;

        s3d::KeyGroup m_start;

        Array<std::unique_ptr<KeyPovD8>> m_povs;
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
            // JoyCon
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

                    m_povs.push_back(std::make_unique<JoyConPovD8>(pad));
                }
            }
        }

        void update()
        {
            for (auto&& pov : m_povs) {
                pov->update();
            }
        }

        using GroupState = decltype(&KeyGroup::up);
        using PovState = decltype(&InputState::up);

        bool state(AbyssKey::KeyType type, GroupState gState, PovState iState) const 
        {
            switch (type) {
            case AbyssKey::A:
                {
                    return (m_jump.*gState)(); 
                }
            case AbyssKey::B:
                {
                    return (m_attack.*gState)();
                }
            case AbyssKey::Up:
                {
                    return (m_up.*gState)() || m_povs.any([iState](const std::unique_ptr<KeyPovD8>& pov) {
                        return pov->up().*iState; 
                    }); 
                }
            case AbyssKey::Down:
                {
                    return (m_down.*gState)() || m_povs.any([iState](const std::unique_ptr<KeyPovD8>& pov) {
                        return pov->down().*iState;
                }); 
                }
            case AbyssKey::Left:
                {
                    return (m_left.*gState)() || m_povs.any([iState](const std::unique_ptr<KeyPovD8>& pov) {
                        return pov->left().*iState;
                    }); 
                }
            case AbyssKey::Right:
                {
                    return (m_right.*gState)() || m_povs.any([iState](const std::unique_ptr<KeyPovD8>& pov) {
                        return pov->right().*iState;
                    });
                }
            case AbyssKey::Start:
                {
                    return (m_start.*gState)();
                }
            default:
                    break; 
            }
                return false;
        }

        bool up(AbyssKey::KeyType type) const
        {
            return this->state(type, &KeyGroup::up, &InputState::up);
        }

        bool down(AbyssKey::KeyType type) const
        {
            return this->state(type, &KeyGroup::down, &InputState::down);
        }

        bool pressed(AbyssKey::KeyType type) const
        {
            return this->state(type, &KeyGroup::pressed, &InputState::pressed);
        }

        Duration pressedDuration(AbyssKey::KeyType type) const
        {
            switch (type) {
            case AbyssKey::A:
            {
                return m_jump.pressedDuration();
            }
            case AbyssKey::B:
            {
                return m_attack.pressedDuration();
            }
            case AbyssKey::Up:
            {
                Duration duration = m_up.pressedDuration();
                for (const auto& pov : m_povs) {
                    duration = std::max(duration, pov->up()._pressedDuration);
                }
                return duration;
            }
            case AbyssKey::Down:
            {
                Duration duration = m_down.pressedDuration();
                for (const auto& pov : m_povs) {
                    duration = std::max(duration, pov->down()._pressedDuration);
                }
                return duration;
            }
            case AbyssKey::Left:
            {
                Duration duration = m_left.pressedDuration();
                for (const auto& pov : m_povs) {
                    duration = std::max(duration, pov->left()._pressedDuration);
                }
                return duration;
            }
            case AbyssKey::Right:
            {
                Duration duration = m_right.pressedDuration();
                for (const auto& pov : m_povs) {
                    duration = std::max(duration, pov->right()._pressedDuration);
                }
                return duration;
            }
            case AbyssKey::Start:
            {
                return m_start.pressedDuration();
            }
            default:
                break;
            }
            return Duration{0};
        }
    };

    InputManager::InputManager() :
        m_pImpl(std::make_unique<Impl>())
    {}

    InputManager::~InputManager()
    {}

    void InputManager::Update()
    {
        Instance()->m_pImpl->update();
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