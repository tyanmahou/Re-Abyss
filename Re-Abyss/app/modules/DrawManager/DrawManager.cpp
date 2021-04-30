#include "DrawManager.hpp"

namespace abyss
{
    void DrawManager::add(DrawLayer layer, std::function<void()> drawer)
    {
        m_drawers[static_cast<size_t>(layer)].push_back(drawer);
    }
}
