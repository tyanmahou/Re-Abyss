#pragma once
#include <memory>
#include <typeindex>
#include <abyss/modules/Collision/base/IExtension.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::Collision
{
	/// <summary>
	/// ヒットデータ
	/// </summary>
	struct HitData
	{
		s3d::HashTable<std::type_index, ExtData> extData;
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