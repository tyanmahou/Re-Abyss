#pragma once

namespace abyss
{
    /// <summary>
    /// シーン種類
    /// </summary>
    enum class SceneKind
    {
        /// <summary>エントリーポイント</summary>
        EntryPoint,
        /// <summary>スプラッシュ</summary>
        Splash,
        /// <summary>OPデモ</summary>
        OpDemo,
        /// <summary>タイトル</summary>
        Title,
        /// <summary>セーブ選択</summary>
        SaveSelect,
        /// <summary>ステージ</summary>
        Stage,
        /// <summary>ステージリザルト</summary>
        StageResult,

        /// <summary>エントリーポイント</summary>
        Experiment,
    };
}
