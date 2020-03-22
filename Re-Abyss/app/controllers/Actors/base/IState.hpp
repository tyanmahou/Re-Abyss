# pragma once
# include <Siv3D/Optional.hpp>
# include <Siv3D/Uncopyable.hpp>
# include <Siv3D/HashTable.hpp>
# include <abyss/controllers/Actors/base/ICollider.hpp>

namespace abyss
{

	template <class Actor, class StateKey> class StateManager;

	template <class Actor, class StateKey = typename Actor::State>
	class IState : s3d::Uncopyable
	{
	private:
		StateManager<Actor, StateKey>* m_manager;
	protected:
		Actor* m_actor;


		void changeState(const StateKey& next)
		{
			m_manager->changeState(next);
		}

		template<class Module>
		Module* binded() const
		{
			return m_manager->binded<Module>();
		}
	public:

		IState() = default;

		virtual ~IState() = default;

		virtual void setup() {}

		virtual void start() {}

		virtual void update([[maybe_unused]]double dt) {}

		virtual void end() {}
		virtual void onCollisionEnter(ICollider*) {}
		virtual void onCollisionStay(ICollider*) {}
		virtual void onCollisionExit(ICollider*) {}

		virtual void draw() const {}

		void init(StateManager<Actor, StateKey>* manager)
		{
			m_manager = manager;
			m_actor = manager->getActor();
		}
	};

	template <class Actor, class StateKey = typename Actor::State>
	class StateManager
	{
	private:

		using State = std::shared_ptr<IState<Actor, StateKey>>;

		using FactoryFunction_t = std::function<State()>;

		s3d::HashTable<StateKey, FactoryFunction_t> m_factories;

		State m_current;

		StateKey m_currentState;

		s3d::Optional<StateKey> m_nextState;

		Actor*const  m_actor;

		template<class Module>
		static inline Module Actor::* s_bind = nullptr;
	public:

		StateManager(Actor* actor): 
			m_actor(actor)
		{}

		template <class Type>
		StateManager& add(const StateKey& state)
		{
			auto factory = [=]() {
				auto state = std::make_shared<Type>();
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

		void update(double dt)
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
			if (m_current) {
				m_current->update(dt);
			}
		}

		void draw()const
		{
			if (m_current) {
				m_current->draw();
			}
		}

		void onCollisionEnter(ICollider* col)
		{
			if (m_current) {
				m_current->onCollisionEnter(col);
			}
		};
		void onCollisionStay(ICollider* col)
		{
			if (m_current) {
				m_current->onCollisionStay(col);
			}
		};
		void onCollisionExit(ICollider* col) 
		{
			if (m_current) {
				m_current->onCollisionExit(col);
			}
		};
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

		template<class Module>
		const StateManager& bind(Module Actor::* memPtr) const
		{
			s_bind<Module> = memPtr;
			return *this;
		}

		template<class Module>
		Module* binded() const
		{
			if (!s_bind<Module>) {
				return nullptr;
			}
			return &(m_actor->*s_bind<Module>);
		}
	};
}