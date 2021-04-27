#pragma once
# include <Siv3D/Optional.hpp>
# include <Siv3D/Uncopyable.hpp>
# include <Siv3D/HashTable.hpp>

# include <abyss/modules/Actors/base/ActorObj.hpp>
# include <abyss/components/base/IComponent.hpp>
# include <abyss/components/Actors/base/IPostCollision.hpp>
# include <abyss/components/Actors/base/IPostUpdate.hpp>
# include <abyss/components/Actors/base/ILastUpdate.hpp>
# include <abyss/components/Actors/base/IDraw.hpp>
# include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Actor
{
    class StateCtrl;
    using Coro::Task;

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

        virtual void setup() {}

        virtual Task<void> start() { co_return; }
        virtual void update() {}
        virtual void lastUpdate() {}
        virtual void end() {}

        virtual void draw() const {}
    };

    class StateCtrl :
        public IComponent,
        public IPostUpdate,
        public ILastUpdate,
        public IDraw,
        public IPostCollision
    {
    private:
        using State_t = std::shared_ptr<IState>;
        State_t m_current;
        std::pair<StatePriorityType, State_t> m_next;
        std::shared_ptr<IPostCollision> m_collisionReact;
        std::unique_ptr<Task<void>> m_startTask;

        ActorObj* const  m_pActor;
    public:
        StateCtrl(ActorObj* pActor);
        
        void setup(Executer executer)override;
        void onStart() override;

        void onPostUpdate() override;

        void onLastUpdate() override;

        void onDraw() const override;

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
            Actor::IPostUpdate,
            Actor::ILastUpdate,
            Actor::IDraw,
            Actor::IPostCollision
        >;
    };
}