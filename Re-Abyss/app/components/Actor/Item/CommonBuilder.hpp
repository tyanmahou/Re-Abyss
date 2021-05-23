#pragma once

#include <Siv3D/Vector2D.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/StateCtrl.hpp>

namespace abyss::Actor::Item
{
    struct BuildOption
    {
        friend struct CommonBuilder;
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
        // body
        s3d::Vec2 pos;
        s3d::Vec2 bodySize;
        std::shared_ptr<IState> initState = nullptr;
    };
    struct CommonBuilder
    {
    public:
        static void Build(ActorObj* pActor, const BuildOption& opt = BuildOption{});
    };
}