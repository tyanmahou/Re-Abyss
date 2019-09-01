#include "ICollider.hpp"

namespace abyss
{
	void ICollider::onCollisionEnter(ICollider*)
	{
	}

	void ICollider::onCollisionStay(ICollider*)
	{
	}

	void ICollider::onCollisionExit(ICollider*)
	{
	}

	const s3d::String& ICollider::getTag() const
	{
		return tag;
	}

	const s3d::String& ICollider::getLayer() const
	{
		return layer;
	}

}