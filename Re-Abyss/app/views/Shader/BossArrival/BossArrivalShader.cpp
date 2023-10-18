#include <abyss/views/Shader/BossArrival/BossArrivalShader.hpp>

namespace
{
    struct ShaderParam
    {
        float timer{}; 
        Float2 pos{};
    };
}
namespace abyss
{
    class BossArrivalShader::Impl
    {
    public:
        Impl(Resource::Assets* pAsset) :
            m_vs(pAsset->load(U"boss_arrival.hlsl"))
        {
        }
        void setPos(const s3d::Vec2& pos)
        {
            m_cb->pos = static_cast<Float2>(pos);
        }
        void setTime(double time)
        {
            m_cb->timer = static_cast<float>(time);
        }
        ScopedCustomShader2D start()
        {
            s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Vertex, 1, m_cb);
            return ScopedCustomShader2D(m_vs);
        }
    private:
        VertexShader m_vs;
        ConstantBuffer<ShaderParam> m_cb;
    };

    BossArrivalShader::BossArrivalShader(Resource::Assets* pAsset):
        m_pImpl(std::make_unique<Impl>(pAsset))
    {
    }
    BossArrivalShader::~BossArrivalShader()
    {
    }
    const BossArrivalShader& BossArrivalShader::setPos(const s3d::Vec2& pos) const
    {
        m_pImpl->setPos(pos);
        return *this;
    }
    const BossArrivalShader& BossArrivalShader::setTime(double time) const
    {
        m_pImpl->setTime(time);
        return *this;
    }
    s3d::ScopedCustomShader2D BossArrivalShader::start() const
    {
        return m_pImpl->start();
    }
}
