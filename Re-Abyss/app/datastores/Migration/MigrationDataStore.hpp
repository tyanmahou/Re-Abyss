#pragma once
#include <abyss/datastores/Migration/base/IMigrationDataStore.hpp>
#include <abyss/datastores/base/DBDataStore.hpp>

namespace abyss::User
{
    class MigrationDataStore : 
        public IMigrationDataStore
    {
    public:
        MigrationDataStore();

        s3d::Array<s3d::int32> versionIds() const override;
        s3d::Array<s3d::int32> updateVersionIds(s3d::int32 currentVersionId) const override;
        void up(s3d::int32 versionId) const override;
        void down(s3d::int32 versionId) const override;
    private:
    };
    using MigrationDataStoreInataller = DBDataStoreInataller<IMigrationDataStore, MigrationDataStore>;
}