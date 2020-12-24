#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::ui::Serif
{
    struct Builder
    {
        static void Build(IUserInterface* pUi, Event::Talk::TalkObj* pTalk);
    };
}