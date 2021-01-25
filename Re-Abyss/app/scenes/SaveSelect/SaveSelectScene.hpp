#pragma once
#include "../base/ISceneBase.hpp"

namespace abyss
{
	/// <summary>
	/// SaveSelect Scene
	/// </summary>
	class SaveSelectScene : public ISceneBase
	{
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	public:
		SaveSelectScene(const InitData& init);
		void onSceneUpdate() override;
		void onSceneDraw() const override;

		void finally() override;
	};
}