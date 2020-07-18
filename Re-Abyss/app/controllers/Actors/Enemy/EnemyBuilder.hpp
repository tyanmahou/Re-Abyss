#pragma once
#include <functional>
#include <Siv3D/String.hpp>

#include <abyss/types/Forward.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/StateModel.hpp>

namespace abyss::Enemy
{
    class EnemyBuilder
    {
    private:
        EnemyActor* m_pActor;

        // body
        s3d::Vec2 m_pos;
        s3d::Vec2 m_bodySize;
        s3d::Vec2 m_bodyPivot;
        Forward m_forward;

        // hp
        s3d::int32 m_initHp;

        // collder
        bool m_isEnableCollider = true;
        std::function<CShape()> m_colliderFunc;

        // map collider
        bool m_isEnableMapCollider = true;
        bool m_isEnableRoomHit = false;
        bool m_isEnableRoomHitStrict = false;

        // audio sourece
        s3d::String m_audioSettingGroupPath;

        // damage
        bool m_isEnableDamage = true;

        // deadcallabck
        bool m_isEnableDeadCallback = true;

        // breathing
        bool m_isEnableBreathing = true;

        bool m_isAutoDestroy = true;

        std::shared_ptr<IState> m_initState = nullptr;
    public:
        EnemyBuilder(EnemyActor* pActor);

        EnemyBuilder& setInitPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        EnemyBuilder& setBodySize(const s3d::Vec2& size)
        {
            m_bodySize = size;
            return *this;
        }
        EnemyBuilder& setBodyPivot(const s3d::Vec2& pivot)
        {
            m_bodyPivot = pivot;
            return *this;
        }
        EnemyBuilder& setForward(Forward forward)
        {
            m_forward = forward;
            return *this;
        }
        EnemyBuilder& setInitHp(s3d::int32 hp)
        {
            m_initHp = hp;
            return *this;
        }
        EnemyBuilder& setIsEnableCollider(bool enable)
        {
            m_isEnableCollider = enable;
            return *this;
        }
        EnemyBuilder& setColliderFunc(const std::function<CShape()>& func)
        {
            m_colliderFunc = func;
            return *this;
        }
        EnemyBuilder& setIsEnableMapCollider(bool enable)
        {
            m_isEnableMapCollider = enable;
            return *this;
        }
        EnemyBuilder& setIsEnableRoomHit(bool enable, bool isStrict = false)
        {
            m_isEnableRoomHit = enable;
            m_isEnableRoomHitStrict = isStrict;
            return *this;
        }
        EnemyBuilder& setAudioSettingGroupPath(const s3d::String& path)
        {
            m_audioSettingGroupPath = path;
            return *this;
        }
        EnemyBuilder& setIsEnableDamage(bool enable)
        {
            m_isEnableDamage = enable;
            return *this;
        }
        EnemyBuilder& setIsEnableDeadCallback(bool enable)
        {
            m_isEnableDeadCallback = enable;
            return *this;
        }
        EnemyBuilder& setIsEnableBreathing(bool enable)
        {
            m_isEnableBreathing = enable;
            return *this;
        }

        EnemyBuilder& setIsAutoDestroy(bool isAuto)
        {
            m_isAutoDestroy = isAuto;
            return *this;
        }

        EnemyBuilder& setInitState(const std::shared_ptr<IState>& initState)
        {
            m_initState = initState;
            return *this;
        }

        template<class State, class... Args>
        EnemyBuilder& setInitState(Args&&... args)
        {
            return setInitState(std::make_shared<State>(std::forward<Args>(args)...));
        }
        void build() const;
    };
}