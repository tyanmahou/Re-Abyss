#include "DrawManager.hpp"

namespace abyss
{
    void DrawManager::clear()
    {
        for (auto& drawers : m_drawers) {
            drawers.clear();
        }
    }
    void DrawManager::add(DrawLayer layer, std::function<void()> drawer, double order)
    {
        m_drawers[static_cast<size_t>(layer)].emplace_back(order, std::move(drawer));
    }
    void DrawManager::draw(DrawLayer layer)
    {
        for (auto&& target : m_drawers[static_cast<size_t>(layer)].sort()) {
            target.drawer();
        }
    }
    size_t DrawManager::size(DrawLayer layer) const
    {
        return m_drawers[static_cast<size_t>(layer)].size();
    }
}
