#pragma once
#include <abyss/modules/GameObject/Components.hpp>
#include <abyss/components/Cron/base/IJob.hpp>
#include <abyss/modules/Room/IRoomMoveCallback.hpp>

namespace abyss::Cron::BubbleGenerator
{
	class Generator final: 
		public IComponent,
		public IJob,
		public Room::IRoomMoveCallback
	{
	public:
		Generator(Manager* pManager);

		void onStart() override;
		Coro::Task<> onExecute() override;

		void onCheckOut() override;
		void onCheckIn() override;
	private:
		Ref<Effect::EffectObj> buildEffect(const s3d::Optional<s3d::RectF>& area = s3d::none);
	private:
		Manager* m_pManager;
		s3d::int32 m_count = 0;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Cron::BubbleGenerator::Generator>
	{
		using Base = MultiComponents<
			Cron::IJob,
			Room::IRoomMoveCallback
		>;
	};
}