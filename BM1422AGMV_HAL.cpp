/*
 * BM1422AGMV_HAL.cpp
 *
 *  Created on: Dec 16, 2024
 *      Author: Sezakiaoi
 */

#include <BM1422AGMV_HAL.h>
#include <i2c.h>


void BM1422AGMV_HAL::write(BM1422AGMV_HAL::REGISTER REGISTER_ADDR, uint8_t* command, uint8_t len){

	HAL_I2C_Mem_Write(&hi2c2, I2C_ADDR, uint8_t(REGISTER_ADDR), 1, command, len, 10);
}

void BM1422AGMV_HAL::read(BM1422AGMV_HAL::REGISTER REGISTER_ADDR, uint8_t* receive_buffer, uint8_t len){

	HAL_I2C_Mem_Read(&hi2c2, I2C_ADDR, uint8_t(REGISTER_ADDR), 1, receive_buffer, len, 10);
}
