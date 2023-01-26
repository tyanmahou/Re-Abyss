#pragma once

namespace abyss
{
    /// <summary>
    /// シーン種類
    /// </summary>
    enum class SceneKind
    {
        Invalid,
        /// <summary>起動シーン</summary>
        Boot,
        /// <summary>スプラッシュ</summary>
        Splash,
        /// <summary>OPデモ</summary>
        OpDemo,
        /// <summary>タイトル</summary>
        Title,
        /// <summary>セーブ選択</summary>
        SaveSelect,
        /// <summary>ホーム画面</summary>
        Home,
        /// <summary>ステージ</summary>
        Stage,
        /// <summary>ステージリザルト</summary>
        StageResult,

#if ABYSS_DEVELOP
        /// <summary>開発ポータル</summary>
        DevPortal,
        /// <summary>実験シーン</summary>
        Experiment,
#endif
    };
}
