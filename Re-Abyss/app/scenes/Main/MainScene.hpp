#pragma once
#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss
{
	/// <summary>
	/// Main Scene
	/// </summary>
	class MainScene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
		MainScene(const InitData& init);
		void onSceneUpdate() override;
		void onSceneDraw() const override;
	};
}