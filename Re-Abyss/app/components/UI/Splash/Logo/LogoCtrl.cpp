#include <abyss/components/UI/Splash/Logo/LogoCtrl.hpp>
#include <abyss/views/UI/Splash/Logo/LogoVM.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Constants.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Splash::Logo
{
    LogoCtrl::LogoCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_timer(pUi),
        m_view(std::make_unique<LogoVM>())
    {}
    LogoCtrl::~LogoCtrl()
    {}
    void LogoCtrl::onUpdate()
    {
        if (InputManager::Start.down()) {
            m_isForceEnd = true;
        }
    }
    void LogoCtrl::onDraw() const
    {
        m_view
            ->setPos(Constants::AppResolutionF / 2.0)
            .setTime(m_timer.time0_1())
            .draw();
    }
    bool LogoCtrl::isEnd() const
    {
        return m_timer.isEnd() || m_isForceEnd;
    }
}
