#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    class DisappearStart :
        public ICommand
    {
    public:
        DisappearStart(AdvObj* pObj);

        void onStart() override;

        Coro::Fiber<> onCommand() override;

    private:
        AdvObj* m_pObj;
    };
}
