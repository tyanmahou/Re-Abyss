#include "Cursor.hpp"
#include "Shot.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/Cycle/Title/Cursor/CursorVM.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::Title::Cursor
{
    Cursor::Mode& operator ++(Cursor::Mode& mode)
    {
        mode = (mode == Cursor::Mode::Max) ? 
            Cursor::Mode::Min : 
            static_cast<Cursor::Mode>(static_cast<int>(mode) + 1);
        return mode;
    }
    Cursor::Mode& operator --(Cursor::Mode& mode)
    {
        mode = (mode == Cursor::Mode::Min) ?
            Cursor::Mode::Max :
            static_cast<Cursor::Mode>(static_cast<int>(mode) - 1);
        return mode;
    }
    Cursor::Cursor():
        m_view(std::make_unique<CursorVM>()),
        m_gameStartTimer(1s, false),
        m_shot(std::make_unique<Shot>(Vec2{350.0 , 360.0 } + Vec2{30, -1}))
    {}
    Cursor::~Cursor()
    {}
    void Cursor::update()
    {
        if (m_isGameStart) {
            m_shot->update();
            if (m_gameStartTimer.reachedZero()) {
                const auto& event = m_events[static_cast<size_t>(Mode::GameStart)];
                if (event) {
                    event();
                }
            }
            return;
        }
        // カーソルを動かす
        if (InputManager::Up.down()) {
            --m_mode;
        } else if (InputManager::Down.down()) {
            ++m_mode;
        }

        // 決定
        if (InputManager::A.down() || InputManager::Start.down()) {
            if (m_mode == Mode::GameStart) {
                m_shot->addShotFiringEffect();
                m_gameStartTimer.start();
                m_isGameStart = true;
            } else {
                const auto& event = m_events[static_cast<size_t>(m_mode)];
                if (event) {
                    event();
                }
            }
        }
    }

    void Cursor::draw() const
    {
        struct CursorViewParam
        {
            String name;
            double posY;
        };
        const static std::array<CursorViewParam, ModeTerm> viewParams
        {
            CursorViewParam{U"GAME START", 360.0},
            CursorViewParam{U"Exit", 410.0},
        };
        size_t modeIndex = static_cast<size_t>(m_mode);
        m_view->setPos({ 350, viewParams[modeIndex].posY }).draw();

        for (const auto& param : viewParams) {
            FontAsset(U"titleSelect")(param.name).drawAt(480, param.posY);
        }
        if (m_isGameStart) {
            m_shot->draw();
        }
    }
}
