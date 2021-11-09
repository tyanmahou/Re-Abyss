#pragma once
#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss
{
	/// <summary>
	/// Root Scene
	/// </summary>
	class RootScene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
		RootScene(const InitData& init);
		void onSceneUpdate()override;
		void onSceneDraw() const override;
	};
}