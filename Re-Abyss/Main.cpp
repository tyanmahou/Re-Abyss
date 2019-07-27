
//
// Siv3D August 2016 v2 for Visual Studio 2019
// 
// Requirements
// - Visual Studio 2015 (v140) toolset
// - Windows 10 SDK (10.0.17763.0)
//

# include <Siv3D.hpp>

void Main()
{
	const Font font(30);

	while (System::Update())
	{
		font(L"ようこそ、Siv3D の世界へ！").draw();

		Circle(Mouse::Pos(), 50).draw({ 255, 0, 0, 127 });
	}
}
