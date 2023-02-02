#include <abyss/scenes/Loading/Loader.hpp>
#include <abyss/scenes/Loading/Common/Loading.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Loading;

    class AsyncLoading
    {
    public:
        AsyncLoading(std::function<void()> task) :
            m_task(this->load(std::move(task)))
        {}

        AsyncLoading(Coro::Generator<double> task):
            m_task(this->loadAsync(std::move(task)))
        {}

        double progress() const
        {
            return m_progress;
        }
        bool resume() const
        {
            return m_task.resume();
        }
        bool isDone() const
        {
            return m_task.isDone();
        }
    private:
        Coro::Fiber<> load(std::function<void()> task)
        {
            m_progress = 0.0;
            co_await Coro::Aysnc(std::move(task));
            m_progress = 1.0;
        }
        Coro::Fiber<> loadAsync(Coro::Generator<double> task)
        {
            m_progress = 0.0;
            co_await Coro::Aysnc([&] {
                for (auto progress : task) {
                    m_progress = progress;
                }
            });
            m_progress = 1.0;
        }
    private:
        double m_progress = 0.0;
        Coro::Fiber<void> m_task;
    };

    struct LoadTask
    {
    public:
        LoadTask(std::unique_ptr<AsyncLoading> task, std::unique_ptr<ILoading> loading) :
            m_task(std::move(task)),
            m_loading(std::move(loading))
        {
            m_fiber.reset(std::bind(&LoadTask::updateAsync, this));
        }
        bool update()
        {
            return m_fiber.resume();
        }
        void draw() const
        {
            if (m_loading) {
                m_loading->draw();
            }
        }
        double progress() const
        {
            return m_task->progress();
        }
    private:

        Coro::Fiber<void> updateAsync()
        {
            return loadAsync() & updateLoadingAsync();
        }
        Coro::Fiber<void> loadAsync()
        {
            while (m_task->resume()) {
                co_yield{};
            }
        }
        Coro::Fiber<void> updateLoadingAsync()
        {
            if (!m_loading) {
                co_return;
            }
            while (m_loading->update(this->progress())) {
                co_yield{};
            }
        }
    private:
        Coro::FiberHolder<void> m_fiber;
        std::unique_ptr<AsyncLoading> m_task;
        std::unique_ptr<ILoading> m_loading;
    };
}
namespace abyss::Loading
{
    class Loader::Impl
    {
    public:
        Impl()
        {

        }
        void start(std::function<void()> task)
        {
            task();
        }
        void start(Coro::Generator<double> task)
        {
            for ([[maybe_unused]]auto progress : task) {
            }
        }
        void startAsync(std::unique_ptr<AsyncLoading> task, std::unique_ptr<ILoading> loading)
        {
            m_loadingTasks.emplace(std::move(task), std::move(loading));
        }
        bool update()
        {
            if (m_loadingTasks.empty()) {
                return false;
            }
            auto& front = m_loadingTasks.front();
            if (!front.update()) {
                m_loadingTasks.pop();
            }
            return !m_loadingTasks.empty();
        }

        void draw() const
        {
            if (m_loadingTasks.empty()) {
                return;
            }
            auto& front = m_loadingTasks.front();
            front.draw();
        }

        bool isDone() const
        {
            return m_loadingTasks.empty();
        }
    private:
        std::queue<LoadTask> m_loadingTasks;
    };
    Loader::Loader() :
        m_pImpl(std::make_unique<Impl>())
    {
    }
    Loader::~Loader()
    {}
    void Loader::start(std::function<void()> task)
    {
        m_pImpl->start(std::move(task));
    }
    void Loader::start(Coro::Generator<double> task)
    {
        m_pImpl->start(std::move(task));
    }
    void Loader::startAsync(std::function<void()> task)
    {
        m_pImpl->startAsync(
            std::make_unique<AsyncLoading>(std::move(task)),
            std::make_unique<Common::Loading>()
            );
    }
    void Loader::startAsync(Coro::Generator<double> task)
    {
        m_pImpl->startAsync(
            std::make_unique<AsyncLoading>(std::move(task)),
            std::make_unique<Common::Loading>()
        );
    }
    bool Loader::update()
    {
        return m_pImpl->update();
    }
    void Loader::draw() const
    {
        return m_pImpl->draw();
    }
    bool Loader::isLoading() const
    {
        return !this->isDone();
    }
    bool Loader::isDone() const
    {
        return m_pImpl->isDone();
    }
}
