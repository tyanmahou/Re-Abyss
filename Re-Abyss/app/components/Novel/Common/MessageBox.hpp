#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>

namespace abyss::Novel
{
    class MessageBox : public IComponent
    {
    public:
        MessageBox(TalkObj* pTalk);

        void onStart() override;
    private:
        TalkObj* m_pTalk;
    };
}