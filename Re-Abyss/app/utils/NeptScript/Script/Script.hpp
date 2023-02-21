#pragma once
#include <memory>

namespace abyss::Nept
{
    class Script
    {
        class Impl;
    public:
        Script() = default;
        Script(const s3d::FilePath& path);
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}
