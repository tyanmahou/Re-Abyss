#pragma once
#include <functional>
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/types/Forward.hpp>
#include <abyss/types/ColDirection.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>
#include <abyss/modules/Actors/base/ActorObj.hpp>

namespace abyss::Actor::Enemy
{
    /// <summary>
    /// ビルドオプション
    /// </summary>
    struct BuildOption
    {
        friend struct CommonBuilder;
    private:
        // body
        s3d::Vec2 pos;
        s3d::Vec2 bodySize;
        s3d::Vec2 bodyPivot;
        Forward forward;

        // hp
        s3d::int32 initHp;

        // collder
        bool isEnableCollider = true;
        std::function<CShape()> colliderFunc;
        std::shared_ptr<CustomCollider::IImpl> colliderImpl;

        // map collider
        bool isEnableMapCollider = true;
        bool isEnableRoomHit = false;
        s3d::Optional<ColDirection> roomHitStrict;

        // audio sourece
        s3d::String audioSettingGroupPath;

        // damage
        bool isEnableDamage = true;

        // deadcallabck
        bool isEnableDeadCallback = true;

        // breathing
        bool isEnableBreathing = true;

        bool isAutoDestroy = true;

        std::shared_ptr<IState> initState = nullptr;
    public:
        BuildOption();

        BuildOption& setInitPos(const s3d::Vec2& _pos)
        {
            this->pos = _pos;
            return *this;
        }
        BuildOption& setBodySize(const s3d::Vec2& size)
        {
            this->bodySize = size;
            return *this;
        }
        BuildOption& setBodyPivot(const s3d::Vec2& pivot)
        {
            this->bodyPivot = pivot;
            return *this;
        }
        BuildOption& setForward(Forward _forward)
        {
            this->forward = _forward;
            return *this;
        }
        BuildOption& setInitHp(s3d::int32 hp)
        {
            this->initHp = hp;
            return *this;
        }
        BuildOption& setIsEnableCollider(bool enable)
        {
            this->isEnableCollider = enable;
            return *this;
        }
        BuildOption& setColliderFunc(const std::function<CShape()>& func)
        {
            this->colliderFunc = func;
            this->colliderImpl = nullptr;
            return *this;
        }
        BuildOption& setColliderImpl(const std::shared_ptr<CustomCollider::IImpl> col)
        {
            this->colliderFunc = nullptr;
            this->colliderImpl = col;
            return *this;
        }
        template<class Type, class... Args>
        BuildOption& setColliderImpl(Args&& ... args)
        {
            return setColliderImpl(std::make_shared<Type>(std::forward<Args>(args)...));
        }
        BuildOption& setIsEnableMapCollider(bool enable)
        {
            this->isEnableMapCollider = enable;
            return *this;
        }
        BuildOption& setIsEnableRoomHit(bool enable, const s3d::Optional<ColDirection>& strict = s3d::none)
        {
            this->isEnableRoomHit = enable;
            this->roomHitStrict = strict;
            return *this;
        }
        BuildOption& setAudioSettingGroupPath(const s3d::String& path)
        {
            this->audioSettingGroupPath = path;
            return *this;
        }
        BuildOption& setIsEnableDamage(bool enable)
        {
            this->isEnableDamage = enable;
            return *this;
        }
        BuildOption& setIsEnableDeadCallback(bool enable)
        {
            this->isEnableDeadCallback = enable;
            return *this;
        }
        BuildOption& setIsEnableBreathing(bool enable)
        {
            this->isEnableBreathing = enable;
            return *this;
        }

        BuildOption& setIsAutoDestroy(bool isAuto)
        {
            this->isAutoDestroy = isAuto;
            return *this;
        }

        BuildOption& setInitState(const std::shared_ptr<IState>& _initState)
        {
            this->initState = _initState;
            return *this;
        }

        template<class State, class... Args>
        BuildOption& setInitState(Args&&... args)
        {
            return setInitState(std::make_shared<State>(std::forward<Args>(args)...));
        }
    };

    struct CommonBuilder
    {
        static void Build(ActorObj* pActor, const BuildOption& opt = BuildOption{});
    };
}