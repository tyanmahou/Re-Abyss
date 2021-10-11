#pragma once
#include <abyss/components/UI/Common/HierarchyCtrl.hpp>
#include <abyss/components/UI/SaveSelect/Main/ModeCtrl.hpp>
#include <abyss/components/UI/SaveSelect/Main/Users.hpp>
#include <abyss/components/UI/SaveSelect/Main/UserSelector.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::SaveSelect::Main
{
    class UserSelect : public IHierarchy
    {
    public:
        UserSelect(UIObj* pUi);

        void start() override;

        bool update() override;
        private:
            UIObj* m_pUi;
            Ref<ModeCtrl> m_mode;
            Ref<Users> m_users;
            Ref<UserSelector> m_selector;
    };
}