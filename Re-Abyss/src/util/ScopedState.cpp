#include "ScopedState.hpp"
#include <Siv3D/Graphics2D.hpp>

using namespace s3d;

namespace abyss
{
	void ScopedRenderStates2D::clear()
	{
		m_oldBlendState.reset();
		m_oldRasterizerState.reset();
		m_oldSamplerState.reset();
	}
	ScopedRenderStates2D::ScopedRenderStates2D(ScopedRenderStates2D&& other)
	{
		m_oldBlendState = other.m_oldBlendState;
		m_oldRasterizerState = other.m_oldRasterizerState;
		m_oldSamplerState = other.m_oldSamplerState;
		other.clear();
	}
	ScopedRenderStates2D::~ScopedRenderStates2D()
	{
		m_oldBlendState.then(s3d::Graphics2D::SetBlendState);
		m_oldRasterizerState.then(s3d::Graphics2D::SetRasterizerState);
		if (m_oldSamplerState) {
			s3d::Graphics2D::SetSamplerState(*m_oldSamplerState);
		}
	}
	ScopedRenderStates2D::ScopedRenderStates2D(const s3d::BlendState& blendState):
		m_oldBlendState(s3d::Graphics2D::GetBlendState())
	{
		s3d::Graphics2D::SetBlendState(blendState);
	}
	ScopedRenderStates2D::ScopedRenderStates2D(const s3d::SamplerState& samplerState):
		m_oldSamplerState(s3d::Graphics2D::GetSamplerState())
	{
		s3d::Graphics2D::SetSamplerState(samplerState);
	}

	ScopedStencilMask::ScopedStencilMask(std::function<void()> base, s3d::StencilFunc stencilFunc, s3d::uint8 stencilValue):
		m_oldStencilState(Graphics2D::GetStencilState()),
		m_oldStencilValue(Graphics2D::GetStencilValue())
	{
		Graphics2D::SetStencilState(StencilState::Replace);
		Graphics2D::SetStencilValue(stencilValue);

		base();

		Graphics2D::SetStencilState(StencilState::Test(stencilFunc));
	}
	ScopedStencilMask::~ScopedStencilMask()
	{
		Graphics2D::SetStencilState(m_oldStencilState);
		Graphics2D::SetStencilValue(m_oldStencilValue);
	}
}