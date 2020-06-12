#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class AudioGroup
    {
    public:
        AudioGroup() = default;
        AudioGroup(const s3d::FilePath& path);
        s3d::Audio operator()(const s3d::String& key) const;

        explicit operator bool()const;
    private:
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    };
}