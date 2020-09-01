#pragma once
#include "../base/ISceneBase.hpp"

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
		void update()override;
		void draw() const override;

		void finally() override;
	};
}