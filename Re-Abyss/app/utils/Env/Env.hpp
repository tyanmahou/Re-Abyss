#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss
{
    /// <summary>
    /// 環境変数
    /// </summary>
    class Env
    {
    public:
        /// <summary>
        /// 環境変数設定
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value"></param>
        /// <param name="overwrite"></param>
        static bool Set(const s3d::String& key, const s3d::String& value, bool overwrite = true);

        /// <summary>
        /// 環境変数取得
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        static s3d::String Get(const s3d::String& key);

        static s3d::Optional<s3d::String> GetOpt(const s3d::String& key);

        /// <summary>
        /// 環境変数ファイルの読み込み
        /// </summary>
        static bool Load(const s3d::String& path = U".env", bool overwrite = true);
    };
}
