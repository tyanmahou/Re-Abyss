#pragma once
#include <Siv3D/String.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>

namespace abyss::EventTrigger
{
    class MainModel :
        public IComponent
    {
    private:
        IActor* m_pActor;
        s3d::String m_path;
    public:
        MainModel(IActor* pActor, const s3d::String& path);
        void onStart() override;
    };
}
