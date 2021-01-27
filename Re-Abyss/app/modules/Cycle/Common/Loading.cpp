#include "Loading.hpp"
#include <abyss/views/Cycle/Common/Loading/LoadingView.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Cycle;
    class AsyncLoading final : public ILoadingTask
    {
    public:
        AsyncLoading(std::function<void(double& progress)> func):
            m_task(Coro::Aysnc(func, std::ref(m_progress)))
        {
        }
        double progress() const override
        {
            return m_progress;
        }
        bool isDone() const override
        {
            return m_task.isDone() || !m_task.moveNext();
        }
    private:
        double m_progress = 0.0;
        Coro::Task<void> m_task;
    };
}
namespace abyss::Cycle
{
    Loading::Loading():
        m_view(std::make_unique<LoadingView>())
    {}
    Loading::~Loading()
    {}
    void Loading::start(std::function<void(double& progress)> func)
    {
        m_task = std::make_unique<AsyncLoading>(func);
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
        m_view->draw();
    }
}
