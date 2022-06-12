#pragma once
#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss
{
	/// <summary>
	/// Splash Scene
	/// </summary>
	class SplashScene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
		SplashScene(const InitData& init);
		~SplashScene();
		void onSceneUpdate()override;
		void onSceneDraw() const override;
	};
}