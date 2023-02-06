#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>

namespace abyss::Resource::Preload
{
    /// <summary>
    /// メッセージ
    /// </summary>
    /// <param name="lang"></param>
    /// <returns></returns>
    Preloader Message(s3d::StringView lang = U"ja");
}
