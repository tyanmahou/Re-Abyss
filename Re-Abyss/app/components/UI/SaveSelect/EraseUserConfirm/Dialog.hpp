#pragma once
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/components/UI/Dialog/DialogResult.hpp>
#include <abyss/components/UI/SaveSelect/EraseUserConfirm/Result.hpp>

#include <abyss/views/UI/Message/CursorVM.hpp>

namespace abyss::UI::SaveSelect::EraseUserConfirm
{
    struct Dialog :
        public UI::Dialog::DialogResult<Result>,
        public IUpdate,
        public IDraw
    {
    public:
        static void Build(UIObj* pUi);
    public:
        Dialog(UIObj* pUi);

        void onUpdate() override;
        void onDraw() const override;
    private:
        UIObj* m_pUi;
        bool m_yes = false;
        std::unique_ptr<UI::Message::CursorVM> m_cursor;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::SaveSelect::EraseUserConfirm::Dialog>
    {
        using Base = MultiComponents<
            UI::IUpdate,
            UI::IDraw,
            UI::Dialog::DialogResult<UI::SaveSelect::EraseUserConfirm::Result>
        >;
    };
}
