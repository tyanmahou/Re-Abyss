#pragma once
#include <Siv3D/String.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    class Main :
        public IComponent
    {
    public:
        Main(ActorObj* pActor, const s3d::String& path, s3d::uint32 eventId);
        void onStart() override;
    private:
        ActorObj* m_pActor;
        s3d::String m_path;
        s3d::uint32 m_eventId;
    };
}
