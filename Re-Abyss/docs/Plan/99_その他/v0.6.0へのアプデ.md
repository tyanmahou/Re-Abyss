### ビルド設定の修正

- インクルードディレクトリィなどの変更
```
$(SIV3D_0_6_0)に変更
```
- コマンドラインに追加
```
 /Zc:__cplusplus 
```

### フラグ周り
bool から YesNo に変更

### JSON
JSONReader(filePath) を JSON::Load(filePath) に変更
[U"a.b.c"]が使えなくなったので[U"a"][U"b"][U"c"]に修正