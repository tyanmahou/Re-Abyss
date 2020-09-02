#pragma once
#include <Siv3D/Fwd.hpp>
namespace abyss::Ooparts
{
    class IDrawCallbackView
    {
    public:
        virtual ~IDrawCallbackView() = default;

        virtual void onDraw(const s3d::Vec2& pos) const = 0;
    };
}