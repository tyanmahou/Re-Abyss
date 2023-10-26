#include <abyss/commons/Resource/Font/FontRegister.hpp>
#include <abyss/commons/Resource/Font/FontAssetName.hpp>

namespace abyss::Resource
{
    void FontRegister::Load()
    {
        // フォントはデバッグモードでもリソースに入れてます

        // タイトル
        FontAsset::Register(U"pm12r-15", 15, FontAssetName::PixelMplus12);
        FontAsset::Register(U"pm12r-20", 20, FontAssetName::PixelMplus12);
        FontAsset::Register(U"pm12r-25", 25, FontAssetName::PixelMplus12);

        FontAsset::Register(U"pm12b-12", 12, FontAssetName::PixelMplus12B);
        FontAsset::Register(U"pm12b-18", 18, FontAssetName::PixelMplus12B);
        FontAsset::Register(U"pm12b-20", 20, FontAssetName::PixelMplus12B);

        FontAsset::Register(U"r-12", 12, Typeface::Regular);
        FontAsset::Register(U"r-16", 16, Typeface::Regular);
    }
}
