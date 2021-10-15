#pragma once
#include <abyss/commons/Fwd.hpp>

#include <abyss/components/Novel/base/ITalker.hpp>
#include <abyss/models/Novel/OldSerifModel.hpp>

namespace abyss::Novel
{
    class SerifCtrl : 
        public ITalker
    {
    public:
        SerifCtrl(TalkObj* pTalk, const OldSerifModel& serif);

        void onStart() override;
        void onEnd() override;

        Coro::Task<> onTalk() override;


        const s3d::Optional<s3d::String>& getActorName()const;

        OldSerifModel::Side getSide() const;

        const s3d::Array<OldSerifModel::Message>& getMessages()const;

        const s3d::String& getMessage(size_t index)const;

        s3d::int32 getStrIndex()const;

        bool isAll()const;
        bool isLeft()const;
        bool isRight()const;

        s3d::String getPrev() const;
        const s3d::String& getCurrent() const;
        const s3d::String& getCurrentKind()const;

        bool isEnd() const;
    private:
        TalkObj* m_pTalk;
        OldSerifModel m_serif;
    };
}