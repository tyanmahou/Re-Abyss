#pragma once
#include "../base/ISceneBase.hpp"

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
		void update()override;
		void draw() const override;
	};
}