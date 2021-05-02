#include "DrawManager.hpp"

namespace abyss
{
    void DrawManager::clear()
    {
        for (auto& drawers : m_drawers) {
            drawers.clear();
        }
    }
    void DrawManager::add(DrawLayer layer, std::function<void()> drawer)
    {
        m_drawers[static_cast<size_t>(layer)].push_back(drawer);
    }
    void DrawManager::draw(DrawLayer layer) const
    {
        for (auto& drawer : m_drawers[static_cast<size_t>(layer)]) {
            drawer();
        }
    }
}
