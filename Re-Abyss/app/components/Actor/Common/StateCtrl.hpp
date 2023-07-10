#pragma once
#include <Siv3D/Optional.hpp>
#include <Siv3D/Uncopyable.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPostCollision.hpp>
#include <abyss/modules/Actor/base/IPreUpdate.hpp>
#include <abyss/modules/Actor/base/IPostUpdate.hpp>
#include <abyss/modules/Actor/base/ILastUpdate.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss::Actor
{
    class StateCtrl;
    using Coro::Fiber;

    using StatePriorityType = s3d::int32;

    class IState
    {
    private:
        StateCtrl* m_manager;
    protected:
        ActorObj* m_pActor = nullptr;

        template<class State, class... Args>
        void changeState(Args&&... args) const;

        template<class State, StatePriorityType priority, class... Args>
        void changeState(Args&&... args) const;
    public:
        IState()=default;
        virtual ~IState() = default;

        void init(StateCtrl* manager);

        virtual void onCache() {}

        virtual void start() {}
        virtual Fiber<void> updateAsync() { co_return; }
        virtual void update() {}
        virtual void lastUpdate() {}
        virtual void end() {}
    };

    class StateCtrl :
        public IComponent,
        public IPreUpdate,
        public IPostUpdate,
        public ILastUpdate,
        public IPostCollision
    {
    private:
        using State_t = std::shared_ptr<IState>;
    public:
        StateCtrl(ActorObj* pActor);
        
        void setup(Executer executer)override;
        void onStart() override;
        void onEnd() override;

        void onPreUpdate() override;
        void onPostUpdate() override;

        void onLastUpdate() override;

        void onPostCollision() override;

        void stateUpdate();

        void changeState(const std::shared_ptr<IState>& next, StatePriorityType priority = 0);

        template<class State, class... Args>
        void changeState(Args&&... args)
        {
            changeState(std::make_shared<State>(std::forward<Args>(args)...), 0);
        }

        template<class State, StatePriorityType priority, class... Args>
        void changeState(Args&&... args)
        {
            changeState(std::make_shared<State>(std::forward<Args>(args)...), priority);
        }

        inline ActorObj* getActor() const
        {
            return m_pActor;
        }

        template<class State>
        bool isState() const
        {
            return dynamic_cast<State*>(m_current.get()) != nullptr;
        }

    private:
        ActorObj* const  m_pActor;
        State_t m_current;
        std::pair<StatePriorityType, State_t> m_next;
        std::shared_ptr<IPostCollision> m_collisionReact;
        Coro::FiberHolder<void> m_task;
        bool m_doneOnStart = false;
    };

    template<class State, class... Args>
    void IState::changeState(Args&&... args) const
    {
        m_manager->changeState<State>(std::forward<Args>(args)...);
    }

    template<class State, StatePriorityType priority, class... Args>
    void IState::changeState(Args&&... args) const
    {
        m_manager->changeState<State, priority>(std::forward<Args>(args)...);
    }
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::StateCtrl>
    {
        using Base = MultiComponents<
            Actor::IPreUpdate,
            Actor::IPostUpdate,
            Actor::ILastUpdate,
            Actor::IPostCollision
        >;
    };
}
