#include "AbyssDream.hpp"
#include<Siv3D/String.hpp>
#include<Siv3D/Vector2D.hpp>

#include"../vendor/S3DTiled/include/S3DTiled.hpp"
#include"../view/effects/Bubble.hpp"
namespace abyss
{
	using namespace s3dTiled;

	const TiledMap& Map()
	{
		static TiledReader t(L"work/stage0/stage0.tmx");
		return t.getTiledMap();
	}
	bool AbyssDream::update() const
	{
		static s3d::Effect e;
		static Texture tex(L"resources/Images/bgs/stage0-4.png");
		static Texture tex2(L"resources/Images/bgs/stage0-3.png");
		static Texture tex3(L"resources/Images/bgs/stage0-2.png");
		static Texture tex4(L"resources/Images/bgs/stage0-1.png");
		tex.draw();
		int32 f = System::FrameCount();
		float t = static_cast<float>(f);
		if (f % 80 == 0) {
			e.add<BubbleEffect>();
			e.setSpeed(0.1);
		}
		tex.draw();
		tex2.uv(t/960/3, 0, 1, 1).draw();
		tex3.uv(t/960/2, 0, 1, 1).draw();
		tex4.uv(0, 0, 1, 1).draw();

		ClearPrint();
		if (!Map().drawLayer(L"map", { 0,0,960,520 }))
		{
			Println(L"failed map");
		}
		Map().drawLayer(L"front",{ 0,0,960,520 });
		Graphics2D::SetBlendState(BlendState::Additive);
		e.update();
		Graphics2D::SetBlendState(BlendState::Default);
		return true;
	}

	AbyssDream::AbyssDream():
		Application(L"Abyss Dream", {960, 540})
	{
		Map();
	}

	AbyssDream::~AbyssDream()
	{
	}
}
