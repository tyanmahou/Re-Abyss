#pragma once

#if ABYSS_DEBUG
#include <memory>
#include <Siv3D/String.hpp>

namespace abyss::Debug
{
    /// <summary>
    /// デバッグメニュー
    /// </summary>
    class Menu
    {
        class Impl;
    public:
        Menu();
        ~Menu();

        void update();
        void draw() const;

        bool isDebug(const s3d::String& label) const;

        void open();
        void close();

        bool isOpend() const;
    private:
        class Impl;
    public:
        std::unique_ptr<Impl> m_pImpl;
    };
}

#endif
