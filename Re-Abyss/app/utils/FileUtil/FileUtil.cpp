﻿#include <abyss/utils/FileUtil/FileUtil.hpp>

#include <stack>
#include <Siv3D.hpp>
#include <abyss/debugs/Log/Log.hpp>

namespace
{
	bool IsResourcePath(const s3d::FilePath& path)
	{
		return path.starts_with(U'/');
	}
}

namespace abyss::FileUtil
{
	s3d::String BaseName(s3d::FilePathView path)
	{
        if (path.ends_with(U'/')) {
            path.remove_suffix(1);
        }
        return s3d::FileSystem::BaseName(path);
	}
    s3d::String FileName(s3d::FilePathView path)
    {
        if (path.ends_with(U'/')) {
            path.remove_suffix(1);
        }
        return s3d::FileSystem::FileName(path);
    }
	s3d::FilePath FixRelativePath(const s3d::FilePath& path)
    {
		std::stack<String> dirNameStack;
		String dirName = U"";
		for (auto&& c : path) {
			if (c == U'/') {
				if (dirName == U".") {

				} else if (dirName == U"..") {
                    if (dirNameStack.empty()) {
                        dirNameStack.push(dirName);
                    } else {
                        dirNameStack.pop();
                    }
				} else {
					dirNameStack.push(dirName);
				}
				dirName.clear();
			} else {
				dirName += c;
			}
		}
		String result = dirName;
		while (!dirNameStack.empty()) {
			result = dirNameStack.top() + U"/" + result;
			dirNameStack.pop();
		}
		return result;
    }
	s3d::FilePath FixResource(const s3d::FilePath& path, bool useResource)
	{
		if (useResource) {
			s3d::FilePath resourcePath;
			if (::IsResourcePath(path)) {
				resourcePath = path;
			} else {
				resourcePath = Resource(path);
			}
#if ABYSS_DEBUG
			if (::IsResourcePath(resourcePath)) {
				return resourcePath;
			}
			Debug::Log::Error(U"Not Found Resoure: {}"_fmt(path));
#else
			return resourcePath;
#endif
		}
		return path;
	}
	s3d::FilePath ParentPath(const s3d::FilePath& path)
	{
		if (::IsResourcePath(path)) {
			return U"/" + FileSystem::RelativePath(FileSystem::ParentPath(path.substr(1)));
		} else {
			return FileSystem::RelativePath(FileSystem::ParentPath(path));
		}
	}
	s3d::String Extension(const s3d::FilePath& path)
	{
		auto basePath = ::IsResourcePath(path) ? path.substr(1) : path;
		return FileSystem::Extension(basePath);
	}
	s3d::String FixPath(const s3d::FilePath& path, bool useResource)
	{
		return FixResource(FixRelativePath(path), useResource);
	}
}
