#pragma once
#include <Siv3D/Array.hpp>
#include <memory>

namespace abyss::Collision
{
	/// <summary>
	/// ヒットデータ
	/// </summary>
	struct HitData
	{

	};

	/// <summary>
	/// コリジョンリザルト
	/// </summary>
	class Result
	{
		friend class Branch;
	public:
		bool isHitAny() const;

	private:
		Result() = default;

		void add(const HitData & hitData);

		void onReflesh();
	private:
		s3d::Array<HitData> m_results;
	};
}