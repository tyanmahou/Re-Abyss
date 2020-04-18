#pragma once

#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Stage/base/IStageView.hpp>
#include <abyss/views/Stage/Bubble/BubbleGenerator.hpp>

namespace abyss
{
	class StageView : public IStageView
	{
		Decor* m_decor;
		BackGround* m_bg;
		BubbleGenerator m_bubbles;
	public:
		StageView() = default;
		StageView& setDecor(Decor* decor);
		StageView& setBg(BackGround* bg);

		void drawBack(const CameraView& camera) const override;
		void drawMiddle(const CameraView& camera) const override;
		void drawFront(const CameraView& camera) const override;
	};
}