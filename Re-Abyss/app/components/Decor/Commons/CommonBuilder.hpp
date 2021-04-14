#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/DecorEntity.hpp>

namespace abyss::decor
{
	struct BuildOption
	{
		friend struct CommonBuilder;
	public:
		BuildOption& setInitInfo(const DecorEntity& _entity)
		{
			this->entity = _entity;
			return *this;
		}
	private:
		DecorEntity entity;
	};

	struct CommonBuilder
	{
		static void Build(DecorObj* pObj, const BuildOption& opt = BuildOption{});
	};
}