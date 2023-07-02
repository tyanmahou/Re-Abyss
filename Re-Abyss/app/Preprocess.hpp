#pragma once

// デバッグ機能の使用マクロ
#ifdef ABYSS_DEVELOP || ABYSS_STAGING
#define ABYSS_DEBUG 1
#endif

// テスト実行のマクロ
#ifdef ABYSS_DEVELOP
#define ABYSS_DO_TEST 1
#endif

// リソースビルドを使用しないマクロ
#ifdef ABYSS_DEVELOP
#define ABYSS_NO_BUILD_RESOURCE 1
#endif
