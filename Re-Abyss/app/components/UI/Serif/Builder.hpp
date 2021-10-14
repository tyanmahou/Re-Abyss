#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Novel
{
    class SerifCtrl;
    class FaceTable;
}
namespace abyss::UI::Serif
{
    struct Builder
    {
        static void Build(
            UIObj* pUi,
            const Ref<Novel::SerifCtrl>& serif,
            const Ref<Novel::FaceTable>& faceTable
        );
    };
}