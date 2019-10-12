#pragma once

#include <Siv3D/Effect.hpp>


namespace abyss
{
	class WorldModel;

	class WorldView
	{
		WorldModel* m_pModel;

		s3d::Effect m_effect;
	public:
		inline void setWorldModel(WorldModel* const pModel)
		{
			this->m_pModel = pModel;
		}

		void draw()const;

		s3d::Effect& getEffect();
	};
}