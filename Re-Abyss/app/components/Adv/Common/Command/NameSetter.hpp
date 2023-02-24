#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <abyss/modules/Adv/Name.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Adv
{
    class NameSetter :
        public ICommand
    {
    public:
        NameSetter(AdvObj* pTalk, const Name& name);

        void onStart() override;
        Coro::Fiber<> onCommand() override;
    private:
        AdvObj* m_pTalk = nullptr;
        Name m_name;
    };
}
