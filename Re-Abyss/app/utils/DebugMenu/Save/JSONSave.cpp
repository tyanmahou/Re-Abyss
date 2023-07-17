#include <abyss/utils/DebugMenu/Save/JSONSave.hpp>
#include <abyss/utils/DebugMenu/RootFolder.hpp>
#include <abyss/utils/DebugMenu/BoolItem.hpp>
#include <abyss/utils/DebugMenu/RadioButton.hpp>

namespace abyss::DebugMenu
{
    JSONSave::JSONSave(const s3d::FilePath& savePath):
        m_savePath(savePath)
    {
    }
    bool JSONSave::load(const RootFolder* pRoot) const
    {
        JSON json(m_savePath);
        if (!json) {
            return false;
        }
        return true;
    }
    bool JSONSave::save(const RootFolder* pRoot) const
    {
        auto saveFolder = [&](this auto&& self, const IFolder* pFolder)->JSON
        {
            JSON json;
            for (const auto& child : pFolder->childNodes()) {
                if (auto boolItem = std::dynamic_pointer_cast<BoolItem>(child)) {
                    json[boolItem->key()] = boolItem->value().toBool();
                } else if (auto radioButton = std::dynamic_pointer_cast<RadioButton>(child)) {
                    json[radioButton->key()] = radioButton->value().toIndex();
                } else if (auto folder = std::dynamic_pointer_cast<Folder>(child)) {
                    if (auto&& child = self(folder.get()); !child.isNull()) {
                        json[folder->key()] = std::move(child);
                    }
                }
            }
            return json;
        };
        JSON result = saveFolder(pRoot);
        return result.save(m_savePath);
    }
}
