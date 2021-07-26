#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/UI/base/IUpdate.hpp>
#include <Siv3D/Timer.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::Title::BackGround
{
    class BgCtrl final :
        public IComponent
    {
    public:
        BgCtrl(UIObj* pUi);

        void onStart() override;
        double time0_1() const;
        bool isEnd() const;

        s3d::Vec2 getPos() const;
        s3d::Vec2 getAtlantisPos() const;

    private:
        UIObj* m_pUi;
        s3d::Timer m_timer;
    };
}