#include "Quake.hpp"
#include <Siv3D.hpp>
#include <abyss/models/Camera/QuakeModel.hpp>

namespace abyss
{
    void Quake::add(const std::shared_ptr<QuakeModel>& quake)
    {
        m_quakes.push_back(quake);
    }

    void Quake::stopAll()
    {
        m_quakes.clear();
    }

    s3d::Vec2 Quake::apply(const s3d::Vec2& pos)
    {
        Vec2 offset{ 0, 0 };
        for (const auto& quake : m_quakes) {
            quake->update();
            offset += quake->getOffset();
        }
        m_quakes.remove_if([](const std::shared_ptr<QuakeModel>& quake) {
            return quake->isEnd();
        });
        return pos + offset;
    }
    bool Quake::isEnd() const
    {
        return m_quakes.empty();
    }
}
