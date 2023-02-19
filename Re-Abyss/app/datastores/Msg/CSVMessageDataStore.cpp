#include <abyss/datastores/Msg/CSVMessageDataStore.hpp>
#include <abyss/commons/Path.hpp>

namespace
{
    using namespace abyss::Resource::Msg;

    // 決め打ちで高速化
    size_t LangColumn(const Language& lang)
    {
        if (lang == Language::Ja()) {
            return 1;
        }
        return 1;
    }
}
namespace abyss::Resource::Msg
{
    CSVMessageDataStore::CSVMessageDataStore(Assets* pAssets):
        m_pAssets(pAssets)
    {
    }
    s3d::Array<std::pair<s3d::String, s3d::String>> CSVMessageDataStore::select(s3d::StringView category, const Language& lang) const
    {
        s3d::Array<std::pair<s3d::String, s3d::String>> ret;
        s3d::CSV csv = m_pAssets->loadCSV(category + U".csv", Path::MsgPath);
        if (!csv) {
            return ret;
        }
        if (csv.rows() <= 1) {
            return ret;
        }
        size_t langColumn = ::LangColumn(lang);
        for (size_t row = 1; row < csv.rows(); ++row) {
            if (auto&& msg = csv.get(row, langColumn)) {
                ret.push_back(std::make_pair(csv.get(row, 0), std::move(msg)));
            }
        }
        return ret;
    }
}
