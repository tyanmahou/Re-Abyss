#include "FileUtil.hpp"
#include <stack>
#include <Siv3D.hpp>
#include <abyss/debugs/Log/Log.hpp>
namespace abyss::FileUtil
{
    s3d::FilePath FixRelativePath(const s3d::FilePath& path)
    {
		std::stack<String> dirNameStack;
		String dirName = U"";
		for (auto&& c : path) {
			if (c == U'/') {
				if (dirName == U".") {

				} else if (dirName == U"..") {
					dirNameStack.pop();
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
#if ABYSS_DEBUG
			auto resourcePath = Resource(path);
			if (FileSystem::IsResource(resourcePath)) {
				return resourcePath;
			}
			Debug::Log::PrintCache << U"Not Found Resoure: " << path;
#else
			return Resource(path);
#endif
		}
		return path;
	}
	s3d::FilePath ParentPath(const s3d::FilePath& path)
	{
		if (FileSystem::IsResource(path)) {
			return U"/" + FileSystem::RelativePath(FileSystem::ParentPath(path.substr(1)));
		} else {
			return FileSystem::RelativePath(FileSystem::ParentPath(path));
		}
	}
}
