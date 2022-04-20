#pragma once
#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss
{
	/// <summary>
	/// ClearResult Scene
	/// </summary>
	class ClearResultScene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
		ClearResultScene(const InitData& init);
		~ClearResultScene();
		void onSceneUpdate()override;
		void onSceneDraw() const override;
	};
}