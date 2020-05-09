#pragma once
#include <Siv3D/String.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/types/CShape.hpp>

namespace abyss
{
	class ICollider
	{
	protected:
		s3d::String tag;
		s3d::String layer;
	public:

		virtual CShape getCollider() const { return s3d::none; }

		virtual void onCollisionEnter(ICollider*);
		virtual void onCollisionStay(ICollider*);
		virtual void onCollisionExit(ICollider*);

		const s3d::String& getTag() const;
		const s3d::String& getLayer() const;

		virtual bool accept(const ActVisitor&) = 0;
	};
}