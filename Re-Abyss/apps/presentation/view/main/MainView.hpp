#pragma once
#include <S3DTiled.hpp>
#include <Siv3D/Effect.hpp>
#include "../IView.hpp"
#include "WorldView.hpp"
#include "object/WorldObjectViewFactory.hpp"
namespace abyss
{
	class IMainView : public IView
	{
	public:
		virtual void addWorldObjectView(std::unique_ptr<IWorldObjectView>&& view, s3d::int32 layer) = 0;
		virtual const IWorldObjectViewFactory* getFactory()const = 0;
	};

	class MainView : public IMainView
	{
	private:
		WorldView m_woldView;
		WorldObjectViewFactory m_worldObjViewFactory;

	public:
		const IWorldObjectViewFactory* getFactory()const override;
		void addWorldObjectView(std::unique_ptr<IWorldObjectView>&& view, s3d::int32 layer) override;
		void update() override;
		void draw()const;
	};
}