#pragma once
#include <memory>

namespace abyss::Cycle::Title::BackGround
{
    class BackGroundModel;
    class BackGroundVM;
    class AtlantisVM;

    class BackGround
    {
        std::unique_ptr<BackGroundModel> m_model;
        std::unique_ptr<BackGroundVM> m_bgView;
        std::unique_ptr<AtlantisVM> m_atlantisView;
    public:
        BackGround();
        ~BackGround();

        bool isEnd() const;

        void update();
        void draw()const;
    };
}