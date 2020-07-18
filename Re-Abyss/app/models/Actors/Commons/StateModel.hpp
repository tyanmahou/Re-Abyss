#pragma once
# include <Siv3D/Optional.hpp>
# include <Siv3D/Uncopyable.hpp>
# include <Siv3D/HashTable.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>
# include <abyss/models/Actors/base/IComponent.hpp>
# include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>
# include <abyss/models/Actors/base/IUpdateModel.hpp>
# include <abyss/models/Actors/base/ILastUpdateModel.hpp>
# include <abyss/models/Actors/base/IDrawModel.hpp>

namespace abyss
{
    class StateModel;

    class IState
    {
    private:
        StateModel* m_manager;
    protected:
        IActor* m_pActor = nullptr;

        template<class State, class... Args>
        void changeState(Args&&... args) const;

    public:
        IState()=default;
        virtual ~IState() = default;

        void init(StateModel* manager);

        virtual void setup() {}

        virtual void start(){}
        virtual void update([[maybe_unused]] double dt) {}
        virtual void lastUpdate() {}
        virtual void end() {}
    };

    class StateModel :
        public IComponent,
        public IUpdateModel,
        public ILastUpdateModel
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
        StateModel(IActor* pActor):
            m_pActor(pActor)
        {}

        void setup() override
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
    struct ComponentTree<StateModel>
    {
        using Base = MultiComponents<
            IUpdateModel,
            ILastUpdateModel
        >;
    };
}