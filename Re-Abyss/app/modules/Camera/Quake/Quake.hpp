#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/modules/Camera/Quake/QuakeEpicenter.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class Quake
    {
        s3d::Array<std::shared_ptr<QuakeEpicenter>> m_quakes;
        s3d::Vec2 m_offset{0, 0};
    public:
        void add(const std::shared_ptr<QuakeEpicenter>& quake);

        void stopAll();

        void update(double dt);

        bool isEnd() const;

        const s3d::Vec2& getOffset()const
        {
            return m_offset;
        }
    };
}
