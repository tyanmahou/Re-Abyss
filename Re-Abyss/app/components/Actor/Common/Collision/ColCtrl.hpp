#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/modules/Collision/Branch.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Collision
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
			for (const auto& b : m_branch) {
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
			for (const auto& b : m_branch) {
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
		s3d::Array<Ref<abyss::Collision::Branch>> m_branch;
	};
}