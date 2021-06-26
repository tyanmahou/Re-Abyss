#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss
{
	enum class WindowSizeKind
	{
		ThreeSecond,
		FiveFourth,
		SixFifth,
		Default,
		FourFifth,
		ThreeFourth,
		Half,
		FullScrren,

		KIND_MAX
	};

	/// <summary>
	/// ウィンドウ制御
	/// </summary>
    class WindowCtrl
    {
	public:
		WindowCtrl(const s3d::String& appName, s3d::Size windowSize, bool useScalable = false);

		/// <summary>
		/// ウィンドウサイズを変更
		/// </summary>
		/// <param name="kind"></param>
		void changeWindowSize(WindowSizeKind kind);
		void changeWindowSizeNext();
	private:
		s3d::Size m_baseSceneSize;
		WindowSizeKind m_windowSizeKind;
    };
}