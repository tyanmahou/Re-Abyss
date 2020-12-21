#pragma once
#include <abyss/models/Light/LightModel.hpp>
#include <abyss/views/Light/LightView.hpp>

namespace abyss
{
    class Light
    {
    private:
        LightView m_view;
    public:
        void clear();
        void addLight(const LightModel& light);
        void draw(double dt, const CameraView& camera) const;
    };
}