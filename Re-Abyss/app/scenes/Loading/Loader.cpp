#include <abyss/scenes/Loading/Loader.hpp>
#include <abyss/scenes/Loading/Common/Loading.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Loading;

    class LoadingThread
    {
    public:
        LoadingThread(std::function<void(std::stop_token)> task) :
            _pr(),
            _f(_pr.get_future()),
            _thread([&, task = std::move(task)](std::stop_token token) {
            try {
                task(token);
                _pr.set_value();
            } catch (...) {
                _pr.set_exception(std::current_exception());
            }
            })
        {
        }
        Coro::Fiber<> get()
        {
            while (_f.wait_for(0s) != std::future_status::ready) {
                co_yield{};
            }
            co_return _f.get();
        }
        void cancel()
        {
            _thread.request_stop();
        }
    private:
        std::promise<void> _pr;
        std::future<void> _f;
        std::jthread _thread;
    };
    class AsyncLoader
    {
    public:
        AsyncLoader(LoadingTask task) :
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
        Coro::Fiber<> loadAsync(LoadingTask task)
        {
            m_progress = 0.0;
            LoadingThread loadingThread([&](std::stop_token token) {
                for (auto progress : task.loadProgress(token)) {
                    m_progress = progress;
                }
            });
            co_await loadingThread.get();
            m_progress = 1.0;
        }
    private:
        double m_progress = 0.0;
        Coro::Fiber<void> m_task;
    };

    class AsyncLoading
    {
    public:
        AsyncLoading(std::unique_ptr<AsyncLoader> task, std::unique_ptr<ILoading> loading) :
            m_task(std::move(task)),
            m_loading(std::move(loading))
        {
            m_fiber.reset(std::bind(&AsyncLoading::updateAsync, this));
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
        std::unique_ptr<AsyncLoader> m_task;
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
        void startSync(LoadingTask task)
        {
            task.load();
        }
        void startAsync(std::unique_ptr<AsyncLoader> task, std::unique_ptr<ILoading> loading)
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
        std::queue<AsyncLoading> m_loadingTasks;
    };
    Loader::Loader() :
        m_pImpl(std::make_unique<Impl>())
    {
    }
    Loader::~Loader()
    {}
    void Loader::start(LoadingTask task)
    {
        m_pImpl->startSync(std::move(task));
    }
    void Loader::startAsync(LoadingTask task)
    {
        m_pImpl->startAsync(
            std::make_unique<AsyncLoader>(std::move(task)),
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
