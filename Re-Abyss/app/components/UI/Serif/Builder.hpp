#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::ui::Serif
{
    struct Builder
    {
        static void Build(
            IUserInterface* pUi,
            const Ref<Event::Talk::SerifCtrl>& serif,
            const Ref<Event::Talk::FaceTable>& faceTable
        );
    };
}