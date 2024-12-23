# STM32_BM1422AGMV

デバック完了しました！

エラーの出力とコメントアウトを追加予定

## サンプルコード

初回に1度実行される部分と、ループする部分に分けて書いてあります

それぞれの環境に合わせて使ってください

```cpp
#include "BM1422AGMV.h"

BM1422AGMV bm(&hi2c2);

int16_t mag_data[3] = {};

//1回のみ実行される部分
void init(){

	bm.activation();
	bm.setting(bm.mode::scale_14bit, bm.output_rate::rate_1000hz);
}

//whileでループする部分
void loop(){

	bm.get_data(mag_data);
}
```

## setting()関数について

センサーの基本的な設定をしています

#### 第1引数 出力のスケール
```cpp
scale_12bit
scale_14bit
```

#### 第2引数 出力レート(ODR)
```cpp
rate_10hz 
rate_20hz
rate_100hz
rate_1000hz
```
