#pragma once
#include <memory>
#include <concepts>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Cron/base/BatchHolder.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Cron
{
    template<class Type, class... Args>
    concept BatchBuildable = requires(Batch * pBatch, Args&&... args)
    {
        Type::Build(pBatch, std::forward<Args>(args)...);
    };

    class Crons
    {
    private:
        Cron::BatchHolder m_batchs;

        Manager* m_pManager = nullptr;
    public:
        Crons& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }

        void update();

        /// <summary>
        /// バッチの作成
        /// </summary>
        /// <returns></returns>
        Ref<Batch> create();

        /// <summary>
        /// ビルダーからバッチの作成
        /// </summary>
        template<class Type, class... Args>
        Ref<Batch> create(Args&& ... args)
            requires BatchBuildable<Type, Args...>
        {
            auto obj = this->create();
            Type::Build(obj.get(), std::forward<Args>(args)...);
            return obj;
        }

        /// <summary>
        /// バッチの登録
        /// </summary>
        /// <param name="batch"></param>
        /// <returns></returns>
        Ref<Batch> regist(const std::shared_ptr<Batch>& batch);
    };
}
