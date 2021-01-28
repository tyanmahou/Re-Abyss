#include "PreloadInfo.hpp"

namespace abyss::Resource::Preload
{
    PreloadInfo& PreloadInfo::unique()
    {
        for (auto&& memP : PrelaodInfoMemPtrs) {
            (this->*memP).unique();
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