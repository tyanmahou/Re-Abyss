#include "MaskUtil.hpp"
#include <abyss/commons/Constants.hpp>
#include <Siv3D.hpp>
namespace abyss
{
    void MaskUtil::Draw(
        std::function<void()> mask,
        std::function<void()> drawer,
        MaskFunc func
    ) {
        constexpr auto screenSize = Constants::AppResolution;
        constexpr uint32 width = screenSize.x;
        constexpr uint32 height = screenSize.y;
        static RenderTexture rt(width, height);
        static RenderTexture rt2(width, height);
        static const PixelShader notEqualPs(U"resources/shaders/not_equal_mask.hlsl", { { U"PSConstants2D", 0 } });

		rt.clear(ColorF(1.0, 1.0));
		{
			ScopedRenderTarget2D target(rt);
			mask();
		}
		rt2.clear(ColorF(0.0, 0.0));
		{
			static BlendState blend {
				true, 
				Blend::SrcAlpha,
				Blend::InvSrcAlpha, 
				BlendOp::Add,
				Blend::SrcAlpha,
				Blend::InvSrcAlpha
			};
			ScopedRenderStates2D state(blend);
			ScopedRenderTarget2D target(rt2);
			drawer();
		}
		Graphics2D::SetTexture(1, rt);
		{
			ScopedCustomShader2D shader(notEqualPs);
			rt2.draw(Graphics2D::GetLocalTransform().inversed().transform(Vec2{0, 0}));
		}
    }
}
