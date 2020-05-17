#pragma once
#include <abyss/controllers/UI/base/IUserInterface.hpp>

namespace abyss::ui
{
    class BossHPBar : public IUserInterface
    {
    public:
        BossHPBar(IActor* actor);
    };
}