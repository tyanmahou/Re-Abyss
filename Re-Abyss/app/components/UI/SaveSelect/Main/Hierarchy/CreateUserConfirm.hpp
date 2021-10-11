#pragma once
#include <abyss/components/UI/Common/HierarchyCtrl.hpp>
#include <abyss/models/User/UserModel.hpp>
#include <abyss/views/UI/Serif/CursorVM.hpp>

namespace abyss::UI::SaveSelect::Main
{
    class CreateUserConfirm : public IHierarchy
    {
    public:
        CreateUserConfirm(std::function<void(UserPlayMode)> callback);

        bool update() override;

        void draw() const override;

    private:
        UserPlayMode m_playMode = UserPlayMode::Normal;
        std::function<void(UserPlayMode)> m_callback;
        std::unique_ptr<UI::Serif::CursorVM> m_cursor;
        bool m_isDone = false;
    };
}