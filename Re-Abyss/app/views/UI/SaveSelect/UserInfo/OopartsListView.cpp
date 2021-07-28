#include "OopartsListView.hpp"
#include <Siv3D.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Constants.hpp>

namespace abyss::UI::SaveSelect::UserInfo
{
    OopartsListView::OopartsListView():
        m_rt(Constants::AppResolution)
    {
    
    }
    void OopartsListView::draw() const
    {
        m_rt.clear(ColorF(0.0, 0.0));

        {
            static BlendState blend{
                true,
                Blend::SrcAlpha,
                Blend::InvSrcAlpha,
                BlendOp::Add,
                Blend::One,
                Blend::Zero
            };
            ScopedRenderStates2D scopedBlend(blend);
            ScopedRenderTarget2D scopedRt(m_rt);
            for (auto&& [index, type] : s3d::Indexed(m_having)) {
                auto pos = m_pos + s3d::Vec2{ m_offsetX * (index), 0 };
                m_icon(type).resized(40, 40).draw(pos);
            }
        }
        {
            Transformer2D transLocal(Mat3x2::Identity(), Transformer2D::Target::SetLocal);
            Transformer2D transCamera(Mat3x2::Identity(), Transformer2D::Target::SetCamera);

            auto shader = m_outLineShader
                .setTextureSize(Constants::AppResolution)
                .setOutLineSize(1.0)
                .setColor(s3d::Palette::White)
                .start();
            m_rt.draw();
        }
    }
}
