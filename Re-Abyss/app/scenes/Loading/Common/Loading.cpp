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
        m_progressTarget = progress;
        m_progress += 3.0 * s3d::Scene::DeltaTime();
        if (m_progress >= m_progressTarget) {
            m_progress = m_progressTarget;
        }
        return m_progress < 1.0;
    }
    void Loading::draw() const
    {
        m_view
            ->setProgress(m_progress)
            .draw();
    }
}

