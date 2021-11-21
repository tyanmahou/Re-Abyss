#pragma once
#include <abyss/modules/Collision/base/INode.hpp>
#include <abyss/modules/Collision/Result.hpp>

namespace abyss::Collision
{
	/// <summary>
	/// 衝突ブランチ
	/// </summary>
	class Branch
	{
	public:
		void onPreCollision();
		void onCollision(const Branch& other);
		bool isCollision(const Branch& other) const;
	private:
		Result m_result;
		s3d::Array<std::unique_ptr<INode>> m_nodes;
	};
}