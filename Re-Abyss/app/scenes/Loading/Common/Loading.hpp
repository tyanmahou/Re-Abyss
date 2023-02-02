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
        double m_progress = 0.0;
        double m_progressTarget = 0.0;

        std::unique_ptr<LoadingView> m_view;
    };
}
