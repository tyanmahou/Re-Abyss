#pragma once
#include <abyss/views/actors/Enemy/Slime/SlimeVM.hpp>

namespace abyss::Cycle
{
    class LoadingView
    {
    public:
        LoadingView();
        LoadingView& setProgress(double progress);
        void draw() const;
    private:
        std::unique_ptr<Actor::Enemy::Slime::SlimeVM> m_slime;
        double m_progress = 1.0;
    };
}