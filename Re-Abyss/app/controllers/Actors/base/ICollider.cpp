#include "ICollider.hpp"

namespace abyss
{
	void ICollider::onCollisionEnter([[maybe_unused]] ICollider* collider)
	{
	}

	void ICollider::onCollisionStay([[maybe_unused]] ICollider* collider)
	{
	}

	void ICollider::onCollisionExit([[maybe_unused]] ICollider* collider)
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