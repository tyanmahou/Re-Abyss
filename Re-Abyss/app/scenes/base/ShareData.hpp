#pragma once
#include <memory>
#include <abyss/modules/Sound/BackGroundMusic.hpp>

namespace abyss
{
    /// <summary>
    /// 共有データ
    /// </summary>
	struct ShareData
	{
        /// <summary>
        /// サウンド関連
        /// </summary>
        struct SoundData
        {
            BackGroundMusic bgm;
        };
    public:
        SoundData sound;
	};
}