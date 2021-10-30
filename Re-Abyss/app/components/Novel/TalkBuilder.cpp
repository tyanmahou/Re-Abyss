#include "TalkBuilder.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

#include <abyss/components/Novel/Common/ClearMessage.hpp>
#include <abyss/components/Novel/Common/ColorTag.hpp>
#include <abyss/components/Novel/Common/MessageStream.hpp>
#include <abyss/components/Novel/Common/ShakeTag.hpp>
#include <abyss/components/Novel/Common/WaitInput.hpp>
#include <abyss/components/Novel/Common/WaitTime.hpp>

#include <abyss/components/Novel/Common/MessageBox.hpp>
#include <abyss/utils/Mns/Script.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss::Novel;
    using namespace Mns;
    using namespace Mns::Ast;
    class EvalImpl final : public IEvalImpl
    {
    public:
        EvalImpl(Engine* pEngine):
            m_pEngine(pEngine)
        {}
    public:
        void eval(const TagStatement& statement) override
        {
            const auto& tag = statement.tag.first;
            const auto& tagValue = statement.tag.second;
            if (tag == U"cm") {
                m_pEngine->addCommand<ClearMessage>();
            } else if (tag == U"l") {
                m_pEngine->addCommand<WaitInput>();
            } else if (tag == U"r") {
                m_pEngine->addCommand<MessageStream>(U"\n");
            } else if (tag == U"color") {
                if (tagValue) {
                    m_pEngine->addCommand<ColorTag>(Color(*tagValue));
                }
            } else if (tag == U"/color") {
                m_pEngine->addCommand<ColorTag>(s3d::none);
            } else if (tag == U"shake") {
                m_pEngine->addCommand<ShakeTag>(true);
            } else if (tag == U"/shake") {
                m_pEngine->addCommand<ShakeTag>(false);
            } else if (tag == U"wait") {
                Duration time{};
                for (const auto& [key, value] : statement.childs) {
                    if (key == U"time" && value) {
                        time = Duration(s3d::Parse<double>(*value));
                    }
                }
                m_pEngine->addCommand<WaitTime>(time);
            }
        }
        void eval(const Ast::NameStatement& statement) override
        {
            //@todo
        }
        void eval(const Ast::TextStatement& statement) override
        {
            m_pEngine->addCommand<MessageStream>(statement.text);
        }
    private:
        Engine* m_pEngine;
    };
}
namespace abyss::Novel
{
    void TalkBuilder::Build(TalkObj* pTalk, const s3d::String& path)
    {
        const auto& engine = pTalk->engine();

        // スクリプトからロード
        {
            Mns::Script script(path);
            EvalImpl eval(engine.get());
            script.eval(&eval);
        }

        pTalk->attach<MessageBox>(pTalk);
    }
}
