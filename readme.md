# STM32_BM1422AGMV

デバック完了しました！

エラーの出力とコメントアウトを追加予定

## サンプルコード

```cpp

#include "BM1422AGMV.h"
#include <cstdint>

BM1422AGMV bm;

int16_t mag_data[3] = {};

//起動時に1回のみ実行
void init(){

    bm.activation();
    bm.setting(bm.mode::scale_12bit, bm.output_rate::rate_1000hz);
}

//whileでループする部分
void loop(){

    bm.get_data(mag_data);
    
    //通信のコードを書く mag_dataはint16
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
