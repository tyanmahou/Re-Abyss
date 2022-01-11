#pragma once
#include <Siv3D/HashTable.hpp>

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

        /// <summary>
        /// ダメージを受けるか
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        bool isDamaged(s3d::uint64 id) const;

        /// <summary>
        /// コンボ数を取得
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        s3d::int32 getComboCount(s3d::uint64 id) const;

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