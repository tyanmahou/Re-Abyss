#include "IconView.hpp"

#include <abyss/views/actors/Ooparts/Nyan/NyanVM.hpp>
#include <abyss/views/actors/Ooparts/Xto/XtoVM.hpp>

namespace abyss::Actor::Ooparts
{
    IconView::IconView():
        m_icons{
            {OopartsType::Invalid, s3d::TextureRegion()},
            {OopartsType::Xto, Xto::XtoVM().icon()},
            {OopartsType::Nyan, Nyan::NyanVM().icon()},
        }
    {}

    s3d::TextureRegion IconView::operator()(OopartsType type) const
    {
        return m_icons.at(type);
    }
}
