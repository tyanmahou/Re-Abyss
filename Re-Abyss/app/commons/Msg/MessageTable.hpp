#pragma once
#include <abyss/commons/Msg/Label.hpp>
#include <Siv3D/HashTable.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Msg
{
    /// <summary>
    /// メッセージテーブル
    /// </summary>
    class MessageTable
    {
    public:
        void add(const Label& label, s3d::String message);
        void add(s3d::StringView category, s3d::StringView key, s3d::String message);

        /// <summary>
        /// メッセージ取得
        /// NOTE: 無くてもエラーにならないようにメンバconstをつけてない
        /// </summary>
        /// <param name="label"></param>
        /// <returns></returns>
        const s3d::String& get(const Label& label);
    private:
        s3d::HashTable<s3d::String, s3d::HashTable<s3d::String, s3d::String>> m_table;
    };
}
