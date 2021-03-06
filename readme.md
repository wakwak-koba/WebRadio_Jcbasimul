# WebRadio_Jcbasimul

### 機能
- [WebRadio_with_ESP8266Audio](https://github.com/m5stack/M5Unified/tree/master/examples/Advanced/WebRadio_with_ESP8266Audio) をベースにして、[JCBAインターネットサイマルラジオ](https://www.jcbasimul.com/) が聴けるようにしました。
- 2022年4月時点で公開されている全132局を網羅しています。
- 選局と音量は不揮発性メモリに保存され、次回の起動時に初期採用されます。
- 試験的に [リリースパッケージ](release/) も用意しました。Arduino 環境のない方でもインストールできます。

![image1](docs/screenshot.png)

### WiFi設定
SDカードを用いて WiFi の設定が行えます。  
いったん接続に成功すれば、以降はSDカードは必要ありません。  
具体的な記述方法は [説明](sdcard/) をご覧ください。

![image1](docs/wifi.png)

### 操作方法
|ボタン|動作|
|:-------------:|:----:|
|Aボタン1回クリック|選局・次|
|Aボタン2回クリック|選局・前|
|Bボタン|音量・減|
|Cボタン|音量・増|

### 各自で調整するとよい箇所
全132局を網羅したため、あまりに多すぎて選局が大変です。  
Arduino のビルド環境が必要とはなりますが、不要な局はコメント行にして必要最小限にすると快適になるかと思います。

### ビルドに必要なライブラリ
- [espressif/arduino-esp32](https://github.com/espressif/arduino-esp32/releases/tag/2.0.2)
- [m5stack/M5GFX](https://github.com/m5stack/M5GFX)
- [m5stack/M5Unified](https://github.com/m5stack/M5Unified)
- [earlephilhower/ESP8266Audio](https://github.com/earlephilhower/ESP8266Audio)
- [Links2004/arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets)
- [arduino-libraries/Arduino_JSON](https://github.com/arduino-libraries/Arduino_JSON)

### ビルド時の注意
　PSRAM:Enabled にしてビルドすると、低速な PSRAM をバッファとして利用されうるコードが生成されてしまいます。  
　PSRAM:Disabled でビルドされることを強く推奨します。
 
### ペンディング中
- 番組名も取得可能と思われるが調査中

### 謝辞
かっこいいビジュアルは [lovyan03](https://github.com/lovyan03/) さんの制作です。  
ずっと見てても飽きないですよね！
