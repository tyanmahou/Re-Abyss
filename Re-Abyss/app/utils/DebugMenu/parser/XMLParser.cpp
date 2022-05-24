#include <abyss/utils/DebugMenu/parser/MenuParser.hpp>

#include <abyss/utils/DebugMenu/RootFolder.hpp>
#include <abyss/utils/DebugMenu/BoolItem.hpp>
#include <abyss/utils/DebugMenu/Button.hpp>
#include <abyss/utils/DebugMenu/RadioButton.hpp>

#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::DebugMenu;

    class XMLParserImpl
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
            auto folderKey = xml.name();
            auto folderLabel = xml.attribute(U"label").value_or(folderKey);
            Node ret(this->makeFolderNode(isRoot, folderKey, folderLabel));

            for (auto e = xml.firstChild(); e; e = e.nextSibling()) {
                auto key = e.name();
                if (key == U"hr") {
                    // @todo
                    continue;
                }
                auto label = e.attribute(U"label").value_or(key);
                if (e.attribute(U"value")) {
                    // value
                    ret.add(this->parseValue(e));
                } else if (e.attribute(U"select")) {
                    // radioButton
                    // @todo
                    continue;
                } else if (e.firstChild()) {
                    // folder
                    ret.add(this->parseFolder(e));
                } else if (auto custom = e.attribute(U"custom")) {
                    // custom
                    // @todo
                    continue;
                } else {
                    // button
                    // @todo
                    continue;
                }
            }

            return ret;
        }
        Node parseValue(const XMLElement& xml)
        {
            auto key = xml.name();
            auto label = xml.attribute(U"label").value_or(key);
            auto value = xml.attribute(U"value").value_or(U"false");

            if (auto boolValue = s3d::ParseOpt<bool>(value)) {
                // @todo callback
                return Node::Create<BoolItem>(key, label, *boolValue);
            }
            return Node::Create<BoolItem>(key, label);
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
    Node MenuParser::FromXML(s3d::FilePathView path, bool isRoot)
    {
        return ::XMLParserImpl{}.parseRoot(path, isRoot);
    }
}
