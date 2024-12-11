#pragma once
#include <Siv3D/String.hpp>

namespace abyss::FileUtil
{
   s3d::String BaseName(s3d::FilePathView path);
   s3d::String FileName(s3d::FilePathView path);

    /// <summary>
    /// 相対パスの ../ ./を排除する
    /// ex Hoge/../Piyp/ => Hoge/
    /// </summary>
    s3d::FilePath FixRelativePath(const s3d::FilePath& path);

    /// <summary>
    /// Resource パスに修正する
    /// </summary>
    s3d::FilePath FixResource(const s3d::FilePath& path, bool useResource = true);

    /// <summary>
    /// 親ディレクトリィパスを返す
    /// </summary>
    s3d::FilePath ParentPath(const s3d::FilePath& path);

    //
    s3d::String Extension(const s3d::FilePath& path);

    /// <summary>
    /// FixRelativePath -> FixResource
    /// </summary>
#if ABYSS_NO_BUILD_RESOURCE
    s3d::String FixPath(const s3d::FilePath& path, bool useResource = false);
#else
    s3d::String FixPath(const s3d::FilePath& path, bool useResource = true);
#endif
}
