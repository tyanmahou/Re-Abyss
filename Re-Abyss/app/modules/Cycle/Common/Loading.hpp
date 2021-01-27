#pragma once
#include <memory>

namespace abyss::Cycle
{
    class LoadingView;

    class Loading
    {
    public:
        Loading();
    private:
        std::unique_ptr<LoadingView> m_view;
    };
}