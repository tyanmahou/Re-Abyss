#pragma once
#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss
{
	/// <summary>
	/// StageResult Scene
	/// </summary>
	class StageResultScene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
        StageResultScene(const InitData& init);
		~StageResultScene();
		void onSceneUpdate()override;
		void onSceneDraw() const override;
	};
}
