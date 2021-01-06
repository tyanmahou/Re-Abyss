#pragma once
#include <abyss/commons/Resource/SaveUtil.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class DBDataStore
    {
    protected:
        s3dsql::SQLite3 m_db;
    public:
        DBDataStore();
        DBDataStore(const s3d::String& path);
        INJECT_CTOR(DBDataStore(const std::shared_ptr<s3dsql::SQLite3>& db));
        virtual ~DBDataStore() = default;
    };

    struct DBInstaller final : emaject::IInstaller
    {
        DBInstaller();
        DBInstaller(const s3d::String& path);
        void onBinding(emaject::Container* conatienr) const override;

    private:
        std::shared_ptr<s3dsql::SQLite3> m_db;
    };

    template<class From, class To>
    struct DBDataStoreInataller final : emaject::IInstaller
    {
        void onBinding(emaject::Container* conatienr) const override
        {
            conatienr->bind<From>()
                .to<To>()
                .asCache();
        }
    };
}