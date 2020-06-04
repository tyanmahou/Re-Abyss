#pragma once
#include <memory>
#include <concepts>
#include <Siv3D/Duration.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Cron/base/BatchHolder.hpp>
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
        void regist(const std::shared_ptr<cron::IScheduler>& scheduler, const std::shared_ptr<cron::IJob>& job);

        /// <summary>
        /// ジョブを登録
        /// </summary>
        /// <param name="duration"></param>
        /// <param name="job"></param>
        void regist(const s3d::Duration& duration, const std::shared_ptr<cron::IJob>& job);

        /// <summary>
        /// UIを作成
        /// </summary>
        template<class Type, class... Args>
        Ref<Type> create(const s3d::Duration& duration, Args&& ... args)
            //requires IsUserInterface<Type> && std::constructible_from<Type, Args...>
        {
            auto job = std::make_shared<Type>(std::forward<Args>(args)...);
            this->regist(duration, job);
            return job;
        }
    };
}