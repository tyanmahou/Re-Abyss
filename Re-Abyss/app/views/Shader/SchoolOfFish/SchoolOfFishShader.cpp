#include <abyss/views/Shader/SchoolOfFish/SchoolOfFishShader.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    struct ShaderParam
    {
        float timer{};
        float column{};
        float row{};
        float scale{1.0f};

        Float2 pos{};
        float speed{1.0f};
        float angle{};
        Float2 textureSize{};

        float heightOffset{};
        float amplitude{};
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
            this->setTexture(Resource::Assets::Main()->loadTexturePacker(U"Effect/Misc/Fish/Fish.json")(U"fish_1"));
        }
        void setPos(const s3d::Vec2& pos)
        {
            m_cb->pos = static_cast<Float2>(pos);
        }
        void setSpeed(double speed)
        {
            m_cb->speed = static_cast<float>(speed);
        }
        void setAngle(double angle)
        {
            m_cb->angle = static_cast<float>(angle);
        }
        void setHeightOffset(double heightOffset)
        {
            m_cb->heightOffset = static_cast<float>(heightOffset);
        }
        void setAmplitude(double amplitude)
        {
            m_cb->amplitude = static_cast<float>(amplitude);
        }
        void setTime(double time)
        {
            m_cb->timer = static_cast<float>(time);
        }
        void setSize(s3d::int32 column, s3d::int32 row)
        {
            m_cb->column = static_cast<float>(column);
            m_cb->row = static_cast<float>(row);
        }
        void setScale(double scale)
        {
            m_cb->scale = static_cast<float>(scale);
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
        m_pImpl(std::make_unique<Impl>())
    {}
    SchoolOfFishShader::~SchoolOfFishShader()
    {
    }
    const SchoolOfFishShader& SchoolOfFishShader::setPos(const s3d::Vec2& pos) const
    {
        m_pImpl->setPos(pos);
        return *this;
    }
    const SchoolOfFishShader& SchoolOfFishShader::setSpeed(double speed) const
    {
        m_pImpl->setSpeed(speed);
        return *this;
    }
    const SchoolOfFishShader& SchoolOfFishShader::setAngle(double angle) const
    {
        m_pImpl->setAngle(angle);
        return *this;
    }
    const SchoolOfFishShader& SchoolOfFishShader::setHeightOffset(double heightOffset) const
    {
        m_pImpl->setHeightOffset(heightOffset);
        return *this;
    }
    const SchoolOfFishShader& SchoolOfFishShader::setAmplitude(double amplitude) const
    {
        m_pImpl->setAmplitude(amplitude);
        return *this;
    }
    const SchoolOfFishShader& SchoolOfFishShader::setTime(double time) const
    {
        m_pImpl->setTime(time);
        return *this;
    }
    const SchoolOfFishShader& SchoolOfFishShader::setSize(s3d::int32 column, s3d::int32 row) const
    {
        m_pImpl->setSize(column, row);
        return *this;
    }
    const SchoolOfFishShader& SchoolOfFishShader::setScale(double scale) const
    {
        m_pImpl->setScale(scale);
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
