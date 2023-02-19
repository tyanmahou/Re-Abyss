#pragma once
#include <Siv3D/RenderTexture.hpp>
#include <abyss/views/Shader/NegaPosiInv/NegaPosiInvShader.hpp>

namespace abyss::Sfx
{
    /// <summary>
    /// ネガポジ反転
    /// </summary>
    class NegaPosiInv
    {
    public:
        NegaPosiInv();

        NegaPosiInv& setIsValid(bool isValid)
        {
            m_isValid = isValid;
            return *this;
        }
        bool isValid() const
        {
            return m_isValid;
        }

        void update();
        s3d::ScopedCustomShader2D start() const;

        void maskRecord(std::function<void()> drawer);
    private:
        NegaPosiInvShader m_shader;
        s3d::RenderTexture m_mask;
        bool m_isValid = false;
    };
}
