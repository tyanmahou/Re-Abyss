#include <abyss/views/Actor/Ooparts/base/OopartsViewUtil.hpp>
#include <abyss/views/Actor/Ooparts/Xto/XtoVM.hpp>
#include <abyss/views/Actor/Ooparts/Nyan/NyanVM.hpp>

namespace abyss::Actor::Ooparts::OopartsViewUtil
{
    std::shared_ptr<BaseVM> CreateViewFromType(OopartsType type)
    {
        switch (type) {
        case abyss::OopartsType::Invalid:
            break;
        case abyss::OopartsType::Xto:
            return std::make_shared<Xto::XtoVM>();
        case abyss::OopartsType::Nyan:
            return std::make_shared<Nyan::NyanVM>();
        default:
            break;
        }
        return nullptr;
    }
}
