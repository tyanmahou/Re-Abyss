#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/UI/Message/Main.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Adv
{
    class MessageBox : public IComponent
    {
    public:
        MessageBox(AdvObj* pTalk);

        void onStart() override;

        const Ref<UI::UIObj>& getUi() const
        {
            return m_pUi;
        }

        void setVisible(bool isVisible);
        bool isBusyAnim() const;
        void animToTail() const;
    private:
        AdvObj* m_pTalk;
        Ref<UI::UIObj> m_pUi;
        Ref<UI::Message::Main> m_msgMain;

        bool m_isVisible = false;
    };
}
