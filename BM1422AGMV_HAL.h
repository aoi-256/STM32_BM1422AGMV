/*
 * BM1422AGMV_HAL.h
 *
 *  Created on: Dec 16, 2024
 *      Author: Sezakiaoi
 */

#ifndef INC_BM1422AGMV_HAL_H_
#define INC_BM1422AGMV_HAL_H_

#include <cstdint>

class BM1422AGMV_HAL{

	public:

		enum class REGISTER: uint8_t{

			WIA 	= 0x0F,
			DATA_X  = 0x10,
			STA1    = 0x18,
			CNTL1   = 0x1B,
			CNTL2   = 0x1C,
			CNTL3   = 0x1D,
			CNTL4   = 0x5C,
		};

		void write(BM1422AGMV_HAL::REGISTER, uint8_t* command, uint8_t len);
		void read(BM1422AGMV_HAL::REGISTER, uint8_t* receive_buffer, uint8_t len);

	private:

		uint8_t I2C_ADDR = 0b0001110 << 1;
};

#endif /* INC_BM1422AGMV_HAL_H_ */
