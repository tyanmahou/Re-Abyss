#include "DIContainer.hpp"

namespace abyss
{
    DIContainer::DIContainer() :
        m_pImpl(std::make_shared<Impl>())
    {}
}