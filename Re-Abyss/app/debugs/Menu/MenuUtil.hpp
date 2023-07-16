#pragma once
#include <abyss/debugs/Menu/DebugFlag.hpp>

#if ABYSS_DEBUG
namespace abyss::Debug
{
    /// <summary>
    /// デバッグメニューユーティリティ
    /// </summary>
    class MenuUtil
    {
    public:
        /// <summary>
        /// 指定のデバッグフラグが立っているか
        /// </summary>
        /// <param name="label"></param>
        /// <returns></returns>
        static bool IsDebug(const s3d::String& label);

        /// <summary>
        /// メニュー閉じる
        /// </summary>
        static void RequestClose();

        static bool Load();
        static bool Save();
    };
}
#endif
