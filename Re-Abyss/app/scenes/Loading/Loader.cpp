#include <abyss/scenes/Loading/Loader.hpp>
#include <abyss/scenes/Loading/Common/Loading.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>
#include <abyss/utils/Thread/Task.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Loading;

    class AsyncLoader
    {
    public:
        AsyncLoader(LoadProcessor task):
            m_task(std::make_unique<Coro::Fiber<void>>(this->loadAsync(std::move(task))))
        {
        }

        double progress() const
        {
            return m_progress;
        }
        bool resume()
        {
            if (!m_task) {
                return false;
            }
            return m_task->resume();
        }
        bool isDone() const
        {
            if (!m_task) {
                return false;
            }
            return m_task->isDone();
        }
        void requestCancel()
        {
            if (m_task) {
                m_task = nullptr;
            }
        }
    private:
        Coro::Fiber<> loadAsync(LoadProcessor task)
        {
            co_await task.loadAsync(m_progress);
        }
    private:
        double m_progress = 0.0;
        std::unique_ptr<Coro::Fiber<void>> m_task;
    };

    class AsyncLoading : public ILoadingOperation
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
        void requestCancel() override
        {
            m_task->requestCancel();
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
        void startSync(LoadProcessor task)
        {
            task.load();
        }
        LoadingHundler startAsync(std::unique_ptr<AsyncLoader> task, std::unique_ptr<ILoading> loading)
        {
            auto operation = std::make_shared<AsyncLoading>(std::move(task), std::move(loading));
            m_loadingTasks.push(operation);
            return LoadingHundler(operation);
        }
        bool update()
        {
            if (m_loadingTasks.empty()) {
                return false;
            }
            auto& front = m_loadingTasks.front();
            if (!front->update()) {
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
            front->draw();
        }

        bool isDone() const
        {
            return m_loadingTasks.empty();
        }
    private:
        std::queue<std::shared_ptr<AsyncLoading>> m_loadingTasks;
    };
    Loader::Loader() :
        m_pImpl(std::make_unique<Impl>())
    {
    }
    Loader::~Loader()
    {}
    void Loader::start(LoadProcessor&& task)
    {
        m_pImpl->startSync(std::move(task));
    }
    LoadingHundler Loader::startAsync(LoadProcessor&& task)
    {
        return m_pImpl->startAsync(
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
