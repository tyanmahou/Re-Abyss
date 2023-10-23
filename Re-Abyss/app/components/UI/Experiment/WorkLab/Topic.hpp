#pragma once
#if ABYSS_DEVELOP
#include <abyss/components/UI/Experiment/ITopic.hpp>

namespace abyss::UI::Experiment::WorkLab
{
    class Topic : public ITopic
    {
    public:
        Topic();

        void update() override;
        void draw() const override;
    private:
    };
}
#endif
