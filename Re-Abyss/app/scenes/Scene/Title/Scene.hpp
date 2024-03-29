#pragma once
#include <abyss/scenes/Scene/ISceneBase.hpp>

namespace abyss::Scene::Title
{
	/// <summary>
	/// Title Scene
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
