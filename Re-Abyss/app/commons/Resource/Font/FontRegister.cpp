#include <abyss/commons/Resource/Font/FontRegister.hpp>

namespace abyss::Resource
{
    void FontRegister::Load()
    {
        // フォントはデバッグモードでもリソースに入れてます

        // タイトル
        FontAsset::Register(U"pm12r-15", 15, U"/resources/fonts/PixelMplus12-Regular.ttf");
        FontAsset::Register(U"pm12r-20", 20, U"/resources/fonts/PixelMplus12-Regular.ttf");
        FontAsset::Register(U"pm12r-25", 25, U"/resources/fonts/PixelMplus12-Regular.ttf");

        FontAsset::Register(U"pm12b-12", 12, U"/resources/fonts/PixelMplus12-Bold.ttf");
        FontAsset::Register(U"pm12b-18", 18, U"/resources/fonts/PixelMplus12-Bold.ttf");
        FontAsset::Register(U"pm12b-20", 20, U"/resources/fonts/PixelMplus12-Bold.ttf");

        FontAsset::Register(U"r-12", 12, Typeface::Regular);
        FontAsset::Register(U"r-16", 16, Typeface::Regular);
    }
}
