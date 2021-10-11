#pragma once
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/components/UI/Dialog/DialogResult.hpp>
#include <abyss/components/UI/SaveSelect/CreateUserConfirm/Result.hpp>

#include <abyss/views/UI/Serif/CursorVM.hpp>

namespace abyss::UI::SaveSelect::CreateUserConfirm
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
        UserPlayMode m_playMode = UserPlayMode::Normal;
        std::unique_ptr<UI::Serif::CursorVM> m_cursor;
    };
}