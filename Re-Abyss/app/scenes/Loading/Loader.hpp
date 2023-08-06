#pragma once
#include <memory>
#include <functional>
#include <abyss/scenes/Loading/ILoading.hpp>
#include <abyss/scenes/Loading/LoadProcessor.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Loading
{
    class ILoadingOperation
    {
    public:
        virtual ~ILoadingOperation() = default;
        virtual void requestCancel() = 0;
    };
    struct LoadingHundler
    {
    public:
        LoadingHundler(std::shared_ptr<ILoadingOperation> operation):
            m_operation(operation)
        {}

        void requestCancel()
        {
            if (m_operation) {
                m_operation->requestCancel();
            }
        }
    private:
        Ref<ILoadingOperation> m_operation;
    };

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
        void start(LoadProcessor&& task);

        /// <summary>
        /// 非同期でロード開始
        /// </summary>
        /// <param name="task"></param>
        LoadingHundler startAsync(LoadProcessor&& task);

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
