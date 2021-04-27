#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::Serif
{
    struct Builder
    {
        static void Build(
            UIObj* pUi,
            const Ref<Event::Talk::SerifCtrl>& serif,
            const Ref<Event::Talk::FaceTable>& faceTable
        );
    };
}