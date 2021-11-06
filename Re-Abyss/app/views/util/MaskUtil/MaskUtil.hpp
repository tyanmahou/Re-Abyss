#pragma once
#include <abyss/views/Shader/Mask/MaskShader.hpp>

namespace abyss
{
    /// <summary>
    /// マスク処理ユーティリティ
    /// </summary>
    class MaskUtil
    {
    public:
        static MaskShader& Instance();
    };
}