#include <abyss/modules/Camera/Quake/Quake.hpp>
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

    void Quake::update(double dt)
    {
        Vec2 offset{ 0, 0 };
        for (const auto& quake : m_quakes) {
            quake->update(dt);
            offset += quake->getOffset();
        }
        m_quakes.remove_if([](const std::shared_ptr<QuakeModel>& quake) {
            return quake->isEnd();
        });
        m_offset = offset;
    }
    bool Quake::isEnd() const
    {
        return m_quakes.empty();
    }
}
