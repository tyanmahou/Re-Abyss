#pragma once
#include <functional>
#include <abyss/utils/Coro/Generator/Generator.hpp>

namespace abyss::Loading
{
    class LoadProcessor
    {
        using FuncType = std::function<void(std::stop_token)>;
        using ProgressFuncType = std::function<Coro::Generator<double>(std::stop_token)>;
    public:
        template<class T>
        LoadProcessor(T&& task):
            LoadProcessor(0, std::forward<T>(task))
        {}

        LoadProcessor(LoadProcessor&& other);

        void load() const;
        Coro::Generator<double> loadProgress(std::stop_token token) const;
    private:
        LoadProcessor(char, FuncType task);
        LoadProcessor(int, ProgressFuncType task);

        bool isPrimitiveFunc() const;
        bool isProgressFunc() const;

        void execPrimitiveFunc(std::stop_token token) const;
        Coro::Generator<double> execProgressFunc(std::stop_token token) const;
    private:

        std::variant<
            FuncType,
            ProgressFuncType
        > m_task;
    };
}
