#pragma once
#include <memory>
#include <source_location>
#include <Siv3D/String.hpp>

namespace abyss::DebugLog
{
    /// <summary>
    /// ログ種類
    /// </summary>
    enum class LogKind
    {
        Info,
        Warn,
        Error,
        Load,
    };

    /// <summary>
    /// デバッグログ
    /// </summary>
    class DebugLog
    {
        class Impl;
    public:
        DebugLog();

        void print(LogKind kind, const s3d::String& log, const std::source_location& location = std::source_location::current());
        void printUpdate(LogKind kind, const s3d::String& log, const std::source_location& location = std::source_location::current());
        void clear();

        void update();
        void draw() const;
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}
