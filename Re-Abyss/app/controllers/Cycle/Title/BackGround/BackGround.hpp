#pragma once
#include <memory>

namespace abyss::Cycle::Title::BackGround
{
    class BackGroundModel;
    class BackGroundVM;

    class BackGround
    {
        std::unique_ptr<BackGroundModel> m_model;
        std::unique_ptr<BackGroundVM> m_view;
    public:
        BackGround();
        ~BackGround();

        bool isEnd() const;

        void update();
        void draw()const;
    };
}