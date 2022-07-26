#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Shader/Bloom/BloomShader.hpp>

namespace abyss::Sfx
{
    class Bloom
    {
    public:
        Bloom();

        void setManager(Manager* pManager)
        {
            m_pManager = pManager;
        }

        void apply(const s3d::Texture& tex) const;

    private:
        Manager* m_pManager;
        BloomShader m_bloomShader;
    };
}
