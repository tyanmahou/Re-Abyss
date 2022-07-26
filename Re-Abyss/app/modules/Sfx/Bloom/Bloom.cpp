#include <abyss/modules/Sfx/Bloom/Bloom.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Light/Light.hpp>

namespace abyss::Sfx
{
    Bloom::Bloom()
    {
    }
    void Bloom::apply(const s3d::Texture& tex) const
    {
        if (auto* pLight = m_pManager->getModule<Light>()) {
            m_bloomShader.setLightColor(pLight->getColor());
        } else {
            m_bloomShader.setLightColor(Palette::White);
        }
        m_bloomShader.apply(tex);
    }
}
