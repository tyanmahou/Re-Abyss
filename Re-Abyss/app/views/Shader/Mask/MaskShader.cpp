#include <abyss/views/Shader/Mask/MaskShader.hpp>

#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss
{
	class MaskShader::Impl
	{
	private:
		RenderTexture m_rt;
		RenderTexture m_rt2;
		PixelShader m_maskPs;
		struct ShaderParam
		{
			s3d::int32 isEqual;
			Float3 _unused;
		};
		ConstantBuffer<ShaderParam> m_cb;
	public:
		Impl(uint32 width, uint32 height) :
			m_rt(width, height),
			m_rt2(width, height),
			m_maskPs(Resource::Assets::Norelease()->load(U"mask.hlsl"))
		{}

		void draw(MaskFunc func, const std::function<void()> mask)
		{
			m_rt.clear(ColorF(0.0, 0.0));
			{
				static BlendState blend{
					true,
					Blend::Zero,
					Blend::Zero,
					BlendOp::Add,
					Blend::One,
					Blend::One,
				};
				ScopedRenderStates2D state(blend);
				ScopedRenderTarget2D target(m_rt);
				mask();
			}
			Graphics2D::SetPSTexture(1, m_rt);

			m_cb->isEqual = func == MaskFunc::Equal ? 1 : 0;
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, m_cb);

			{
				static BlendState blend{
					true,
					Blend::One,
					Blend::SrcAlpha
				};
				ScopedRenderStates2D state(blend);
				ScopedCustomShader2D shader(m_maskPs);

				Transformer2D transLocal(Mat3x2::Identity(), Transformer2D::Target::SetLocal);
				Transformer2D transCamera(Mat3x2::Identity(), Transformer2D::Target::SetCamera);

				m_rt2.draw();
			}
			Graphics2D::Flush();
		}

		const RenderTexture& getDrawerTarget()
		{
			return m_rt2;
		}
	};
	MaskShader::MaskShader(const Size& size) :
		MaskShader(size.x, size.y)
	{}
	MaskShader::MaskShader(uint32 width, uint32 height) :
		m_pImpl(std::make_shared<Impl>(width, height))
	{}
	MaskShader::ScopedMask MaskShader::equal(const std::function<void()>& mask) const
	{
		return ScopedMask(this->m_pImpl, MaskFunc::Equal, mask);
	}
	MaskShader::ScopedMask MaskShader::notEqual(const std::function<void()>& mask) const
	{
		return ScopedMask(this->m_pImpl, MaskFunc::NotEqual, mask);
	}

	MaskShader::ScopedMask::ScopedMask(
		const std::shared_ptr<Impl>& parentImpl,
		MaskFunc func,
		const std::function<void()>& mask
	) :
		m_parentImpl(parentImpl),
		m_func(func),
		m_mask(mask),
		m_oldBlend(Graphics2D::GetBlendState()),
		m_oldTarget(Graphics2D::GetRenderTarget()),
		m_oldViewport(Graphics2D::GetViewport())
	{
		static BlendState blend{ true, Blend::SrcAlpha, Blend::InvSrcAlpha, BlendOp::Add, Blend::Zero, Blend::InvSrcAlpha };
		Graphics2D::Internal::SetBlendState(blend);
		const auto& rt = m_parentImpl->getDrawerTarget();
		rt.clear(s3d::Palette::Black);
		Graphics2D::Internal::SetRenderTarget(rt);
		Graphics2D::Internal::SetViewport(Rect(rt.size()));
	}
	MaskShader::ScopedMask::~ScopedMask()
	{
		Graphics2D::Internal::SetBlendState(m_oldBlend);
		Graphics2D::Internal::SetRenderTarget(m_oldTarget);
		Graphics2D::Internal::SetViewport(m_oldViewport);

		m_parentImpl->draw(m_func, m_mask);
	}
}
