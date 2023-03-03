#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <abyss/modules/Adv/base/SkipCtrl.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Adv
{
    class Process final : public IComponent
    {
    public:
        Process(AdvObj* pObj);

        bool update();

        template<class T, class ... Args>
        void addCommand(Args&&... args)
        {
            addCommand(std::make_shared<T>(m_pObj, std::forward<Args>(args)...));
        }
        void addCommand(std::function<void(AdvObj*)> callback);

        void addCommand(std::shared_ptr<ICommand> command);
    public:
        void onStart() override;
        void onEnd() override;
    private:
        void resetStream();
    private:
        AdvObj* m_pObj;

        // コマンド
        Coro::FiberHolder<> m_stream;
        std::queue<std::shared_ptr<ICommand>> m_commands;
        bool m_doneCurrentInit = false;

        Ref<SkipCtrl> m_skip;
    };
}
