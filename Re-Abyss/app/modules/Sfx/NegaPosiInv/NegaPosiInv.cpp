#include <abyss/modules/Sfx/NegaPosiInv/NegaPosiInv.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss::Sfx
{
    NegaPosiInv::NegaPosiInv() :
        m_mask(Constants::GameScreenSize.asPoint())
    {
    }
    void NegaPosiInv::update()
    {
        m_mask.clear(s3d::ColorF(0, 0));
    }
    s3d::ScopedCustomShader2D NegaPosiInv::start() const
    {
        return m_shader
            .setMaskTexture(m_mask)
            .start();
    }

    void NegaPosiInv::maskRecord(std::function<void()> drawer)
    {
        s3d::ScopedRenderTarget2D scopedRt(m_mask);
        static constexpr BlendState blend{
            true,
            Blend::Zero,
            Blend::Zero,
            BlendOp::Add,
            Blend::One,
            Blend::One,
        };
        ScopedRenderStates2D scopedState(blend);

        drawer();
    }
}
