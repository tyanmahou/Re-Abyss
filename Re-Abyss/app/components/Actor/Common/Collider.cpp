#include <abyss/components/Actor/Common/Collider.hpp>

namespace abyss::Actor
{
	using namespace Col;
	void Collider::setup(Executer executer)
	{
		for (auto&& c : m_colliders) {
			c->setup(executer);
		}
	}

	void Collider::onStart()
	{
		for (auto&& c : m_colliders) {
			c->onStart();
		}
	}

	Ref<ICollider> Collider::add(const std::shared_ptr<ICollider>& collider)
	{
		m_colliders << collider;
		return collider;
	}
	Ref<ICollider> Collider::add(const std::function<CShape()>& func)
	{
		class FuncHolder : public ICollider
		{
			std::function<CShape()> m_colFunc;
		public:

			FuncHolder(const std::function<CShape()>& func) :
				m_colFunc(func)
			{}
			CShape getCollider() const override
			{
				if (m_colFunc) {
					return m_colFunc();
				}
				return s3d::none;
			}
		};
		return this->add(std::make_shared<FuncHolder>(func));
	}
}