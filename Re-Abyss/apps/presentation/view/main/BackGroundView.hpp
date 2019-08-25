#pragma once
#include <data/entity/BackGroundEntity.hpp>
#include "../IView.hpp"

namespace abyss
{
	class BackGroundVM
	{
		BackGroundEntity m_data;
	public:
		BackGroundVM(const BackGroundEntity& data);

		void draw(const s3d::Vec2& pos)const;
	};

	class BackGroundView : public IView
	{
	private:
		s3d::Array<BackGroundVM> m_bgs;
		s3d::Vec2 m_pos;
	public:
		void addBackGround(const BackGroundVM& bg);
		void setPos(const s3d::Vec2& pos);
		void draw()const override;
	};
}