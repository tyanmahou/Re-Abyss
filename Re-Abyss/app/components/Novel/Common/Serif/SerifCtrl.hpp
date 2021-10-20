#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <abyss/models/Novel/SerifModel.hpp>

namespace abyss::Novel
{
    class SerifCtrl :
        public ICommand
    {
    public:
        SerifCtrl(TalkObj* pTalk);

        void onStart() override;
        void onEnd() override;

        Coro::Task<> onCommand() override;

        const SerifModel& getCurrent() const;
        const s3d::Optional<SerifModel>& getPrev() const;
    private:
        TalkObj* m_pTalk;

        s3d::Array<SerifModel> m_serifs;
        size_t m_serifIndex = 0;
        s3d::int32 m_strIndex = 0;
    };
}