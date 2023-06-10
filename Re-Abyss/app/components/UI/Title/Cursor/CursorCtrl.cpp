#include <abyss/components/UI/Title/Cursor/CursorCtrl.hpp>
#include <abyss/components/UI/Title/Cursor/Shot.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/MsgUtil.hpp>
#include <abyss/views/UI/Title/Cursor/CursorVM.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Sound/Sounds.hpp>
#include <abyss/components/Sound/SePath.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/components/Cycle/Title/Master.hpp>
#include <abyss/params/UI/Title/CursorParam.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::UI::Title;
    Vec2 CursorPos(size_t modeIndex)
    {
        return AnchorUtil::FromCc(CursorParam::ViewParam::Pos(modeIndex));
    }
    Vec2 CursorPosModeName(size_t modeIndex)
    {
        return AnchorUtil::FromCc(0, CursorParam::ViewParam::PosY(modeIndex));
    }
}
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
        m_gameStartTimer(1s, StartImmediately::No, pUi->getModule<GlobalTime>()),
        m_shot(std::make_unique<Shot>(pUi))
    {
    }
    CursorCtrl::~CursorCtrl()
    {}
    void CursorCtrl::onStart()
    {
        auto manager = m_pUi->getManager();
        (*this)[Mode::GameStart] = [manager] {
            manager->getModule<CycleMaster>()->find<Cycle::Title::Master>()->gameStart();
        };
        (*this)[Mode::Exit] = [manager] {
            manager->getModule<CycleMaster>()->find<Cycle::Title::Master>()->exit();
        };
    }
    void CursorCtrl::onUpdate()
    {
        const size_t modeIndex = static_cast<size_t>(m_mode);

        if (m_isSelected) {
            m_shot->update();
            if (m_gameStartTimer.reachedZero()) {
                const auto& event = m_events[modeIndex];
                if (event) {
                    event();
                    m_isDone = true;
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
            m_shot->setPos(::CursorPos(modeIndex));
            // shot effect
            m_shot->addShotFiringEffect();
            m_gameStartTimer.start();
            m_isSelected = true;

            m_pUi->getModule<Sounds>()->playSe(Sound::SePath::TitleDecide);
        }
    }

    void CursorCtrl::onDraw() const
    {
        const size_t modeIndex = static_cast<size_t>(m_mode);
        m_view->setPos(::CursorPos(modeIndex)).draw();

        constexpr const std::array<MsgUtil::Text, ModeTerm> modeName
        {
            MsgUtil::Title_GameStart,
            MsgUtil::Title_Exit
        };
        for (size_t index = 0; index < ModeTerm; ++index) {
            FontAsset(FontName::SceneName)(modeName[index]).drawAt(::CursorPosModeName(index));
        }
        if (m_isSelected) {
            m_shot->draw();
        }
    }
}
