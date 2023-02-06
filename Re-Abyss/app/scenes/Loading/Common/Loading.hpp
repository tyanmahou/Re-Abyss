#pragma once
#include <memory>
#include <abyss/scenes/Loading/ILoading.hpp>

namespace abyss::Loading::Common
{
    class LoadingView;

    class Loading final : public ILoading
    {
    public:
        Loading();
        ~Loading();

        bool update(double progress) override;
        void draw() const  override;
    private:
        std::unique_ptr<LoadingView> m_view;
    };
}
