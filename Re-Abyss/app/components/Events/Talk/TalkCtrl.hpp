#pragma once
#include <queue>
#include <memory>

#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Events/base/IStream.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Event::Talk
{
    class TalkObj;

    template<class Type, class... Args>
    concept TalkBuildy = requires(TalkObj* pTalk, Args&&... args)
    {
        Type::Build(pTalk, std::forward<Args>(args)...);
    };

    class TalkCtrl :
        public IComponent,
        public IStream
    {
    public:
        TalkCtrl(IEvent* pEvent);

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;

        Coro::Task<> onExecute() override;

        /// <summary>
        /// 会話の生成
        /// </summary>
        /// <returns></returns>
        Ref<TalkObj> create();

        /// <summary>
        /// ビルダーから会話の生成
        /// </summary>
        template<class BuilerType, class... Args>
        Ref<TalkObj> create(Args&& ... args)
            requires TalkBuildy<BuilerType, Args...>
        {
            auto event = this->create();
            BuilerType::Build(event.get(), std::forward<Args>(args)...);
            return event;
        }

        /// <summary>
        /// 会話の登録
        /// </summary>
        /// <param name="event"></param>
        /// <returns></returns>
        Ref<TalkObj> regist(const std::shared_ptr<TalkObj>& talk);
    private:
        IEvent* m_pEvent;

        std::queue<std::shared_ptr<TalkObj>> m_talks;
        bool m_doneCurrentInit = false;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::Talk::TalkCtrl>
    {
        using Base = MultiComponents<
            Event::IStream
        >;
    };
}