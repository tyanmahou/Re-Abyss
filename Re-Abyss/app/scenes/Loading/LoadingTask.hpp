#pragma once
#include <functional>
#include <abyss/utils/Coro/Generator/Generator.hpp>

namespace abyss::Loading
{
    class LoadingTask
    {
        using FuncType = std::function<void(std::stop_token)>;
        using ProgressFuncType = std::function<Coro::Generator<double>(std::stop_token)>;
    public:
        template<class T>
        LoadingTask(T&& task):
            LoadingTask(0, std::forward<T>(task))
        {}

        LoadingTask(LoadingTask&& other);

        void load() const;
        Coro::Generator<double> loadProgress(std::stop_token token) const;
    private:
        LoadingTask(char, FuncType task);
        LoadingTask(int, ProgressFuncType task);
    private:

        std::variant<
            FuncType,
            ProgressFuncType
        > m_task;
    };
}
