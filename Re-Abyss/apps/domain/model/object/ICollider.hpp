#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Shape.hpp>

namespace abyss
{
	class ICollider
	{
	protected:
		s3d::String tag;
		s3d::String layer;
	public:

		virtual s3d::Shape getCollider() const = 0;

		virtual void onCollisionEnter(ICollider*);
		virtual void onCollisionStay(ICollider*);
		virtual void onCollisionExit(ICollider*);

		const s3d::String& getTag() const;
		const s3d::String& getLayer() const;
	};
}