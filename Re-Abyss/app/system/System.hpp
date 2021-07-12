#pragma once
#include <Emaject.hpp>

namespace abyss::Sys
{
    class ICoreSystem;

    class System
    {
    public:
        System() = default;

        void update();

        void draw() const;
    private:
        [[INJECT(m_core)]]
        std::shared_ptr<ICoreSystem> m_core;
    };
}