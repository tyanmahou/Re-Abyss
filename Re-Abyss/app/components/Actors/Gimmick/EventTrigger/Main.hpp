#pragma once
#include <Siv3D/String.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    class Main :
        public IComponent
    {
    private:
        ActorObj* m_pActor;
        s3d::String m_path;
    public:
        Main(ActorObj* pActor, const s3d::String& path);
        void onStart() override;
    };
}
