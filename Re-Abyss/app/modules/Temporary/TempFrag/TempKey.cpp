#include <abyss/modules/Temporary/TempFrag/TempKey.hpp>
#include <Siv3D/FormatLiteral.hpp>

using namespace s3d::Literals::FormatLiterals;

namespace abyss
{
    TempKey TempKey::ItemGet(const s3d::String& mapName, s3d::uint32 id)
    {
        return TempKey(U"[{}]item-get-{}"_fmt(mapName, id));
    }
}
