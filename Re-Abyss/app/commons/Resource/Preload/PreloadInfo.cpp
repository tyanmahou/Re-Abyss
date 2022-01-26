#include <abyss/commons/Resource/Preload/PreloadInfo.hpp>

namespace abyss::Resource::Preload
{
    PreloadInfo& PreloadInfo::unique()
    {
        for (auto&& memP : PrelaodInfoMemPtrs) {
            (this->*memP).sort_and_unique();
        }
        return *this;
    }
    PreloadInfo& PreloadInfo::operator+=(const PreloadInfo& other)
    {
        for (auto&& memP : PrelaodInfoMemPtrs) {
            (this->*memP).append(other.*memP);
        }
        return *this;
    }
    size_t PreloadInfo::size() const
    {
        size_t size = 0;
        for (auto&& memP : PrelaodInfoMemPtrs) {
            size += (this->*memP).size();
        }
        return size;
    }
}