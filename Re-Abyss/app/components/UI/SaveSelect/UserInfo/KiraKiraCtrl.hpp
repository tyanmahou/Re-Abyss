#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IPostUpdate.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/Actor/Ooparts/KiraKiraAlgorithm.hpp>

namespace abyss::UI::SaveSelect::UserInfo
{
    class KiraKiraCtrl :
        public IComponent,
        public IUpdate,
        public IPostUpdate
    {
    public:
        KiraKiraCtrl(UIObj* pUi);

        void onStart() override;
        void onUpdate() override;
        void onPostUpdate() override;

        KiraKiraCtrl& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        KiraKiraCtrl& setActive(bool isActive)
        {
            m_isActive = isActive;

            return *this;
        }
        KiraKiraCtrl& releaseOneShot()
        {
            m_releaseOneShot = true;

            return *this;
        }
    private:
        UIObj* m_pUi;

        bool m_isActive = false;
        bool m_releaseOneShot = false;
        s3d::Vec2 m_pos{ 0, 0 };
        Actor::Ooparts::KiraKiraAlgorithm m_algo;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<UI::SaveSelect::UserInfo::KiraKiraCtrl>
    {
        using Base = MultiComponents<
            UI::IUpdate,
            UI::IPostUpdate
        >;
    };
}