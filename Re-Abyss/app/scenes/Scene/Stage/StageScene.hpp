#pragma once
#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss
{
	/// <summary>
	/// Stage Scene
	/// </summary>
	class StageScene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
        StageScene(const InitData& init);
		~StageScene();

		void onSceneUpdate() override;
		void onSceneDraw() const override;
	};
}
