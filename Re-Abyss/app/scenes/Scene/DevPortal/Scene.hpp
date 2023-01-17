#pragma once
#include <abyss/scenes/Scene/ISceneBase.hpp>

#if ABYSS_DEVELOP
namespace abyss::Scene::DevPortal
{
	/// <summary>
	/// DevPortal Scene
	/// </summary>
	class Scene : public ISceneBase
	{
	public:
		Scene(const InitData& init);
		~Scene();
		void onSceneUpdate()override;
		void onSceneDraw() const override;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
	};
}
#endif
