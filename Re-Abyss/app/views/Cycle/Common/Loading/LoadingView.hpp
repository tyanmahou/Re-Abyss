#pragma once
#include <abyss/views/actors/Enemy/Slime/SlimeVM.hpp>

namespace abyss::Cycle
{
    class LoadingView
    {
    public:
        LoadingView();
        void draw() const;
    private:
        std::unique_ptr<Actor::Enemy::Slime::SlimeVM> m_slime;
    };
}