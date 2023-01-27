#pragma once
#include <queue>
#include <memory>
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    template<class Type, class... Args>
    concept EventBuildable = requires(Event::EventObj * pEvent, Args&&... args)
    {
        Type::Build(pEvent, std::forward<Args>(args)...);
    };

    /// <summary>
    /// イベント管理
    /// </summary>
    class Events
    {
    public:
        Events& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }

        bool init();

        bool update();

        bool isEmpty() const;

        bool isWorldStop() const;


        /// <summary>
        /// イベントの生成
        /// </summary>
        /// <returns></returns>
        Ref<Event::EventObj> create();

        /// <summary>
        /// ビルダーからイベントの生成
        /// </summary>
        template<class BuilerType, class... Args>
        Ref<Event::EventObj> create(Args&& ... args)
            requires EventBuildable<BuilerType, Args...>
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
        Ref<Event::EventObj> regist(const std::shared_ptr<Event::EventObj>& event);

    private:
        std::queue<std::shared_ptr<Event::EventObj>> m_events;
        bool m_doneCurrentInit = false;
        Manager* m_pManager = nullptr;
    };
}
