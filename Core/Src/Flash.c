#include "Flash.h"

uint32_t FlashRead(uint32_t addr)
{
return *(__IO uint32_t*)addr;
}

uint64_t FlashRead64(uint32_t addr)
{
return *(__IO uint32_t*)addr;
}

void FlashWrite_NET(uint32_t *ip, uint32_t *mask, uint32_t *gw, uint16_t *port)
{
	uint32_t relay32[16];
	uint64_t * relay64;
	for(uint8_t i = 0;i<16;i++)
	{
		relay32[i] = FlashRead(FLASH_RELAY+(i*4));
	}
	relay64 = & relay32;
	__disable_irq();
	HAL_FLASH_Unlock();

	FLASH_PageErase((__IO uint32_t*)FLASH_NET_DETAILS);

	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->CR &= ~FLASH_CR_PER;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_NET_DETAILS, ip);

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_NET_DETAILS+4, mask);

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_NET_DETAILS+8, gw);

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, FLASH_NET_DETAILS+12, port);

	for(uint8_t i = 0;i<8;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, FLASH_RELAY+(i*8), relay64[i]);
	}
	HAL_FLASH_Lock();

	__enable_irq();
}

void FlashWrite_RELAY(uint64_t * data)
{
	uint32_t ip = FlashRead(FLASH_NET_DETAILS);
	uint32_t mask = FlashRead(FLASH_NET_DETAILS+4);
	uint32_t gw = FlashRead(FLASH_NET_DETAILS+8);
	uint16_t port = FlashRead(FLASH_NET_DETAILS+12);

	__disable_irq();
	HAL_FLASH_Unlock();

	FLASH_PageErase((__IO uint32_t*)FLASH_NET_DETAILS);

	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->CR &= ~FLASH_CR_PER;

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_NET_DETAILS, ip);

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_NET_DETAILS+4, mask);

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_NET_DETAILS+8, gw);

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, FLASH_NET_DETAILS+12, port);

	for(uint8_t i = 0;i<8;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, FLASH_RELAY+(i*8), data[i]);
	}

	HAL_FLASH_Lock();
	__enable_irq();
}

void flash_erase()
{
	__disable_irq();
	HAL_FLASH_Unlock();
	FLASH_PageErase((__IO uint32_t*)FLASH_NET_DETAILS);
	while((FLASH->SR & FLASH_SR_BSY) != 0);
	FLASH->CR &= ~FLASH_CR_PER;
	HAL_FLASH_Lock();
	__enable_irq();
}
