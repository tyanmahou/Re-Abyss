#include <abyss/scenes/Loading/LoadProcessor.hpp>
#include "LoadProcessor.hpp"

namespace abyss::Loading
{
    LoadProcessor::LoadProcessor(char, FuncType task) :
        m_task(std::move(task))
    {
    }
    LoadProcessor::LoadProcessor(int, ProgressFuncType task):
        m_task(std::move(task))
    {
    }
    bool LoadProcessor::isPrimitiveFunc() const
    {
        return std::holds_alternative<FuncType>(m_task);
    }
    bool LoadProcessor::isProgressFunc() const
    {
        return std::holds_alternative<ProgressFuncType>(m_task);
    }
    void LoadProcessor::execPrimitiveFunc(std::stop_token token) const
    {
        return std::get<FuncType>(m_task)(token);
    }
    Coro::Generator<double> LoadProcessor::execProgressFunc(std::stop_token token) const
    {
        return std::get<ProgressFuncType>(m_task)(token);
    }
    LoadProcessor::LoadProcessor(LoadProcessor&& other):
        m_task(std::move(other.m_task))
    {
    }
    void LoadProcessor::load() const
    {
        if (this->isPrimitiveFunc()) {
            this->execPrimitiveFunc(std::stop_token{});
        } else if (this->isProgressFunc()) {
            for ([[maybe_unused]]double progress : this->execProgressFunc(std::stop_token{})) {
            }
        }
    }
    Coro::Generator<double> LoadProcessor::loadProgress(std::stop_token token) const
    {
        co_yield 0;
        if (this->isPrimitiveFunc()) {
            this->execPrimitiveFunc(token);
        } else if (this->isProgressFunc()) {
            for (double progress: this->execProgressFunc(token)) {
                co_yield progress;
            }
        }
        co_yield 1;
    }
}
