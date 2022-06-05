#include <abyss/debugs/Menu/MenuUtil.hpp>
#include <abyss/debugs/System/System.hpp>
#include <abyss/debugs/Menu/Menu.hpp>

#if ABYSS_DEBUG
namespace abyss::Debug
{
    bool MenuUtil::IsDebug(const s3d::String& label)
    {
        return Debug::System::GetMenu().isDebug(label);
    }
    void MenuUtil::RequestClose()
    {
        Debug::System::GetMenu().close();
    }
}
#endif
