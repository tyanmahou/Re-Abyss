#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>
#include <any>
#include <memory>
#include <typeinfo>

namespace abyss::Collision
{
	/// <summary>
	/// ヒットデータ
	/// </summary>
	struct HitData
	{
		s3d::HashTable<std::type_index, std::any> extData;
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