#include <abyss/components/UI/Title/Main.hpp>

#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/Cron/BubbleGenerator/Builder.hpp>

#include <abyss/components/UI/Title/Logo/Builder.hpp>
#include <abyss/components/UI/Title/Logo/LogoCtrl.hpp>
#include <abyss/components/UI/Title/Cursor/Builder.hpp>
#include <abyss/components/UI/Title/Cursor/CursorCtrl.hpp>
#include <abyss/components/UI/Title/BackGround/Builder.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>

namespace abyss::UI::Title
{
    Main::Main(UIObj* pUi):
        m_pUi(pUi)
    {
        m_fiber.reset(std::bind(&Main::onExecute, this));
    }
    void Main::setup([[maybe_unused]]Executer executer)
    {
    }
    void Main::onStart()
    {
    }
    void Main::onEnd()
    {
    }
    void Main::onUpdate()
    {
        m_fiber.resume();
    }
    Coro::Fiber<> Main::onExecute()
    {
        auto uis = m_pUi->getModule<UIs>();

        // ロゴ演出
        auto logoCtrl = uis->create<Logo::Builder>()
            ->find<Logo::LogoCtrl>();
        co_await Coro::FiberUtil::WaitUntil([&logoCtrl]() {
            return !logoCtrl || logoCtrl->isEnd();
        });

        // カーソル生成
        auto cursor = uis->create<Cursor::Builder>()
            ->find<Cursor::CursorCtrl>();

        // 背景生成
        uis->create<UI::Title::BackGround::Builder>();

        // 停止
        co_await Coro::FiberUtil::WaitUntil([&cursor]() {
            return !cursor || cursor->isDone();
        });
    }
}
