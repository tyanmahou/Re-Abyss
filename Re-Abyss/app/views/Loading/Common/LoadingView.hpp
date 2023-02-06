#pragma once
#include <abyss/views/Actor/Enemy/Slime/SlimeVM.hpp>

namespace abyss::Loading::Common
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
