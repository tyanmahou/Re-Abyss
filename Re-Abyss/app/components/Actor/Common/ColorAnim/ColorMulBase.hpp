#pragma once
#include <abyss/modules/GameObject/ComponentTree.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorMul.hpp>

namespace abyss::Actor::ColorAnim
{
	class ColorMulBase : public IColorMul
	{
	public:
		void setIndexMaskMul(size_t mask)
		{
			m_indexMaskMul = mask;
		}
	public:
		size_t indexMaskMul() const override
		{
			return m_indexMaskMul;
		}
	protected:
		size_t m_indexMaskMul{ ~0u };
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::ColorAnim::ColorMulBase>
	{
		using Base = MultiComponents<
			Actor::ColorAnim::IColorMul
		>;
	};
}