#pragma once
#include <memory>
#include <concepts>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/Cron.hpp>
#include <abyss/modules/Cron/base/BatchHolder.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
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
        Ref<Cron::Batch> create();

        /// <summary>
        /// ビルダーからバッチの作成
        /// </summary>
        template<class Type, class... Args>
        Ref<Cron::Batch> create(Args&& ... args)
            requires Cron::BatchBuildy<Type, Args...>
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
        Ref<Cron::Batch> regist(const std::shared_ptr<Cron::Batch>& batch);
    };
}