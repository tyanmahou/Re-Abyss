#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/Col/Node.hpp>
#include <abyss/modules/ColSys/Branch.hpp>
#include <abyss/modules/ColSys/LayerGroup.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
{
	class ColCtrl : 
		public IComponent
	{
	public:
		ColCtrl(ActorObj* pActor);

		void setup(Executer executer);

		void onStart();
		void onEnd();

	public:
		ColCtrl& setActive(bool isActive);

		/// <summary>
		/// ブランチ追加
		/// </summary>
		/// <returns></returns>
		Ref<ColSys::Branch> addBranch();

		/// <summary>
		/// ブランチ取得
		/// </summary>
		/// <returns></returns>
		Ref<ColSys::Branch> branch(size_t index) const;

		/// <summary>
		/// 何かにヒットしたか
		/// </summary>
		/// <returns></returns>
		bool isHitAny() const;

		/// <summary>
		/// 特定の拡張データにヒットしたか
		/// </summary>
		template<class Type>
		bool isHitBy() const
		{
			return isHitBy(typeid(Type));
		}
		bool isHitBy(std::type_index type) const;

		/// <summary>
		/// 衝突したいずれかに対して処理を行う
		/// </summary>
		template<class Type>
		bool anyThen(const std::function<bool(const typename Type::Data&)>& callback) const
		{
			for (const auto& b : m_branchs) {
				if (!b) {
					continue;
				}
				if (b->result().anyThen<Type>(callback)) {
					return true;
				}
			}
			return false;
		}

		/// <summary>
		/// 衝突したすべてに対して処理を行う
		/// </summary>
		template<class Type>
		bool eachThen(const std::function<bool(const typename Type::Data&)>& callback) const
		{
			bool result = false;
			for (const auto& b : m_branchs) {
				if (!b) {
					continue;
				}
				result |= b->result().eachThen<Type>(callback);
			}
			return result;
		}
	private:
		ActorObj* m_pActor;
		s3d::uint64 m_id;
		s3d::Array<std::shared_ptr<ColSys::Branch>> m_branchs;
		bool m_isActive = true;
	};
}