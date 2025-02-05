/*
 * BM1422AGMV.cpp
 *
 *  Created on: Dec 16, 2024
 *      Author: aoi25
 *
 *      基本的にデータシートに書いてある手順をそのまま書いています
 *	https://www.marutsu.co.jp/contents/shop/marutsu/datasheet/BM1422AGMV-ZE2.pdf?srsltid=AfmBOoqfdOcrsayBjkr4m8f85_AMl4rc7Bt3exxuVXZ_LP84yWsz81PN
 */

#include <BM1422AGMV.h>

//BM1422AGMV_HALクラスにi2cピンの情報を渡す
BM1422AGMV::BM1422AGMV(I2C_HandleTypeDef* i2c_pin):BM1422AGMV_HAL(i2c_pin){

}

//通信チェック
uint8_t BM1422AGMV::verify_connection(){

	uint8_t who_am_i = 0x00;
	uint8_t error_count = 0;
	
	//WHO_AM_I 0x41なら成功
	while(who_am_i != 0x41){

		BM1422AGMV_HAL::read(REGISTER::WIA, &who_am_i, 1);
		error_count ++;
	}

	return 0;
}

uint8_t BM1422AGMV::setting(BM1422AGMV::mode mode, BM1422AGMV::output_rate rate){


	//12bitmodeでのoutput_rate(ODR)設定
	//12bitmode 0x80 + rate（同レジスタ内）
	if(uint8_t(mode) == 0){

		uint8_t CTNL1_command = 0x80 + ((uint8_t)rate << 3);
		BM1422AGMV_HAL::write(REGISTER::CNTL1, &CTNL1_command, 1);
	}

	//14bitmodeでのoutput_rate(ODR)設定
	//14bitmode 0xC0 + rate（同レジスタ内）
	else if(uint8_t(mode) == 1){

		uint8_t CTNL1_command = 0xC0 + ((uint8_t)rate << 3);
		BM1422AGMV_HAL::write(REGISTER::CNTL1, &CTNL1_command, 1);
	}

	//CTNL4 リセット解除
	//0x00を連続する2つのレジスタに書き込む（リセット解除）
	uint8_t CTNL4_command[2] = {};
	BM1422AGMV_HAL::write(REGISTER::CNTL4, CTNL4_command, 2);

	//CTNL2 DataReadyの有効化
	//0x0Cを書き込む（有効化)
	uint8_t CTNL2_command = 0x0C;
	BM1422AGMV_HAL::write(REGISTER::CNTL2, &CTNL2_command, 1);

	//CTNL3 　測定モードの設定
	//0x40を書き込む（連続測定モード）
	uint8_t CTNL3_command = 0x40;
	BM1422AGMV_HAL::write(REGISTER::CNTL3, &CTNL3_command, 1);

	return 0;
}

uint8_t BM1422AGMV::get_data(int16_t mag_data[3]){
	
	//DATA_Xから6byteを読む
	BM1422AGMV_HAL::read(BM1422AGMV::REGISTER::DATA_X, raw_data, 6);

	//通信失敗
	if(raw_data[0] == 0 && raw_data[2] == 0 && raw_data[4] == 0){

		return 1;
	}
	else{

		//通信成功
		mag_data[0]  = (int16_t)(raw_data[0] | raw_data[1] << 8);
		mag_data[1]  = (int16_t)(raw_data[2] | raw_data[3] << 8);
		mag_data[2]  = (int16_t)(raw_data[4] | raw_data[5] << 8);

		//バッファーのクリア
		for(uint8_t i=0; i<6; i++){

			raw_data[i] = 0;
		}
	}

	return 0;
}
