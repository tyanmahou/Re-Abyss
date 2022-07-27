#pragma once
#include <abyss/commons/Fwd.hpp>
#include <memory>

namespace abyss::Sfx
{
    class Moisture
    {
        class Impl;
    public:
        Moisture();

        void apply(const s3d::Texture& tex) const;

    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}
