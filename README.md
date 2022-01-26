棒人間のＴＣＧのシミュレーター（自分用）

---

picture/card/ にカードの画像

picture/sheet/ にプレイマットの画像

deck/ にデッキのデータ（テキストファイル）

を置くこと。

---

外出先でも遊びたい――そんな願いをかなえるアプリケーション。

棒人間ＴＣＧのシミュレータです。

ただし、最低限の機能しかないので面白さは落ちるかと。

ご了承ください。


・使い方

まず"deck"フォルダに、使用するデッキの情報をテキストファイルで置いときます。

使用するカードの画像は"picture/card"に置く必要があります。

.exeファイルを起動し、使用するデッキの名前（例えば、"deck1.txt"なら、"deck1"）を
キーボードで入力します。

２つのデッキを指定し終えたら、シミュレーションが始まります。

あとはボタンを適当に押して、自力でシミュレーションを頑張ってください。

終了するにはエスケープキーを押してください。


・デッキの情報の書き方

１行目から、使用するカードの名前（例えば、"no1.png"なら"no1"）を書き、改行します。

次の行には、そのカードの枚数を数字で書きます。

その次以降の行も同様に、カードの名前と枚数を交互に書いていけばいいです。

例：
---------
no1	←カードの名前

3	←その枚数

no35

3

no12

2

----------


TCG Simulator (ver1.0)

(2021/7/29 作成) by のけもの

--
使用ツール：ＤＸライブラリ

--
著作者：のけもの

twitter：@NoKmono23（ https://twitter.com/NoKmono23 ）

--
更新履歴
2021/7/29 ver1.0の完成
