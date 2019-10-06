#pragma once
#include "SceneBase.hpp"

namespace abyss
{
	class MainScene : public ISceneBase
	{
		class Controller;
		std::unique_ptr<Controller> m_pImpl;
	public:
		MainScene(const InitData& init);
		void update()override;
		void draw() const override;
	};
}