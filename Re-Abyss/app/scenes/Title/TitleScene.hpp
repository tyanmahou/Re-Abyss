#pragma once
#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss
{
	/// <summary>
	/// Title Scene
	/// </summary>
	class TitleScene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
		TitleScene(const InitData& init);
		void onSceneUpdate() override;
		void onSceneDraw() const override;
	};
}