#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Event::Talk
{
    class SerifModel;
    class FaceManager;
}

namespace abyss::ui::Serif
{
    struct Builder
    {
        static void Build(IUserInterface* pUi,
            const Ref<Event::Talk::SerifModel>& serif,
            const std::shared_ptr<Event::Talk::FaceManager>& faceManager
        );
    };
}