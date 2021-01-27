#include "Loading.hpp"
#include <abyss/views/Cycle/Common/Loading/LoadingView.hpp>

namespace abyss::Cycle
{
    Loading::Loading():
        m_view(std::make_unique<LoadingView>())
    {}
}
