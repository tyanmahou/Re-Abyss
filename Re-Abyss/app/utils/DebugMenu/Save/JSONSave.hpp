#pragma once
#include <abyss/utils/DebugMenu/Save/IMenuSave.hpp>

namespace abyss::DebugMenu
{
    class Folder;

    class JSONSave : public IMenuSave
    {
    public:
        JSONSave(const s3d::FilePath& savePath);
        bool load(const RootFolder* pRoot)const override;
        bool save(const RootFolder* pRoot)const override;
    private:
        s3d::FilePath m_savePath;
    };
}
