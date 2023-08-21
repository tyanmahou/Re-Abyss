# Siv3Dバージョンアップ手順

- 新規プロジェクト作成
- Appフォルダをbuildに変更
  - プロパティの作業フォルダ
  - ビルド後イベントも
- vendorフォルダ移植
  - [ハードリンクの方法](https://qiita.com/opengl-8080/items/c2b6a93dfca5b61f9e6a)
  - スクリプト化してある
- 追加のinclude/libディレクトリィに各種追加
- プリコンパイル済みヘッダー調整
  - stdafx.hppにrename
  - abyss/stdafx.hppに修正
- コマンドラインを調整
  - `/Zc:__cplusplus /source-charset: utf-8 /std:c++latest `
- editorconfigを調整
  - インデントスペース4に
  - xmlドキュメントに
  - elseの改行設定
- ビルド構成を追加しプリプロセッサ調整
  - `Develop`
    - cpp:`ABYSS_DEBUG` `ABYSS_DO_TEST` `ABYSS_NO_BUILD_RESOURCE` `ABYSS_DEVELOP`
    -リソース:`ABYSS_NO_BUILD_RESOURCE`
  - `Staging`
    - cpp: `ABYSS_DEBUG` `ABYSS_STAGING`

### その他

*ASMリストの場所* *オブジェクト ファイル名*を`$(IntDir)%(RelativeDir)`に変更
https://altebute.hatenablog.com/entry/2015/01/01/235301

上記の影響でモジュールがビルドできなくなるので以下の対応が必要  
https://mahou-ptr.hatenablog.com/entry/2023/08/19/235006