#include "Loading.hpp"
#include <abyss/views/UI/Common/Loading/LoadingView.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::UI;
    class AsyncLoading final : public ILoadingTask
    {
    public:
        AsyncLoading(Coro::Generator<double> task):
            m_task(this->asyncLoad(std::move(task)) & anim())
        {}
        double progress() const override
        {
            return m_progress;
        }
        bool isDone() const override
        {
            return m_task.isDone() || !m_task.moveNext();
        }
    private:
        Coro::Task<> asyncLoad(Coro::Generator<double> task)
        {
            co_await Coro::Aysnc([&]{
                m_progressTarget = 0.0;
                for (auto progress : task) {
                    m_progressTarget = progress;
                }
                m_progressTarget = 1.0;
            });
        }
        Coro::Task<> anim()
        {
            while (m_progress < 1.0) {
                m_progress += 2.0 * s3d::Scene::DeltaTime();
                if (m_progress >= m_progressTarget) {
                    m_progress = m_progressTarget;
                }
                co_yield{};
            }
        }
    private:
        double m_progress = 0.0;
        double m_progressTarget = 0.0;
        Coro::Task<void> m_task;
    };
}
namespace abyss
{
    Loading::Loading():
        m_view(std::make_unique<UI::LoadingView>())
    {}
    Loading::~Loading()
    {}
    void Loading::start(Coro::Generator<double> task)
    {
        m_task = std::make_unique<AsyncLoading>(std::move(task));
    }
    bool Loading::isDone() const
    {
        if (!m_task) {
            return true;
        }
        return m_task->isDone();
    }
    void Loading::draw() const
    {
        m_view
            ->setProgress(!m_task ? 1.0 : m_task->progress())
            .draw();
    }
}
