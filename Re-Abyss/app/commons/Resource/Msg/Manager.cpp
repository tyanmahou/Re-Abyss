#include <abyss/commons/Resource/Msg/Manager.hpp>
#include <abyss/commons/Resource/Msg/MessageTable.hpp>
#include <abyss/commons/Path.hpp>
#include <Siv3D.hpp>

namespace abyss::Resource::Msg
{
    class Manager::Impl
    {
    public:
        void load(const Language& lang)
        {
            this->loadFile(U"Common", lang);
            this->loadFile(U"SaveSelect", lang);
            this->loadFile(U"Title", lang);
        }
        void loadFile(s3d::StringView category, const Language& lang)
        {
            s3d::CSV csv(Path::MsgPath + category + U".csv");
            if (!csv) {
                return;
            }
            if (csv.rows() <= 1) {
                return;
            }
            size_t langColumn = 0;
            for (auto&& l : csv.getRow(0)) {
                if (l == lang.toStrView()) {
                    break;
                }
                langColumn++;
            }
            if (langColumn == csv.columns(0)) {
                return;
            }
            for (size_t row = 1; row < csv.rows(); ++row) {
                if (auto&& msg = csv.get(row, langColumn)) {
                    m_table.add(category, csv.get(row, 0),std::move(msg));
                }
            }
        }
        const s3d::String& get(const Label& label)
        {
            return m_table.get(label);
        }
    private:
        MessageTable m_table;
    };

    Manager::Manager():
        m_pImpl(std::make_unique<Impl>())
    {}

    void Manager::Load(const Language& lang)
    {
        return Instance()->m_pImpl->load(lang);
    }

    const s3d::String& Manager::Get(const Label& label)
    {
        return Instance()->m_pImpl->get(label);
    }
}
