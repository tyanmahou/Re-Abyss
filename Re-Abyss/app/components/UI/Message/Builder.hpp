#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Adv
{
    class SentenceCtrl;
}
namespace abyss::UI::Message
{
    struct Builder
    {
        static void Build(
            UIObj* pUi,
            const Ref<Adv::SentenceCtrl>& sentence
        );
    };
}
