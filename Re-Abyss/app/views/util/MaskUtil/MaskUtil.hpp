#pragma once
#include <functional>
namespace abyss
{
    enum class MaskFunc
    {
        Equal,
        NotEqual,
    };

    /// <summary>
    /// マスク処理ユーティリティ
    /// </summary>
    class MaskUtil
    {
    public:
        static void Draw(std::function<void()> mask, std::function<void()> drawer, MaskFunc func);
    };
}