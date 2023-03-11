#include <abyss/components/UI/Title/MainStream.hpp>

#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/Cron/BubbleGenerator/Builder.hpp>

#include <abyss/components/UI/Title/Logo/Builder.hpp>
#include <abyss/components/UI/Title/Logo/LogoCtrl.hpp>
#include <abyss/components/UI/Title/Cursor/Builder.hpp>
#include <abyss/components/UI/Title/Cursor/CursorCtrl.hpp>
#include <abyss/components/UI/Title/BackGround/Builder.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

namespace abyss::UI::Title
{
    MainStream::MainStream(UIObj* pUi):
        m_pUi(pUi)
    {
        m_fiber.reset(std::bind(&MainStream::onExecute, this));
    }
    void MainStream::setup([[maybe_unused]]Executer executer)
    {
    }
    void MainStream::onStart()
    {
    }
    void MainStream::onEnd()
    {
    }
    void MainStream::onUpdate()
    {
        m_fiber.resume();
    }
    Coro::Fiber<> MainStream::onExecute()
    {
        using namespace UI::Title;
        auto uis = m_pUi->getModule<UIs>();

        // ロゴ演出
        auto logoCtrl = uis->create<Logo::Builder>()
            ->find<Logo::LogoCtrl>();
        co_await Coro::WaitUntil([&logoCtrl]() {
            return !logoCtrl || logoCtrl->isEnd();
        });

        // カーソル生成
        auto cursor = uis->create<Cursor::Builder>()
            ->find<Cursor::CursorCtrl>();

        // 背景生成
        uis->create<UI::Title::BackGround::Builder>();

        // 停止
        co_await Coro::WaitUntil([&cursor]() {
            return !cursor || cursor->isDone();
        });
    }
}
