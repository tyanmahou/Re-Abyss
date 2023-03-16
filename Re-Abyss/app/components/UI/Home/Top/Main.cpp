#include <abyss/components/UI/Home/Top/Main.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/components/UI/Home/Top/ModeUtil.hpp>
#include <abyss/components/Cycle/Home/Master.hpp>
#include <abyss/views/UI/Home/Top/TopView.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/commons/MsgUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Home::Top
{
    Main::Main(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<TopView>())
    {
        ModeUtil::ForEach([&](Mode mode) {
            m_modeLocked[mode] = ModeUtil::IsLocked(pUi, mode);
            m_view->setLock(mode, m_modeLocked[mode]);
        });

        m_fiber.reset(std::bind(& Main::onUpdateAysnc, this));
    }
    Main::~Main()
    {
    }
    void Main::onStart()
    {
        m_tips =m_pUi->find<FooterTips>();
    }
    void Main::onUpdate()
    {
        m_fiber.resume();
        if (m_inAnime.isEnd()) {
            m_time += m_pUi->deltaTime();
            // Tips更新
            m_tips->setTips(
                m_modeLocked[m_mode]
                ? MsgUtil::Home_Tips_Unlock()
                : MsgUtil::Home(U"Tips_Mode_{}"_fmt(Enum::ToStr(m_mode)))()
            );
        }
    }
    Coro::Fiber<> Main::onUpdateAysnc()
    {
        // Inアニメ再生
        while (!m_inAnime.isEnd())
        {
            m_inAnime.update(m_pUi->deltaTime());
            co_yield{};
        }
        while (true)
        {
            // Modeの変更
            {
                auto modePrev = m_mode;
                m_mode = m_modeUpdater.update(m_mode);

                if (m_mode != modePrev) {
                    m_time = 0;
                }
            }
            if (InputManager::B.down()) {
                // 戻る
                m_pUi->getModule<CycleMaster>()->find<Cycle::Home::Master>()->back();
                co_return;
            }
            co_yield{};
        }
    }
    void Main::onDraw() const
    {
        m_view
            ->setTime(m_time)
            .setInAnimeRate(m_inAnime.rate())
            .setMode(m_mode)
            .draw();
    }
}
