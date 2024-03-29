#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::User
{
    class IMigrationDataStore
    {
    public:
        virtual ~IMigrationDataStore() = default;

        virtual s3d::Array<s3d::int64> versionIds() const = 0;
        virtual s3d::Array<s3d::int64> updateVersionIds(s3d::int64 currentVersionId) const = 0;
        virtual void up(s3d::int64 versionId) const = 0;
        virtual void down(s3d::int64 versionId) const = 0;
    };
}