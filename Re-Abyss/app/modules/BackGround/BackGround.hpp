#pragma once

#include <abyss/views/BackGround/BackGroundView.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class BackGround
    {
    private:
        BackGroundView m_view;
    public:
        BackGround() = default;
        void add(const BackGroundVM& backGround);
        void draw(const CameraView& camera) const;
    };
}