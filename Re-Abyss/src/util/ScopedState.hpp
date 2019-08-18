#pragma once

#include <Siv3D/Transformer2D.hpp>
#include <Siv3D/Uncopyable.hpp>

namespace abyss
{
	//
	struct Transformer2D : s3d::Transformer2D
	{

		Transformer2D(const s3d::Mat3x2& mat, bool transformMouse = false)
			: s3d::Transformer2D(
				s3d::Graphics2D::GetTransform().inverse()* mat* s3d::Graphics2D::GetTransform(),
				transformMouse)
		{}

	};

	class ScopedRenderStates2D : s3d::Uncopyable
	{
	private:
		s3d::Optional<s3d::BlendState> m_oldBlendState;
		s3d::Optional<s3d::RasterizerState> m_oldRasterizerState;
		s3d::Optional<s3d::SamplerState> m_oldSamplerState;

		void clear();
	public:
		ScopedRenderStates2D() = default;
		ScopedRenderStates2D(ScopedRenderStates2D&& other);
		~ScopedRenderStates2D();

		ScopedRenderStates2D(const s3d::BlendState& blendState);
		ScopedRenderStates2D(const s3d::SamplerState& samplerState);
	};

	class ScopedStencilMask : s3d::Uncopyable
	{
	private:
		s3d::StencilState m_oldStencilState;
		s3d::uint8 m_oldStencilValue;
		std::function<void()> m_mask;
	public:
		ScopedStencilMask(std::function<void()> base, s3d::StencilFunc stencilFunc, s3d::uint8 stencilValue = 1);
		~ScopedStencilMask();
	};
}