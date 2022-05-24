#include <abyss/utils/DebugMenu/parser/XMLParser.hpp>

#include <abyss/utils/DebugMenu/RootFolder.hpp>

#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::DebugMenu;

    class ParserImpl
    {
    public:

        Node parseRoot(s3d::FilePathView path, bool isRoot)
        {
            const XMLReader xml(path);
            if (!xml) {
                return Node(this->makeFolderNode(isRoot));
            }
            return this->parseFolder(xml, isRoot);
        }
    private:
        Node parseFolder(const XMLElement& xml, bool isRoot = false)
        {
            auto key = xml.name();
            auto label = xml.attribute(U"label").value_or(key);
            Node ret(this->makeFolderNode(isRoot, key, label));
            return ret;
        }

        template<class... Args>
        std::shared_ptr<INode> makeFolderNode(bool isRoot, Args&&... args)
        {
            return isRoot ?
                std::make_shared<RootFolder>(std::forward<Args>(args)...) :
                std::make_shared<Folder>(std::forward<Args>(args)...);
        }
    };
}
namespace abyss::DebugMenu
{
    Node XMLParser::ParseFrom(s3d::FilePathView path, bool isRoot)
    {
        return ::ParserImpl{}.parseRoot(path, isRoot);
    }
}
