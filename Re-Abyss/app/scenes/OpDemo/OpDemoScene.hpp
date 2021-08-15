#pragma once
#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss
{
	/// <summary>
	/// OpDemo Scene
	/// </summary>
	class OpDemoScene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
		OpDemoScene(const InitData& init);
		void onSceneUpdate()override;
		void onSceneDraw() const override;
	};
}