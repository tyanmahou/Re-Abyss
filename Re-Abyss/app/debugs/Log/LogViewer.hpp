#pragma once
#include <abyss/utils/DebugLog/IViewer.hpp>
#include <Siv3D/Texture.hpp>

namespace abyss::Debug
{
    class LogViewer : DebugLog::IViewer
    {
        struct KindCustom
        {
            s3d::Texture icon;
            s3d::ColorF color;
        };
    public:
        LogViewer();

        void draw(const s3d::Array<DebugLog::LogInfo>& logs) const override;
    private:
        s3d::Font m_font;
        s3d::Font m_fontDetail;
        s3d::HashTable<DebugLog::LogKind, KindCustom> m_kindCustom;
    };
}
