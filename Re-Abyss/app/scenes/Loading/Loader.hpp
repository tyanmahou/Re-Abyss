#pragma once
#include <memory>
#include <functional>
#include <abyss/scenes/Loading/ILoading.hpp>
#include <abyss/scenes/Loading/LoadingTask.hpp>

namespace abyss::Loading
{
    /// <summary>
    /// ローダー
    /// </summary>
    class Loader
    {
        class Impl;
    public:
        Loader();
        ~Loader();

        /// <summary>
        /// ロード開始
        /// </summary>
        /// <param name="task"></param>
        void start(LoadingTask task);

        /// <summary>
        /// 非同期でロード開始
        /// </summary>
        /// <param name="task"></param>
        void startAsync(LoadingTask task);

        /// <summary>
        /// 更新
        /// </summary>
        bool update();

        /// <summary>
        /// 描画
        /// </summary>
        void draw() const;

        /// <summary>
        /// ロード中か
        /// </summary>
        /// <returns></returns>
        bool isLoading() const;

        /// <summary>
        /// ロード終了したか
        /// </summary>
        /// <returns></returns>
        bool isDone() const;
    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
