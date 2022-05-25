#include <abyss/debugs/Menu/MenuBuilder.hpp>
#if ABYSS_DEBUG
#include <abyss/utils/FPS/FrameRateHz.hpp>
#include <abyss/debugs/Log/Log.hpp>
#include <Siv3D.hpp>
namespace abyss::Debug
{
	void MenuBuilder::ExecClearLog()
	{
		LogUpdater::Clear();
	}
	void MenuBuilder::ExecSoundMute(bool value)
	{
		// マスターボリューム設定
		if (value) {
			GlobalAudio::SetVolume(0.0);
		} else {
			GlobalAudio::SetVolume(1.0);
		}
	}
	void MenuBuilder::ExecFPS(s3d::StringView value)
	{
		FrameRateHz::Set(ParseOpt<double>(value));
	}
}
#endif