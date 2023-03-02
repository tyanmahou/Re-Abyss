#pragma once
#include <abyss/modules/Adv/Project/CharaTable.hpp>
#include <Emaject.hpp>

namespace abyss::Adv
{
    class IProjectService;

    /// <summary>
    /// プロジェクト設定
    /// </summary>
    class Project
    {
    public:
        INJECT_CTOR(Project(std::shared_ptr<IProjectService> service));

        /// <summary>
        /// キャラの検索
        /// </summary>
        /// <param name="kind"></param>
        /// <returns></returns>
        s3d::Optional<Chara> findChara(CharaKind kind) const;
    private:
        CharaTable m_charaTable;
    };
}
