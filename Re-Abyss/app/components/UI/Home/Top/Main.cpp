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
        this->updateTips();
        while (true)
        {
            // Modeの変更
            {
                auto modePrev = m_mode;
                m_mode = m_modeUpdater.update(m_mode);

                if (m_mode != modePrev) {
                    m_time = 0;

                    // Tips更新
                    this->updateTips();
                }
            }
            if (!m_modeLocked[m_mode] && InputManager::A.down()) {
                switch (m_mode)
                {
                case Mode::Seek:
                    co_await this->onSeek();
                    break;
                case Mode::Guild:
                    co_await this->onGuild();
                    break;
                case Mode::Maint:
                    co_await this->onMaint();
                    break;
                case Mode::Memory:
                    co_await this->onMemory();
                    break;
                case Mode::Collect:
                    co_await this->onCollect();
                    break;
                case Mode::Option:
                    co_await this->onOption();
                    break;
                default:
                    break;
                }
            } else if (InputManager::B.down()) {
                // 戻る
                m_pUi->getModule<CycleMaster>()->find<Cycle::Home::Master>()->back();
                co_return;
            }
            co_yield{};
        }
    }
    Coro::Fiber<> Main::onSeek()
    {
        // TODO 実装
        co_return;
    }
    Coro::Fiber<> Main::onGuild()
    {
        // TODO 実装
        co_return;
    }
    Coro::Fiber<> Main::onMaint()
    {
        // TODO 実装
        co_return;
    }
    Coro::Fiber<> Main::onMemory()
    {
        // TODO 実装
        co_return;
    }
    Coro::Fiber<> Main::onCollect()
    {
        // TODO 実装
        co_return;
    }
    Coro::Fiber<> Main::onOption()
    {
        // TODO 実装
        co_return;
    }
    void Main::updateTips()
    {
        // Tips更新
        m_tips->setTips(
            m_modeLocked[m_mode]
            ? MsgUtil::Home_Tips_Unlock()
            : MsgUtil::Home(U"Tips_Mode_{}"_fmt(Enum::ToStr(m_mode)))()
        );
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
