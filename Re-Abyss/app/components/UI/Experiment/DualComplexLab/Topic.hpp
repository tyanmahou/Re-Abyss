#pragma once
#if ABYSS_DEVELOP
#include <abyss/components/UI/Experiment/ITopic.hpp>
namespace abyss::UI::Experiment::DualComplexLab
{
    class Topic : public ITopic
    {
    public:
        void update() override;
        void draw() const override;
    };
}
#endif
