#pragma once
#include <functional>
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>

#include <abyss/values/Forward.hpp>
#include <abyss/utils/Collision/ColDirection.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Common/Col/Collider/ICollider.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Enemy
{
    /// <summary>
    /// ビルドオプション
    /// </summary>
    struct BuildOption
    {
        friend struct CommonBuilder;
    public:
        BuildOption();

        BuildOption& setDeployId(const s3d::Optional<s3d::uint32>& _deployId)
        {
            this->deployId = _deployId;
            return *this;
        }

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
        BuildOption& setBodyOffset(const s3d::Vec2& offset)
        {
            this->bodyOffset = offset;
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
            this->collider = nullptr;
            return *this;
        }
        BuildOption& setCollider(const std::shared_ptr<Col::ICollider> col)
        {
            this->colliderFunc = nullptr;
            this->collider = col;
            return *this;
        }
        template<class Type, class... Args>
        BuildOption& setCollider(Args&& ... args)
        {
            return setCollider(std::make_shared<Type>(std::forward<Args>(args)...));
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
        BuildOption& setIsEnableDamage(bool enable)
        {
            this->isEnableDamage = enable;
            return *this;
        }
        BuildOption& setUseInvincibleColor(bool _useInvincibleColor)
        {
            this->useInvincibleColor = _useInvincibleColor;
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
        BuildOption& setIsEnableItemDrop(bool enable)
        {
            this->isEnableItemDrop = enable;
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

        BuildOption& setVModelPresenter(const std::shared_ptr<IVModelPresenterBase>& _vModelPresenter)
        {
            this->vModelPresenter = _vModelPresenter;
            return *this;
        }

        template<class Binder, class... Args>
        BuildOption& setVModelPresenter(Args&&... args)
        {
            return setVModelPresenter(std::make_shared<Binder>(std::forward<Args>(args)...));
        }
    private:
        s3d::Optional<s3d::uint32> deployId;

        // body
        s3d::Vec2 pos;
        s3d::Vec2 bodySize;
        s3d::Vec2 bodyOffset;
        Forward forward;

        // hp
        s3d::int32 initHp;

        // collder
        bool isEnableCollider = true;
        std::function<CShape()> colliderFunc;
        std::shared_ptr<Col::ICollider> collider;

        // map collider
        bool isEnableMapCollider = true;
        bool isEnableRoomHit = false;
        s3d::Optional<ColDirection> roomHitStrict;

        // damage
        bool isEnableDamage = true;
        bool useInvincibleColor = false;

        // deadcallabck
        bool isEnableDeadCallback = true;

        // breathing
        bool isEnableBreathing = true;

        // itemdrop
        bool isEnableItemDrop = true;

        bool isAutoDestroy = true;

        std::shared_ptr<IState> initState = nullptr;

        // view
        std::shared_ptr<IVModelPresenterBase> vModelPresenter = nullptr;
    };

    struct CommonBuilder
    {
        static void Build(ActorObj* pActor, const BuildOption& opt = BuildOption{});
    };
}
