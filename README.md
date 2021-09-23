# pm2021_fireWorksApp_template
花火描画プログラムのテンプレート

# 準備
## 1. addon
- ofxOscを入れる

## 2. ソースファイル(.cpp, .h, .hpp)
- oFプロジェクト内のsrcディレクトリに入れる（既存のファイルは置き換えるか，上書き保存でOK）
- コードの説明
    - oFデフォルトコード
        - main.cpp
        - ofApp.cpp
        - ofApp.h
    - 追加コード
        - define.h：設定値の記述
        - confReader.hpp：設定ファイル読み込み用コード

## 3. 設定ファイル(.conf)
- oFプロジェクトのbin/dataディレクトリにsetting.confを入れる
（基本的な設定項目はこのファイルで編集可能）

# 動作説明
- DB参照アプリから，OSC通信で信号（発射したい花火の種類（現状0~6の7種））が送られてくる  
- ofApp.cppのupdate()内に受信信号に応じた条件分岐があるので，そこに花火の発射トリガーを書けばOK

# 参考
- 設定ファイルの読み込みには，下記コードを使用した
- https://github.com/TTRist/confReader