#pragma once
#include <Siv3D/Array.hpp>

namespace abyss::User
{
    class IMigrationVersionDataStore
    {
    public:
        virtual ~IMigrationVersionDataStore() = default;

        virtual bool create() const = 0;

        virtual s3d::int32 selectCurrentVersion()const = 0;
        virtual bool update(const s3d::Array<s3d::int32>& versions)const = 0;
        virtual bool erase(s3d::int32 versionId)const = 0;
    };
}