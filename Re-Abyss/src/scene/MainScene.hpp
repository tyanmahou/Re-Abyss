#pragma once
#include "SceneBase.hpp"

namespace abyss
{
	class MainScene : public AppScene::Scene
	{
		class Impl;
		std::shared_ptr<Impl> m_pImpl;
	public:
		MainScene();
		void init()override;
		void update()override;
		void draw() const override;
	};
}