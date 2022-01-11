#pragma once
#include <Siv3D/HashTable.hpp>
#include <Siv3D/Math.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// コンボレコード
    /// </summary>
    struct ComboRecord
    {
        s3d::int32 comboCount{};
        double comboDuration{};
        double invincibleTime{};

        bool canDamage() const
        {
            return invincibleTime <= 0;
        }

        s3d::int32 calcReductionPower(s3d::int32 power, double reductionRate) const
        {
            const double newPowerF = power * s3d::Pow(reductionRate, comboCount);
            return static_cast<s3d::int32>(s3d::Floor(newPowerF));
        }
    };

    /// <summary>
    /// コンボ履歴統括
    /// </summary>
    class ComboHistory
    {
    public:
        /// <summary>
        /// 更新
        /// </summary>
        /// <param name="dt"></param>
        void update(double dt);

        const ComboRecord& find(s3d::uint64 id);

        /// <summary>
        /// レコード
        /// </summary>
        /// <param name="id"></param>
        /// <param name="comboDuration"></param>
        /// <param name="invincibleTime"></param>
        void updateRecord(s3d::uint64 id, double comboDuration, double invincibleTime);
    private:
        s3d::HashTable<s3d::uint64, ComboRecord> m_records;
    };
}