#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/components/UI/SaveSelect/UserInfo/KiraKiraCtrl.hpp>
#include <abyss/views/UI/SaveSelect/UserInfo/UserInfoView.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::UI::SaveSelect::Main
{
    class UserSelector;
}
namespace abyss::UI::SaveSelect::UserInfo
{
    class ViewCtrl :
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        ViewCtrl(UIObj* pUi);

        void setup(Executer executer) override;
        void onStart() override;
        void onUpdate() override;
        void onDraw() const override;

        void resetTime()
        {
            m_time = 0.0;
        }
    private:
        UIObj* m_pUi;
        Ref<Main::UserSelector> m_selector;
        Ref<KiraKiraCtrl> m_kiraKira;

        double m_time = 0.0;
        std::unique_ptr<UserInfoView> m_view;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<UI::SaveSelect::UserInfo::ViewCtrl>
    {
        using Base = MultiComponents<
            UI::IUpdate,
            UI::IDraw
        >;
    };
}
