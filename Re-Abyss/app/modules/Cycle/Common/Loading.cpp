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
        AsyncLoading(Coro::Generator<double> task)
        {
            auto func = [t = std::move(task), this]() {
                for (auto progress : t) {
                    m_progress = progress;
                }
            };
            m_task = std::make_unique<Coro::Task<void>>(Coro::Aysnc(std::move(func)));
            //for (auto progress : task) {
            //    m_progress = progress;
            //}
        }
        double progress() const override
        {
            return m_progress;
        }
        bool isDone() const override
        {
            return m_task->isDone() || !m_task->moveNext();
        }
    private:
        double m_progress = 0.0;
        std::unique_ptr<Coro::Task<void>> m_task;
    };
}
namespace abyss::Cycle
{
    Loading::Loading():
        m_view(std::make_unique<LoadingView>())
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
