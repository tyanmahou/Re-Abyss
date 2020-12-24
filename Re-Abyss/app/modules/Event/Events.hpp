#pragma once
#include <queue>
#include <memory>
#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/Event.hpp>

namespace abyss
{
    class Events
    {
    private:
        std::queue<std::shared_ptr<Event::IEvent>> m_events;
        bool m_doneCurrentInit = false;
        Manager* m_pManager;
    public:
        Events& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }

        bool init();

        bool update(double dt);

        bool isEmpty() const;

        bool isWorldStop() const;


        /// <summary>
        /// イベントの生成
        /// </summary>
        /// <returns></returns>
        Ref<Event::IEvent> create();

        /// <summary>
        /// ビルダーからイベントの生成
        /// </summary>
        template<class BuilerType, class... Args>
        Ref<Event::IEvent> create(Args&& ... args)
            requires EventBuildy<BuilerType, Args...>
        {
            auto event = this->create();
            BuilerType::Build(event.get(), std::forward<Args>(args)...);
            return event;
        }

        /// <summary>
        /// イベントの登録
        /// </summary>
        /// <param name="event"></param>
        /// <returns></returns>
        Ref<Event::IEvent> regist(const std::shared_ptr<Event::IEvent>& event);
    };
}