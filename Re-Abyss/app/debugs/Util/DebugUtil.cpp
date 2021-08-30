#if ABYSS_DEBUG
#include "DebugUtil.hpp"
#include <abyss/types/CShape.hpp>
#include <abyss/utils/Overloaded.hpp>

#include <Siv3D.hpp>
#include <Siv3D/Windows.hpp>

namespace abyss::Debug::DebugUtil
{
    void DrawShape(const CShape& shape, const s3d::ColorF& color)
    {
        std::visit(overloaded{
            [&color](const auto& c) {
                c.draw(color);
            },
            [&color](const Vec2& c) {
                Shape2D::Cross(5, 2, c).draw(color);
            },
            [&color](const Array<CShape>& c) {
                for (const auto& shape : c) {
                    DrawShape(shape, color);
                }
            },
            []([[maybe_unused]] const None_t&) {}
        }, shape);
    }
    bool FileEdit(const s3d::FilePath& path)
    {
        return reinterpret_cast<size_t>(::ShellExecuteW(nullptr, L"open", s3d::FileSystem::FullPath(path).toWstr().c_str(), nullptr, nullptr, SW_SHOWNORMAL)) > 32;
    }
}

#endif
