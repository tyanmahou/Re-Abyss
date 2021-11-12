#include "SchoolOfFishShader.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    struct ShaderParam
    {
        float timer;
        Float2 textureSize;
    };
}
namespace abyss
{
    class SchoolOfFishShader::Impl
    {
    public:
        Impl() :
            m_vs(Resource::Assets::Norelease()->load(U"school_of_fish.hlsl")),
            m_ps(Resource::Assets::Norelease()->load(U"school_of_fish.hlsl"))
        {
            this->setTexture(Resource::Assets::Main()->loadTexturePacker(U"effects/Misc/Fish/fish.json")(U"fish_1"));
        }
        void setTime(double time)
        {
            m_cb->timer = static_cast<float>(time);
        }
        void setTexture(const s3d::Texture& texture)
        {
            m_texture = texture;
            m_cb->textureSize = static_cast<Float2>(texture.size());
        }
        ScopedCustomShader2D start()
        {
            s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Vertex, 1, m_cb);
            s3d::Graphics2D::SetPSTexture(0, m_texture);
            return ScopedCustomShader2D(m_vs, m_ps);
        }
    private:
        VertexShader m_vs;
        PixelShader m_ps;
        Texture m_texture;
        ConstantBuffer<ShaderParam> m_cb;
    };

    SchoolOfFishShader::SchoolOfFishShader() :
        m_pImpl(std::make_shared<Impl>())
    {}
    const SchoolOfFishShader& SchoolOfFishShader::setTime(double time) const
    {
        m_pImpl->setTime(time);
        return *this;
    }
    const SchoolOfFishShader& SchoolOfFishShader::setTexture(const s3d::Texture& texture) const
    {
        m_pImpl->setTexture(texture);
        return *this;
    }
    s3d::ScopedCustomShader2D SchoolOfFishShader::start() const
    {
        return m_pImpl->start();
    }
}
