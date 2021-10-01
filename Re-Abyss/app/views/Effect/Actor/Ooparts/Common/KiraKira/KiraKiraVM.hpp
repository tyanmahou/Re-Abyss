#pragma once
#include <abyss/components/Effect/Actor/Ooparts/Common/KiraKira/Type.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Effect::Actor::Ooparts::KiraKira
{
    class KiraKiraVM
    {
	public:

		KiraKiraVM(Type type = Type::Type1);

		KiraKiraVM& setPos(const s3d::Vec2& pos)
		{
			m_pos = pos;
			return *this;
		}
		KiraKiraVM& setTime(double time)
		{
			m_time = time;
			return *this;
		}
		void draw() const;

	private:
		s3d::Texture m_texture;
		Type m_type;

		s3d::Vec2 m_pos;
		double m_time = 0;
    };
}