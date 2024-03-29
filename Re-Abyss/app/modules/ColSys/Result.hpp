#pragma once
#include <memory>
#include <typeindex>
#include <abyss/modules/ColSys/base/IExtension.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::ColSys
{
	/// <summary>
	/// ヒットデータ
	/// </summary>
	struct HitData
	{
		s3d::uint64 id;
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

		template<class Type>
		bool isHitBy() const
		{
			return isHitBy(typeid(Type));
		}
		bool isHitBy(std::type_index type) const;

		template<class Type>
		bool anyThen(const std::function<bool(const typename Type::Data&)>& callback) const
		{
			for (const auto& hit : m_results) {
				if (auto it = hit.extData.find(typeid(Type)); it != hit.extData.end()) {
					if (callback(it->second.get<typename Type::Data>())) {
						return true;
					}
				}
			}
			return false;
		}
		template<class Type>
		bool anyThen(const std::function<bool(s3d::uint64, const typename Type::Data&)>& callback) const
		{
			for (const auto& hit : m_results) {
				if (auto it = hit.extData.find(typeid(Type)); it != hit.extData.end()) {
					if (callback(hit.id, it->second.get<typename Type::Data>())) {
						return true;
					}
				}
			}
			return false;
		}
		template<class Type>
		bool eachThen(const std::function<bool(const typename Type::Data&)>& callback) const
		{
			bool result = false;
			for (const auto& hit : m_results) {
				if (auto it = hit.extData.find(typeid(Type)); it != hit.extData.end()) {
					result |= callback(it->second.get<typename Type::Data>());
				}
			}
			return false;
		}
	private:
		Result() = default;

		void add(const HitData & hitData);

		void onReflesh();
	private:
		s3d::Array<HitData> m_results;
	};
}