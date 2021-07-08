#include "Contacter.hpp"

namespace abyss::Physics
{
    Contacter::Contacter(GameObject* pGameObject):
        m_pGameObject(pGameObject)
    {}
    bool Contacter::isActive() const
    {
        if (m_pGameObject && !m_pGameObject->isActive()) {
            return false;
        }
        return m_isActive;
    }
    void Contacter::onCollision(const TerrainData& terrain)
    {
    
    }
}
