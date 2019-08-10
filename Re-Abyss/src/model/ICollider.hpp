#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Shape.hpp>

namespace abyss
{
	class ICollider
	{
	protected:
		s3d::String tag;
		virtual s3d::Shape getCollider() const = 0;
	public:
		virtual void onCollisionEnter(ICollider*){}
		virtual void onCollisionStay(ICollider*){}
		virtual void onCollisionExit(ICollider*) {}
	};
}