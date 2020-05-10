#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/models/Actors/base/StateModel.hpp>
#include <abyss/views/Actors/LaunShark/Shot/ShotVM.hpp>

namespace abyss::LaunShark::Shot
{
	class ShotActor :
		public IActor,
		public Attacker,
		public Receiver
	{
	public:
		enum State
		{
			Wait,
			Pursuit,
			Firinged,
		};
	private:
		Ref<BodyModel> m_body;
		Ref<RotateModel> m_rotate;
		Ref<experimental::HPModel> m_hp;
		std::shared_ptr<ShotVM> m_view;
	public:
		ShotActor(const s3d::Vec2& pos, Forward forward);
		void start() override;
		CShape getCollider() const;
		s3d::Quad getColliderQuad() const;

		bool accept(const ActVisitor& visitor) override;

		ShotVM* getBindedView()const;
	};
}