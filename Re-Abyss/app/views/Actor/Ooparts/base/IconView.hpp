#pragma once
#include <Siv3D/HashTable.hpp>
#include <Siv3D/TextureRegion.hpp>
#include <abyss/types/OopartsType.hpp>

namespace abyss::Actor::Ooparts
{
    class IconView
    {
        s3d::HashTable<OopartsType, s3d::TextureRegion> m_icons;
    public:
        IconView();
        s3d::TextureRegion operator()(OopartsType type) const;

    };
}