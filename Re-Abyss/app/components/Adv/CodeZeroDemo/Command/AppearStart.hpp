#pragma once
#include <abyss/commons/Fwd.hpp>

#include <abyss/modules/Adv/base/ICommand.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    class AppearStart :
        public ICommand
    {
    public:
        AppearStart(AdvObj* pObj);

        void onStart() override;

        Coro::Fiber<> onCommand() override;

    private:
        AdvObj* m_pObj;
    };
}
