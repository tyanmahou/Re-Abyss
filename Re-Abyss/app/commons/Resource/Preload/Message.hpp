#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Resource::Preload
{
    /// <summary>
    /// メッセージをロード
    /// </summary>
    void LoadMessage(s3d::StringView lang = U"ja", const Assets* resource = Assets::Norelease());
}