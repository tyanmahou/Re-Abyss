#include <abyss/types/Temporary/TempKey.hpp>
#include <Siv3D/FormatLiteral.hpp>

using namespace s3d::Literals::FormatLiterals;

namespace abyss
{
    TempKey TempKey::ItemGet(s3d::uint32 id)
    {
        return TempKey(U"item-get-{}"_fmt(id));
    }
}
