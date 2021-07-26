#include "CursorCtrl.hpp"
#include "Shot.hpp"
#include <abyss/commons/FontName.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/views/UI/Title/Cursor/CursorVM.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/components/Cycle/Title/Master.hpp>

#include <Siv3D.hpp>

namespace abyss::UI::Title::Cursor
{
    CursorCtrl::Mode& operator ++(CursorCtrl::Mode& mode)
    {
        mode = (mode == CursorCtrl::Mode::Max) ?
            CursorCtrl::Mode::Min :
            static_cast<CursorCtrl::Mode>(static_cast<int>(mode) + 1);
        return mode;
    }
    CursorCtrl::Mode& operator --(CursorCtrl::Mode& mode)
    {
        mode = (mode == CursorCtrl::Mode::Min) ?
            CursorCtrl::Mode::Max :
            static_cast<CursorCtrl::Mode>(static_cast<int>(mode) - 1);
        return mode;
    }
    CursorCtrl::CursorCtrl(UIObj* pUi) :
        m_pUi(pUi),
        m_view(std::make_unique<CursorVM>()),
        m_gameStartTimer(1s, false),
        m_shot(std::make_unique<Shot>(Vec2{ 350.0 , 360.0 } + Vec2{ 30, -1 }))
    {
    }
    CursorCtrl::~CursorCtrl()
    {}
    void CursorCtrl::onStart()
    {
        auto manager = m_pUi->getManager();
        (*this)[Mode::GameStart] = [manager, this] {
            manager->getModule<CycleMaster>()->find<Cycle::Title::Master>()->gameStart();
            this->m_isDone = true;
        };
        (*this)[Mode::Exit] = [manager, this] {
            manager->getModule<CycleMaster>()->find<Cycle::Title::Master>()->exit();
            this->m_isDone = true;
        };
    }
    void CursorCtrl::onUpdate()
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

    void CursorCtrl::onDraw() const
    {
        struct CursorViewParam
        {
            String name;
            double posY;
        };
        static const std::array<CursorViewParam, ModeTerm> viewParams
        {
            CursorViewParam{U"GAME START", 360.0},
            CursorViewParam{U"Exit", 410.0},
        };
        size_t modeIndex = static_cast<size_t>(m_mode);
        m_view->setPos({ 350, viewParams[modeIndex].posY }).draw();

        for (const auto& param : viewParams) {
            FontAsset(FontName::SceneName)(param.name).drawAt(480, param.posY);
        }
        if (m_isGameStart) {
            m_shot->draw();
        }
    }
}
