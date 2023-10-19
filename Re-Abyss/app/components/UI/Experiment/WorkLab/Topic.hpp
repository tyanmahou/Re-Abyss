#pragma once
#if ABYSS_DEVELOP
#include <abyss/components/UI/Experiment/ITopic.hpp>
#include <abyss/views/Shader/BossArrival/BossArrivalShader.hpp>

namespace abyss::UI::Experiment::WorkLab
{
    class Topic : public ITopic
    {
    public:
        Topic();

        void update() override;
        void draw() const override;
    private:
        BossArrivalShader m_shader;
        s3d::Timer m_timer;
    };
}
#endif
