#pragma once
#include <abyss/utils/DB/DBBindDef.hpp>

namespace abyss::DBUtil
{
    template<DBBindable Type>
    s3d::Optional<Type> FetchOne(const s3dsql::SQLite3& db, s3d::StringView sql, const s3dsql::DBValueArray& param = {})
    {
        s3d::Optional<Type> ret;
        db.fetchOne(sql, param).then([&](s3dsql::DBRow& row) {
            ret = FromRow<Type>(row);
        });
        return ret;
    }

    template<DBBindable Type>
    s3d::Optional<Type> FetchOne(const s3dsql::SQLite3& db, s3d::StringView sql, const s3dsql::DBValueMap& param)
    {
        s3d::Optional<Type> ret;
        db.fetchOne(sql, param).then([&](s3dsql::DBRow& row) {
            ret = FromRow<Type>(row);
        });
        return ret;
    }

    template<DBBindable Type>
    s3d::Array<Type> Fetch(const s3dsql::SQLite3& db, s3d::StringView sql, const s3dsql::DBValueArray& param = {})
    {
        s3d::Array<Type> ret;
        for (auto&& row : db.fetch(sql, param)) {
            ret << FromRow<Type>(row);
        }
        return ret;
    }

    template<DBBindable Type>
    s3d::Array<Type> Fetch(const s3dsql::SQLite3& db, s3d::StringView sql, const s3dsql::DBValueMap& param)
    {
        s3d::Array<Type> ret;
        for (auto&& row : db.fetch(sql, param)) {
            ret << FromRow<Type>(row);
        }
        return ret;
    }

    /// <summary>
    /// SQLのValue用にplace Holder作成する
    /// </summary>
    template<size_t Num> requires (Num > 0)
        struct SQLValuePlaceHolder
    {
    private:
        static consteval auto impl()
        {
            std::array<char32_t, Num * 2 + 1> ret{};
            ret[0] = U'(';
            for (size_t count = 0; count < Num; ++count) {
                if (count != 0) {
                    ret[count * 2] = U',';
                }
                ret[count * 2 + 1] = U'?';
            }
            ret[Num * 2] = U')';
            return ret;
        }
        static constexpr auto raw = impl();
    public:
        static constexpr s3d::StringView value{ raw.data(), raw.size() };
    };

    template<size_t Num> requires (Num > 0)
    s3d::String PlaceHolders(size_t size)
    {
        s3d::String phs;
        bool isFirst = true;
        for (size_t count = 0; count < size; ++count) {
            if (!isFirst) {
                phs += U",";
            } else {
                isFirst = false;
            }
            phs += SQLValuePlaceHolder<Num>::value;
        }
        return phs;
    }

    template<size_t Num, class Type, class Func> requires (Num > 0)
    s3d::int32 ExecPlaceHolder(const s3dsql::SQLite3& db, s3d::StringView sql, const s3d::Array<Type>& values, Func&& func)
    {
        s3d::String placeHolders = PlaceHolders<Num>(values.size());
        s3dsql::DBValueArray params;
        params.reserve(values.size() * Num);
        for (const auto& value : values) {
            func(params, value);
        }
        return db.exec(s3d::Fmt(sql)(placeHolders), params);
    }
}