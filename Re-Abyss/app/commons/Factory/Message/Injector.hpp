#pragma once
#include <abyss/commons/Resource/Msg/Language.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Emaject.hpp>

namespace abyss::Factory::Message
{
    emaject::Injector Injector(const Resource::Msg::Language& lang, Resource::Assets* pAssets);
}
