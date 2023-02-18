#include <abyss/views/Actor/Enemy/CodeZero/Body/BodyVM.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss::Actor::Enemy::CodeZero::Body
{
    BodyVM::BodyVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/CodeZero/CodeZero.json")),
        m_rt(Constants::GameScreenSize.asPoint())
    {}

    BodyVM& BodyVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    BodyVM& BodyVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }
    BodyVM& BodyVM::setWingLPos(const s3d::Vec2& pos)
    {
        m_wingLPos = s3d::Round(pos);
        return *this;
    }
    BodyVM& BodyVM::setWingRPos(const s3d::Vec2& pos)
    {
        m_wingRPos = s3d::Round(pos);
        return *this;
    }
    void BodyVM::draw() const
    {
        {
            m_rt.clear(ColorF(0, 0));
            s3d::ScopedRenderTarget2D renderStart(m_rt);
            s3d::ScopedRenderStates2D blend(BlendState{
                true,
                Blend::SrcAlpha,
                Blend::InvSrcAlpha,
                BlendOp::Add,
                Blend::One,
                Blend::One,
                BlendOp::Max
                });

            m_texture(U"wing").drawAt(m_wingLPos);
            m_texture(U"wing").mirrored().drawAt(m_wingRPos);
            m_texture(U"body").drawAt(m_pos);
        }
        {
            Transformer2D transLocal(Mat3x2::Identity(), Transformer2D::Target::SetLocal);
            Transformer2D transCamera(Mat3x2::Identity(), Transformer2D::Target::SetCamera);
            m_rt.draw(m_colorMul);
        }
    }

}
