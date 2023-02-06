#include <abyss/scenes/Loading/Common/Loading.hpp>
#include <abyss/views/Loading/Common/LoadingView.hpp>

namespace abyss::Loading::Common
{
    Loading::Loading():
        m_view(std::make_unique<LoadingView>())
    {
    }
    Loading::~Loading()
    {
    }
    bool Loading::update(double progress)
    {
        return progress < 1.0;
    }
    void Loading::draw() const
    {
        m_view->draw();
    }
}

