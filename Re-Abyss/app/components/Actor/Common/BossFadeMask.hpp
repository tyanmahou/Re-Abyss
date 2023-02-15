#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IDraw.hpp>

#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
{
	class IBossFadeMaskDrawer
	{
	public:
		virtual ~IBossFadeMaskDrawer() = default;

		virtual void setup([[maybe_unused]] Executer executer) {}
		virtual void onStart() = 0;
		virtual void onDraw() const = 0;
        virtual DrawLayer getLayer() const = 0;
        virtual double getOrder() const = 0;
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

        BossFadeMask& setRate(double rate)
        {
            m_rate = rate;
            return *this;
        }
    public:
        void setup(Executer executer) override;

        void onStart() override;
    public:
		void onDraw() const override;
        DrawLayer getLayer() const override;
        double getOrder() const override;
    private:
        ActorObj* m_pActor;
        std::shared_ptr<IBossFadeMaskDrawer> m_drawer;
        double m_rate{ 1.0 };
	};

    class BossFadeMaskFromMainVModel : public IBossFadeMaskDrawer
    {
    public:
        BossFadeMaskFromMainVModel(ActorObj* pActor);
    public:
        void setup(Executer executer) override;
        void onStart() override;

        void onDraw() const override;
        DrawLayer getLayer() const override;
        double getOrder() const override;
    private:
        ActorObj* m_pActor;
        Ref<VModel> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::BossFadeMask>
    {
        using Base = MultiComponents<Actor::IDraw>;
    };
}
