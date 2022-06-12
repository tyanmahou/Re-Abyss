#pragma once
#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss::Scene::SaveSelect
{
	/// <summary>
	/// SaveSelect Scene
	/// </summary>
	class Scene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
		Scene(const InitData& init);
		~Scene();
		void onSceneUpdate() override;
		void onSceneDraw() const override;
	};
}
