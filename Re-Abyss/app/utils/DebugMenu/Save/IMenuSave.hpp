#pragma once

namespace abyss::DebugMenu
{
    class RootFolder;

    class IMenuSave
    {
    public:
        virtual ~IMenuSave() = default;
        virtual bool save(const RootFolder* pRoot)const = 0;
    };
}
