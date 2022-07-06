#pragma once
#include <abyss/scenes/Scene/ISceneBase.hpp>

#if ABYSS_DEVELOP
namespace abyss::Scene::Experiment
{
	/// <summary>
	/// Experiment Scene
	/// </summary>
	class Scene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
		Scene(const InitData& init);
		~Scene();
		void onSceneUpdate()override;
		void onSceneDraw() const override;
	};
}
#endif
