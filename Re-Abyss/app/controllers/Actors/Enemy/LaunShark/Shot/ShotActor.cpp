#include "ShotActor.hpp"

#include <abyss/models/Actors/Enemy/LaunShark/Shot/State/WaitState.hpp>
#include <abyss/models/Actors/Commons/BodyUpdaterModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Commons/DamageModel.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
#include <abyss/models/Actors/Commons/DeadOnHItReceiverModel.hpp>
#include <abyss/models/Actors/Commons/DeadCheackerModel.hpp>
#include <abyss/models/Actors/Commons/StateModel.hpp>

#include <abyss/models/Actors/Enemy/DamageCallbackModel.hpp>
#include <abyss/models/Actors/Enemy/DeadCallbackModel.hpp>

#include <abyss/models/Collision/LayerGroup.hpp>
#include <Siv3D/MathConstants.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/ShotParam.hpp>

namespace abyss::LaunShark::Shot
{
    ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward)
    {
        // 回転
        {
            m_rotate = this->attach<RotateModel>();
            if (forward == Forward::Right) {
                m_rotate->setRotate(s3d::Math::Constants::Pi);
            }
        }
        // コライダー
        {
            auto col = this->attach<CustomColliderModel>(this);
            col->setLayer(LayerGroup::Enemy);
            col->setColFunc([this] {return this->getCollider(); });
        }
        // ボディ
        {
            (m_body = this->attach<BodyModel>(this))
                ->setPos(pos)
                .noneResistanced()
                .setSize(ShotParam::Base::Size);

            this->attach<BodyUpdaterModel>(this);
        }
        // HP
        {
            this->attach<HPModel>(this)
                ->initHp(ShotParam::Base::Hp).setInvincibleTime(0.2);
        }
        // 音源
        {
            this->attach<AudioSourceModel>(this)->load(U"Enemy/LaunShark/shot.aase");
        }
        // ダメージ
        {
            this->attach<DamageModel>(this);
            this->attach<Enemy::DeadCallbackModel>(this);
        }
        // 死亡チェック
        {
            this->attach<DeadOnHItReceiverModel>(this);
            this->attach<Enemy::DamageCallbackModel>(this);
            this->attach<DeadCheckerModel>(this);
        }
        // 状態管理
        {
            this->attach<StateModel>(this)
                ->changeState<WaitState>()
                ;
        }
        // 描画
        {
            this->attach<DrawModel>(this);
        }
    }
    void ShotActor::start()
    {    
    }
    CShape ShotActor::getCollider() const
    {
        return this->getColliderQuad();
    }
    s3d::Quad ShotActor::getColliderQuad() const
    {
        return m_body->region().rotated(m_rotate->getRotate());
    }
    bool ShotActor::accept(const ActVisitor& visitor)
    {
        bool success = visitor.visit(static_cast<Attacker&>(*this));
        success |= visitor.visit(static_cast<Receiver&>(*this));
        return success || visitor.visit(static_cast<IActor&>(*this));
    }
}
