#pragma once
#include <abyss/modules/GameObject/ComponentTree.hpp>
#include <abyss/components/Actor/Common/ColorAnim/IColorAdd.hpp>

namespace abyss::Actor::ColorAnim
{
	class ColorAddBase : public IColorAdd
	{
	public:
		void setIndexMaskAdd(size_t mask)
		{
			m_indexMaskAdd = mask;
		}
	public:
		size_t indexMaskAdd() const override
		{
			return m_indexMaskAdd;
		}
	protected:
		size_t m_indexMaskAdd{ ~0u };
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::ColorAnim::ColorAddBase>
	{
		using Base = MultiComponents<
			Actor::ColorAnim::IColorAdd
		>;
	};
}