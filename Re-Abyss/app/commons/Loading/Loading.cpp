#include "Loading.hpp"
#include <abyss/views/UI/Common/Loading/LoadingView.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::UI;
    class AsyncLoading final : public ILoadingTask
    {
    public:
        AsyncLoading(Coro::Generator<double> task):
            m_task(Coro::Aysnc([t = std::move(task), this]() {
                m_progress = 0.0;
                for (auto progress : t) {
                    m_progress = progress;
                }
                m_progress = 1.0;
            }))
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
