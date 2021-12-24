#pragma once
#if ABYSS_DEBUG
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Devs/WorldComment/WorldComment.hpp>
#include <abyss/components/Actor/base/IUpdate.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/HP.hpp>

namespace abyss::Actor
{
    class DebugInfo :
        public IComponent,
        public IUpdate
    {
    public:
        DebugInfo(ActorObj* pActor);

        void onStart() override;
        void onUpdate() override;

    private:
        ActorObj* m_pActor;
        std::unique_ptr<WorldComment::Requestor> m_worldComment;
        Ref<Body> m_body;
        Ref<HP> m_hp;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DebugInfo>
    {
        using Base = Actor::IUpdate;
    };
}

#endif