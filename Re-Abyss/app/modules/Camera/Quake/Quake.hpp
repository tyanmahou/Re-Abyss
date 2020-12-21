#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class Quake
    {
        s3d::Array<std::shared_ptr<QuakeModel>> m_quakes;
    public:
        void add(const std::shared_ptr<QuakeModel>& quake);

        void stopAll();

        s3d::Vec2 apply(const s3d::Vec2& pos);

        bool isEnd() const;
    };
}