#pragma once
#include <abyss/scenes/Scene/ISceneBase.hpp>

namespace abyss::Scene::Boot
{
	/// <summary>
	/// Boot Scene
	/// </summary>
	class Scene : public ISceneBase
	{
		class Impl;
	public:
		Scene(const InitData& init);
		~Scene();
		void onSceneUpdate()override;
		void onSceneDraw() const override;
    private:
        std::unique_ptr<Impl> m_pImpl;
	};
}
