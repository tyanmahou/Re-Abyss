#include <abyss/utils/DebugMenu/parser/MenuParser.hpp>

#include <abyss/utils/DebugMenu/RootFolder.hpp>
#include <abyss/utils/DebugMenu/BoolItem.hpp>
#include <abyss/utils/DebugMenu/Button.hpp>
#include <abyss/utils/DebugMenu/RadioButton.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

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

            bool isPushPath = false;
            if (auto path = xml.attribute(U"callbackPath")) {
                isPushPath = true;
                m_callbackPathStack.push(*path);
            }
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
                    ret.add(this->parseRadioButton(e));
                } else if (e.firstChild()) {
                    // folder
                    ret.add(this->parseFolder(e));
                } else if (auto custom = e.attribute(U"custom")) {
                    // custom
                    // @todo
                    continue;
                } else {
                    // button
                    ret.add(this->parseButton(e));
                }
            }
            if (isPushPath) {
                m_callbackPathStack.pop();
            }
            return ret;
        }
        Node parseValue(const XMLElement& xml)
        {
            auto key = xml.name();
            auto label = xml.attribute(U"label").value_or(key);
            auto value = xml.attribute(U"value").value_or(U"false");

            bool initValue = s3d::ParseOpt<bool>(value).value_or(false);
            auto callback = this->findCallback<void(bool)>(xml.attribute(U"callback"));

            return Node::Create<BoolItem>(key, label, initValue, callback);
        }
        Node parseButton(const XMLElement& xml)
        {
            auto key = xml.name();
            auto label = xml.attribute(U"label").value_or(key);

            auto callback = this->findCallback<void()>(xml.attribute(U"callback"));

            return Node::Create<Button>(key, label, callback);
        }
        Node parseRadioButton(const XMLElement& xml)
        {
            auto key = xml.name();
            auto label = xml.attribute(U"label").value_or(key);
            auto select = xml.attribute(U"select").value_or(U"0");
            auto initSelect = s3d::ParseOpt<size_t>(select).value_or(0);

            RadioButton::CallbackType callback;
            if (auto c1 = this->findCallback<void(size_t)>(xml.attribute(U"callback"))) {
                callback = c1;
            } else if (auto c2 = this->findCallback<void(s3d::StringView)>(xml.attribute(U"callback"))) {
                callback = c2;
            } else if (auto c3 = this->findCallback<void(size_t, s3d::StringView)>(xml.attribute(U"callback"))) {
                callback = c3;
            }
            auto radioButton = std::make_shared<RadioButton>(key, label, callback);
            for (auto item = xml.firstChild(); item; item = item.nextSibling()) {
                auto itemValue = item.attribute(U"value").value_or(U"");
                auto itemLabel = item.attribute(U"label").value_or(itemValue);

                radioButton->addList(itemValue, itemLabel);
            }
            radioButton->setSelect(initSelect);

            return Node(radioButton);
        }
        template<class... Args>
        std::shared_ptr<INode> makeFolderNode(bool isRoot, Args&&... args)
        {
            return isRoot ?
                std::make_shared<RootFolder>(std::forward<Args>(args)...) :
                std::make_shared<Folder>(std::forward<Args>(args)...);
        }

        template<class F>
        std::function<F> findCallback(const s3d::Optional<s3d::String>& path)
        {
            if (!path) {
                return nullptr;
            }
            return this->findCallback<F>(*path);
        }
        template<class F>
        std::function<F> findCallback(const s3d::String& path)
        {
            if (auto callback = Reflect<>::find<F>(this->callbackPath(path))){
                return callback;
            }
            if (auto callback = Reflect<>::find<F>(path)) {
                return callback;
            }
            return nullptr;
        }
        s3d::String callbackPath(const s3d::String& path)
        {
            if (m_callbackPathStack.empty() || m_callbackPathStack.top().isEmpty()) {
                return path;
            }
            return U"{}::{}"_fmt(m_callbackPathStack.top(), path);
        }
    private:
        std::stack<s3d::String> m_callbackPathStack;
    };
}
namespace abyss::DebugMenu
{
    Node MenuParser::FromXML(s3d::FilePathView path, bool isRoot)
    {
        return ::XMLParserImpl{}.parseRoot(path, isRoot);
    }
}
