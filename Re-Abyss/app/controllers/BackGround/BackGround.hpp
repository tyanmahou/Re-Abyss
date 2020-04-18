#pragma once
#include <memory>

#include <abyss/views/BackGround/BackGroundView.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class BackGround
    {
    private:
        BackGroundView m_view;
    public:
        BackGround(const std::shared_ptr<IBackGroundService>& service);

        void draw(const CameraView& camera) const;
    };
}