#pragma once

namespace abyss::DebugMenu
{
    class RootFolder;

    class IMenuSave
    {
    public:
        virtual ~IMenuSave() = default;
        virtual bool load(const RootFolder* pRoot)const = 0;
        virtual bool save(const RootFolder* pRoot)const = 0;
    };
}
