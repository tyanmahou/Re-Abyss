#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/DecorEntity.hpp>

namespace abyss::Decor
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
		BuildOption& setIsEnableBasicDraw(bool isEnable)
		{
			this->isEnableBasicDraw = isEnable;
			return *this;
		}
	private:
		DecorEntity entity;
		bool isEnableBasicDraw = true;
	};

	struct CommonBuilder
	{
		static void Build(DecorObj* pObj, const BuildOption& opt = BuildOption{});
	};
}