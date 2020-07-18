# pragma once
# include <Siv3D/Optional.hpp>
# include <Siv3D/Uncopyable.hpp>
# include <Siv3D/HashTable.hpp>
# include <abyss/models/Actors/base/IComponent.hpp>
# include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>
# include <abyss/models/Actors/base/IUpdateModel.hpp>
# include <abyss/models/Actors/base/ILastUpdateModel.hpp>
# include <abyss/models/Actors/base/IDrawModel.hpp>

namespace abyss
{

    template <class Actor, class StateKey> class OldStateModel;

    template <class Actor, class StateKey = typename Actor::State>
    class IOldState : s3d::Uncopyable
    {
    public:
        using State = StateKey;
    private:
        OldStateModel<Actor, StateKey>* m_manager;
    protected:
        Actor* m_pActor;


        void changeState(const StateKey& next)
        {
            m_manager->changeState(next);
        }

    public:

        IOldState() = default;

        virtual ~IOldState() = default;

        virtual void setup() {}

        virtual void start() {}

        virtual void update([[maybe_unused]] double dt) {}
        virtual void lastUpdate() {}

        virtual void end() {}
        virtual void onReflesh() {}
        virtual void onCollisionEnter(IActor*) {}
        virtual void onCollisionStay(IActor*) {}
        virtual void onCollisionExit(IActor*) {}

        virtual void draw() const {}

        void init(OldStateModel<Actor, StateKey>* manager)
        {
            m_manager = manager;
            m_pActor = manager->getActor();
        }
    };

    template <class Actor, class StateKey = typename Actor::State>
    class OldStateModel : 
        public IComponent,
        public IUpdateModel,
        public ILastUpdateModel,
        public IDrawModel,
        public ICollisionCallbackModel
    {
    private:

        using State = std::shared_ptr<IOldState<Actor, StateKey>>;

        using FactoryFunction_t = std::function<State()>;

        s3d::HashTable<StateKey, FactoryFunction_t> m_factories;

        State m_current;

        StateKey m_currentState;

        s3d::Optional<StateKey> m_nextState;

        Actor* const  m_actor;

        void stateUpdate()
        {
            m_nextState.then([=](const StateKey& key) {
                if (m_current) {
                    m_current->end();
                }
                m_current = nullptr;
                m_current = m_factories[key]();
                m_currentState = key;
                m_nextState = s3d::none;
            });
        }
    public:

        OldStateModel(Actor* actor) :
            m_actor(actor)
        {}

        void setup() override
        {
            this->stateUpdate();
        }
        template <class Type>
        OldStateModel& add(const StateKey& state)
        {
            auto factory = [=]() {
                State state = std::make_shared<Type>();
                state->init(this);
                state->setup();
                state->start();
                return state;
            };

            auto it = m_factories.find(state);

            if (it != m_factories.end()) {
                it.value() = factory;
            } else {
                m_factories.emplace(state, factory);

                if (!m_nextState) {
                    m_nextState = state;
                }
            }

            return *this;
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
        void onDraw()const override
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

        void onCollisionEnter(IActor* col) override
        {
            if (m_current) {
                m_current->onCollisionEnter(col);
            }
        }
        void onCollisionStay(IActor* col) override
        {
            if (m_current) {
                m_current->onCollisionStay(col);
            }
        }
        void onCollisionExit(IActor* col) override
        {
            if (m_current) {
                m_current->onCollisionExit(col);
            }
        }
        void changeState(const StateKey& next)
        {
            m_nextState = next;
        }

        Actor* getActor()const
        {
            return m_actor;
        }

        const StateKey& getState()const
        {
            return m_currentState;
        }
    };
}

namespace abyss
{
    template<class T, class U>
    struct ComponentTree<OldStateModel<T, U>>
    {
        using Base = MultiComponents<
            IUpdateModel, 
            ILastUpdateModel, 
            IDrawModel,
            ICollisionCallbackModel
        >;
    };
}