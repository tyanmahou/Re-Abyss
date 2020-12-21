#pragma once
#include <memory>
#include <concepts>
#include <Siv3D/Duration.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Cron/base/BatchHolder.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
    class Cron
    {
    private:
        cron::BatchHolder m_batchs;

        Manager* m_pManager = nullptr;
    public:
        Cron& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }

        void update(double dt);

        /// <summary>
        /// ジョブを登録
        /// </summary>
        Ref<cron::Batch> regist(const std::shared_ptr<cron::IJob>& job, const std::shared_ptr<cron::IScheduler>& scheduler);

        /// <summary>
        /// 定期実行ジョブを登録
        /// </summary>
        /// <param name="duration"></param>
        /// <param name="job"></param>
        Ref<cron::Batch> registInterval(const std::shared_ptr<cron::IJob>& job, const s3d::Duration& duration);

        /// <summary>
        /// 登録
        /// </summary>
        /// <param name="duration"></param>
        /// <param name="job"></param>
        Ref<cron::Batch> registOnce(const std::shared_ptr<cron::IJob>& job);

        /// <summary>
        /// 定期実行ジョブを作成
        /// </summary>
        template<class Type, class... Args>
        Ref<cron::Batch> createInterval(const s3d::Duration& duration, Args&& ... args)
            //requires IsUserInterface<Type> && std::constructible_from<Type, Args...>
        {
            auto job = std::make_shared<Type>(std::forward<Args>(args)...);
            return this->registInterval(job, duration);
        }

        /// <summary>
        /// 一回ジョブを作成
        /// </summary>
        template<class Type, class... Args>
        Ref<cron::Batch> createOnce(Args&& ... args)
            //requires IsUserInterface<Type> && std::constructible_from<Type, Args...>
        {
            auto job = std::make_shared<Type>(std::forward<Args>(args)...);
            return this->registOnce(job);
        }
    };
}