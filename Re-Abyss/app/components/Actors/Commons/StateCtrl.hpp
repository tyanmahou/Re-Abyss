#pragma once
# include <Siv3D/Optional.hpp>
# include <Siv3D/Uncopyable.hpp>
# include <Siv3D/HashTable.hpp>

# include <abyss/controllers/Actors/base/IActor.hpp>
# include <abyss/components/base/IComponent.hpp>
# include <abyss/components/Actors/base/ICollisionCallback.hpp>
# include <abyss/components/Actors/base/IUpdate.hpp>
# include <abyss/components/Actors/base/ILastUpdate.hpp>
# include <abyss/components/Actors/base/IDraw.hpp>
# include <abyss/components/Actors/base/ICollisionCallback.hpp>

namespace abyss::Actor
{
    class StateCtrl;

    class IState
    {
    private:
        StateCtrl* m_manager;
    protected:
        IActor* m_pActor = nullptr;

        template<class State, class... Args>
        void changeState(Args&&... args) const;

    public:
        IState()=default;
        virtual ~IState() = default;

        void init(StateCtrl* manager);

        virtual void setup() {}

        virtual void start(){}
        virtual void update([[maybe_unused]] double dt) {}
        virtual void lastUpdate() {}
        virtual void end() {}

        virtual void draw() const {}

        virtual void onReflesh() {}
        virtual void onCollisionEnter([[maybe_unused]]IActor* pActor) {}
        virtual void onCollisionStay([[maybe_unused]] IActor* pActor) {}
        virtual void onCollisionExit([[maybe_unused]] IActor* pActor) {}
    };

    class StateCtrl :
        public IComponent,
        public IUpdate,
        public ILastUpdate,
        public IDraw,
        public ICollisionCallback
    {
    private:
        using State_t = std::shared_ptr<IState>;

        State_t m_current;
        State_t m_next;

        IActor* const  m_pActor;

        void stateUpdate()
        {
            if (m_next) {
                if (m_current) {
                    m_current->end();
                }
                m_current = m_next;
                m_current->init(this);
                m_next = nullptr;
            }
        }
    public:
        StateCtrl(IActor* pActor):
            m_pActor(pActor)
        {}

        void setup() override
        {
        }

        void onStart() override
        {
            this->stateUpdate();
        }
        void onUpdate(double dt) override
        {
            this->stateUpdate();
            if (m_current) {
                m_current->update(dt);
            }
        }
        void onLastUpdate() override
        {
            if (m_current) {
                m_current->lastUpdate();
            }
        }

        void onDraw() const override
        {
            if (m_current) {
                m_current->draw();
            }
        }

        void onReflesh() override
        {
            if (m_current) {
                m_current->onReflesh();
            }
        }

        void onCollisionEnter(IActor* pActor) override
        {
            if (m_current) {
                m_current->onCollisionEnter(pActor);
            }
        }

        void onCollisionStay(IActor* pActor) override
        {
            if (m_current) {
                m_current->onCollisionStay(pActor);
            }
        }

        void onCollisionExit(IActor* pActor) override
        {
            if (m_current) {
                m_current->onCollisionExit(pActor);
            }
        }
        
        void changeState(const std::shared_ptr<IState>& next)
        {
            m_next = next;
        }
        template<class State, class... Args>
        void changeState(Args&&... args)
        {
            changeState(std::make_shared<State>(std::forward<Args>(args)...));
        }

        IActor* getActor()const
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
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::StateCtrl>
    {
        using Base = MultiComponents<
            Actor::IUpdate,
            Actor::ILastUpdate,
            Actor::IDraw,
            Actor::ICollisionCallback
        >;
    };
}