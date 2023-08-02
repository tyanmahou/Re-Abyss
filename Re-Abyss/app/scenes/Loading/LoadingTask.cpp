#include <abyss/scenes/Loading/LoadingTask.hpp>

namespace abyss::Loading
{
    LoadingTask::LoadingTask(char, FuncType task) :
        m_task(std::move(task))
    {
    }
    LoadingTask::LoadingTask(int, ProgressFuncType task):
        m_task(std::move(task))
    {
    }
    LoadingTask::LoadingTask(LoadingTask&& other):
        m_task(std::move(other.m_task))
    {
    }
    void LoadingTask::load() const
    {
        if (std::holds_alternative<FuncType>(m_task)) {
            std::get<FuncType>(m_task)(std::stop_token{});
        } else if (std::holds_alternative<ProgressFuncType>(m_task)) {
            for ([[maybe_unused]]double progress : std::get<ProgressFuncType>(m_task)(std::stop_token{})) {
            }
        }
    }
    Coro::Generator<double> LoadingTask::loadProgress(std::stop_token token) const
    {
        co_yield 0;
        if (std::holds_alternative<FuncType>(m_task)) {
            std::get<FuncType>(m_task)(token);
        } else if (std::holds_alternative<ProgressFuncType>(m_task)) {
            for (double progress: std::get<ProgressFuncType>(m_task)(token)) {
                co_yield progress;
            }
        }
        co_yield 1;
    }
}
