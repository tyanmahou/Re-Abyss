#include <abyss/components/Actor/Enemy/KingDux/Tentacle/RetireCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/TentacleUtil.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/ReturnState.hpp>
#include <abyss/utils/Math/Math.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	RetireCtrl::RetireCtrl(ActorObj* pActor):
		m_pActor(pActor)
	{
	}
	void RetireCtrl::setup(Executer executer)
	{
		executer.on<IPostUpdate>().addAfter<BehaviorCtrl>();
		executer.on<IPostUpdate>().addBefore<StateCtrl>();
	}
	void RetireCtrl::onStart()
	{
		m_body = m_pActor->find<Body>();
		m_rotCtrl = m_pActor->find<RotateCtrl>();
		m_colCtrl = m_pActor->find<ColCtrl>();
	}
	void RetireCtrl::onPostUpdate()
	{
		if (m_isRetire && !m_isReturnState) {
			ReturnState::Change(m_pActor);
		}
	}
	void RetireCtrl::onMove()
	{
		if (!m_isActive) {
			return;
		}
		m_speed += m_accel * m_pActor->deltaTime();
		if (m_speed > 0) {
			m_speed = 0;
		}
		m_body
			->setVelocity(m_speed * m_rotCtrl->getDir9());
	}
	void RetireCtrl::onPostCollision()
	{
		if (!m_isActive) {
			return;
		}

		if (m_isRetire) {
			// 既にリタイア済み
			return;
		}
		s3d::int32 damage = 0;
		m_colCtrl->anyThen<Col::Attacker>([this, &damage](const Col::Attacker::Data& attacker) {
			damage += attacker.power;
			return true;
		});
		if (damage > 0) {
			m_speed = -s3d::Sqrt(2 * m_accel * damage * 30.0);
		}

		// ルーム距離チェック
		Optional<double> distFromRoom;
		{
			const auto& roomRegion = m_pActor->getModule<RoomManager>()->currentRoom().getRegion();

			auto dir = m_rotCtrl->getDir9();

			const auto shape = TentacleUtil::Shape(m_body->getPos(), m_rotCtrl->getRotate());

			// 下向きか
			const Forward forward = [&] {
				if (auto verticalCheck = Vec2::UnitY().dot(dir); Math::IsZeroLoose(verticalCheck)) {
					// 左右向き
					if (Vec2::UnitX().dot(dir) > 0) {
						return Forward::Right;
					} else {
						return Forward::Left;
					}
				} else if (verticalCheck > 0) {
					return Forward::Down;
				} else {
					return Forward::Up;
				}
			}();
			const auto pivot = (forward == Forward::Down || forward == Forward::Right) ? roomRegion.tl() : roomRegion.br();
			const auto pivotToTip = shape.p0 - pivot;
			const auto normal = ToVec2(forward);

			if (auto dist = normal.dot(pivotToTip); Math::IsZeroLoose(dist)) {
				distFromRoom = 0;
			} else {
				if (forward == Forward::Up && dist <= 80) {
					// 先端が地面より下になった
					m_isRetire = true;
				}
				if (auto dirDotNormal = dir.dot(normal); !Math::IsZeroLoose(dirDotNormal)) {
					distFromRoom = dist / dirDotNormal;
				}
			}
		}
		if (distFromRoom && *distFromRoom <= 200.0) {
			// 大体画面外にいった
			m_isRetire = true;
		}
	}
	void RetireCtrl::onStateStart()
	{
		m_isReturnState = false;
		m_isActive = false;
	}
}
