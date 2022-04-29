#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IDraw.hpp>

namespace abyss::Actor
{
	class IBossFadeMaskDrawer
	{
	public:
		virtual ~IBossFadeMaskDrawer() = default;

		virtual void setup([[maybe_unused]] Executer executer) {}
		virtual void onStart() = 0;
		virtual void onDraw() const = 0;
	};

	class BossFadeMask:
		public IComponent,
		public IDraw
	{
	public:
        BossFadeMask(ActorObj* pActor);

        template<class Type, class...Args>
        BossFadeMask& setDrawer(Args&&... args)
        {
            return setDrawer(std::make_shared<Type>(std::forward<Args>(args)...));
        }
        BossFadeMask& setDrawer(const std::shared_ptr<IBossFadeMaskDrawer>& drawer)
        {
            m_drawer = drawer;
            return *this;
        }
    public:
        void setup(Executer executer) override;

        void onStart() override;
		void onDraw() const override;
    private:
        ActorObj* m_pActor;
        std::shared_ptr<IBossFadeMaskDrawer> m_drawer;
	};
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::BossFadeMask>
    {
        using Base = Actor::IDraw;
    };
}