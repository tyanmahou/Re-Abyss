#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Slime
{
	class SlimeActor;

    class Senser : public IActor
    {
		Ref<PosModel> m_pos;
	public:
		Senser(SlimeActor* p);

		const s3d::Vec2& getPos() const;
    };
}