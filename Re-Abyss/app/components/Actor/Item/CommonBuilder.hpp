#pragma once

#include <Siv3D/Vector2D.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>

namespace abyss::Actor::Item
{
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
        BuildOption& setColliderRadius(double radius)
        {
            this->m_colliderRadius = radius;
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
    private:
        s3d::Optional<s3d::uint32> deployId;

        // body
        s3d::Vec2 pos;
        s3d::Vec2 bodySize;
        s3d::Vec2 bodyOffset;

        // collider
        s3d::Optional<double> m_colliderRadius;
        std::shared_ptr<IState> initState = nullptr;
    };
    struct CommonBuilder
    {
    public:
        static void Build(ActorObj* pActor, const BuildOption& opt = BuildOption{});
    };
}
