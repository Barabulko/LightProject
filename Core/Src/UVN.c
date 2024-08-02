#ifndef __UVN
#include "UVN.h"
#endif
#include "main.h"
#include "string.h"
#include "usbd_cdc.h"
/*битовые маски для передачи полжений реле*/

#define R1_MASK (uint8_t) 0b00000001
#define R2_MASK (uint8_t) 0b00000010
#define R3_MASK (uint8_t) 0b00000100
#define R4_MASK (uint8_t) 0b00001000
#define R5_MASK (uint8_t) 0b00010000
#define  MASK_RELAY_1 (uint8_t) 0b00000001
#define  MASK_RELAY_2 (uint8_t) 0b00001110
#define  MASK_RELAY_3 (uint8_t) 0b01110000
/*значения неисправностей в байте*/

#define L_DEFAULT 		(uint8_t)0xFF	//исходное состояние без неисправностей (для любых неисправнстей)

#define BREAK 			(uint8_t)0x00	//разрыв линии связи

#define IN_PULL_UP 		(uint8_t)2	//подтяжка входа к 1
#define IN_PULL_DOWN 	(uint8_t)6	//подтяжка входа к 0
#define IN_PULL_X 		(uint8_t)10	//подтяжка входа к пустму контакту


#define OUT_PULL_UP 	(uint8_t)16	//подтяжка выхода к 1
#define OUT_PULL_DOWN 	(uint8_t)48	//подтяжка выхода к 0
#define OUT_PULL_X 		(uint8_t)80	//подтяжка выхода к пустму контакту

/**/

#define SELFTEST 		(uint8_t)0x01	//самопроверка
#define SET_DEFAULT 	(uint8_t)0x02	//установка линий в исходное
#define SET_L_CONFIG 	(uint8_t)0x04	//установка будущего значения линий
#define SET_FAULT 		(uint8_t)0x05	//внесение неисправности
#define SET_FUTURE		(uint8_t)0x7F	//внесение неисправности из FUTURE_RELAY
#define SET_NET 		(uint8_t)0x06	//установка айпи
#define GET_CONFIG 		(uint8_t)0x07	//запрос на получение текущих остояний реле
#define SET_FLAG 		(uint8_t)0x08	//установка флага автоматической записи состояний реле в flash
#define RESET_FLAG 		(uint8_t)0x09	//сброс флага автоматической записи состояний реле в flash
#define SAVE_CONF		(uint8_t)0xA0	//ручное сохранение состояний реле в flash
#define TEST			(uint8_t)0xAE	//для тестов

#define REL_BR 			(uint8_t)0x01	//реле на разрыв линии
#define REL_PUO 		(uint8_t)0x02	//реле на подтяжку 1/0 к выходу
#define REL_PUI 		(uint8_t)0x03	//реле на подтяжку 1/0 к входу
#define REL_PXO 		(uint8_t)0x04	//реле на подтяжку внеш/пуст к выходу
#define REL_PXI 		(uint8_t)0x05	//реле на подтяжку внеш/пуст к входу

#define RL_RESET 		(uint8_t)0x00	//установка реле
#define RL_SET 			(uint8_t)0x01	//сброс реле
#define RL_SAVE 		(uint8_t)0x02	//сохранение сост

#define CONF_DEF 		(uint8_t)0x13 	//ответ на проверку состояния(исходное)
#define CONF_NDEF 		(uint8_t)0x10 	//ответ на проверку состояния(нет исходного)
#define UVN_ER 				(uint8_t)0x00 	//ответ на проверку состояния(нет исходного)
uint8_t CURRENT_RELAY[64];
static uint8_t UVN_FLAGS=0;//первый бит usb, второй внешний сигналб, третий флеш, четвертый установки будующиъх состояний
static uint8_t N_FUTURE = 0;
static uint8_t INDX_FUTURE = 0;
static uint8_t * FUTURE_RELAY=CURRENT_RELAY;
static uint8_t USBF=0;

static uint8_t * o_buf;

uint8_t * GetFUTURE_RELAY()
{
	return FUTURE_RELAY;
}

uint8_t GetUVN_FLAGS()
{
	return UVN_FLAGS;
}

uint8_t GetINDX_FUTURE()
{
	return INDX_FUTURE;
}

uint8_t IncINDX_FUTURE()
{
	if(INDX_FUTURE<N_FUTURE-1)
	{
		INDX_FUTURE++;
		return 1;
	}
	else
	{
		INDX_FUTURE=0;
		return  UVN_ER;
	}
}

void SetUSBF()
{

	UVN_FLAGS^=0b00000001;
}

void SetExSigF()
{

	UVN_FLAGS^=0b00000010;

}

void SetFlashF()
{

	UVN_FLAGS^=0b00000100;
}

void SetFutrConfF()
{

	UVN_FLAGS^=0b00001000;
}

uint8_t GetUSBF()
{
	return UVN_FLAGS;
}

void SetBuf(uint8_t * Buf)
{
	o_buf=Buf;
}

uint8_t * GetBuf()
{
	return o_buf;
}

void uvnInit(uint8_t * conf_rel)
{
	u8_t CURRENT_RELAY_START[65];
	for(uint8_t i = 0;i<64;i++)
	{
	CURRENT_RELAY[i]=0;
	CURRENT_RELAY_START[i+1]=conf_rel[i];
	}
	set_fault(CURRENT_RELAY_START);
}
static void set_PortD(u8_t relay, u8_t conf)
{
	switch(relay)
			{

				case 1:

					if(conf == RL_SET)
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);//set - З// Ж/С прав.
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
					}
					else if(conf == RL_RESET)
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
					}
					break;

				case 2:

					if(conf == RL_SET)
					{
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);//set К/С прав.
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
					}
					else if(conf == RL_RESET)
					{
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
					}
					break;

				case 3:
					if(conf == RL_SET)
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);//set Ж/С прав.
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

					}
					else if(conf == RL_RESET)
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
					}

					break;
				case 4:
					if(conf == RL_SET)
					{
						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);//set К/П лев.
						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);

					}
					else if(conf ==RL_RESET)
					{
						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
					}
					break;
			}
}

static void SyncREG(u8_t iR)
{
	switch(iR)
	{
	case 1:
		    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
			break;

	case 2:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
			HAL_Delay(1);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
			break;
	}
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
}

static void relay_protect()
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	for(uint8_t i = 1; i<2; i++)
	{
		SyncREG(i);
	}
}

static void set_Reg(u8_t* M)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	u8_t k = 1; //счетчик реле от 1 до 4 на каждой микросхеме
	u8_t x =0; // счетчик микросхем
	for(int i=1;i<65;i++)
	{
		if ( (M[i] & R1_MASK) != (CURRENT_RELAY[i-1] & R1_MASK))
		{
		switch( M[i] & R1_MASK )
		{
			case 0:
				set_PortD(k, RL_RESET);
				break;

			default:
				 set_PortD(k, RL_SET);
				 break;
		}
		 if(k<4)	{k++;}
		 else 		{k=1; x++; SyncREG(x);}
		}
		else
		{
			set_PortD(k, RL_SAVE);
			if		(k<4)	 {k++;}
			else 	{k=1; x++; SyncREG(x);}
		}

		if ( (M[i] & R2_MASK) != (CURRENT_RELAY[i-1] & R2_MASK))
		{

		switch(M[i] & R2_MASK)
		{
			case 0:
				set_PortD(k, RL_SET);
				if	 (k<4)	 {k++;}
				else {k=1; x++; SyncREG(x);}
				break;
			default:
				set_PortD(k, RL_RESET);
				if	 (k<4)	 {k++;}
				else {k=1; x++; SyncREG(x);}
				break;
		  }
		}
		else
		{
			set_PortD(k, RL_SAVE);
			if	 (k<4)	 {k++;}
			else {k=1; x++; SyncREG(x);}
		}
		if ( (M[i] & R3_MASK) != (CURRENT_RELAY[i-1] & R3_MASK))
				{

			switch(M[i] & R3_MASK)
			{
				case 0:
					set_PortD(k, RL_SET);
					if	 (k<4)	 {k++;}
					else {k=1; x++; SyncREG(x);}
					break;
				default:
					set_PortD(k, RL_RESET);
					if	 (k<4)	 {k++;}
					else {k=1; x++; SyncREG(x);}
					break;
			  }
			}
			else
			{
				set_PortD(k, RL_SAVE);
				if	 (k<4)	 {k++;}
				else {k=1; x++; SyncREG(x);}
			}
		if ( (M[i] & R4_MASK) != (CURRENT_RELAY[i-1] & R4_MASK))
		{

		switch( M[i] & R4_MASK)// к/п - лев.
		{
			case 0:
				set_PortD(k, RL_SET);
				if	 (k<4)	 {k++;}
				else {k=1; x++; SyncREG(x);}
				break;
			 default:
				set_PortD(k, RL_RESET);
				if	 (k<4)	 {k++;}
				else {k=1; x++; SyncREG(x);}
				break;
		}
		}
		else
		{
			set_PortD(k, RL_SAVE);
			if	 (k<4)	 {k++;}
			else {k=1; x++; SyncREG(x);}

		}
		if ( (M[i] & R5_MASK) != (CURRENT_RELAY[i-1] & R5_MASK))
		{
		switch( M[i] & R5_MASK)
		{
			case 0:
				set_PortD(k, RL_SET);
				if	 (k<4)	 {k++;}
				else {k=1; x++; SyncREG(x);}
				break;
			 default:
				set_PortD(k, RL_RESET);
				if	 (k<4)	 {k++;}
				else {k=1; x++; SyncREG(x);}
				break;
		}
		}
		else
		{
			set_PortD(k, RL_SAVE);
			if	 (k<4)	 {k++;}
			else {k=1; x++; SyncREG(x);}
		}

		CURRENT_RELAY[i-1]=M[i];

	}
	//SyncREG(2);//ЭТО КОСТЫЛЬ
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_Delay(5);
	relay_protect();
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
}


static void relay_save()
{
	if(UVN_FLAGS & 0b00000100)
	{
		uint64_t r[8];
		memcpy(r,CURRENT_RELAY,sizeof(CURRENT_RELAY));
		FlashWrite_RELAY(r);
	}
}


void set_fault (u8_t* M)

{
	set_Reg(M);
	relay_save();
}



void SetNET(u8_t* GtB)
{
	u8_t n_ip [4]= {GtB[1],GtB[2],GtB[3],GtB[4]};
	u8_t n_mask [4]= {GtB[5],GtB[6],GtB[7],GtB[8]};
	u8_t n_gw [4]=  {GtB[9],GtB[10],GtB[11],GtB[12]};
	u8_t n_port [4] = {GtB[14],GtB[13]};
	uint32_t ip = *(uint32_t*) n_ip;
	uint32_t mask = *(uint32_t*) n_mask;
	uint32_t gw = *(uint32_t*) n_gw;
	uint16_t port = *(uint16_t*) n_port;
	FlashWrite_NET(ip ,mask, gw, port);
}

void SaveFuture(uint8_t * M)
{
			for(uint8_t i = 0; i<64; i++)
			{
				*(FUTURE_RELAY + i + INDX_FUTURE*64) = M[i];
			}
				INDX_FUTURE++;
				if(N_FUTURE==INDX_FUTURE)
					{
					SetFutrConfF();
					INDX_FUTURE=0;
			}
}

void * GetFunc(u8_t* GtB)
{

	switch(GtB[0])
	{
	case SELFTEST:
		  if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_11) == 1)
		  {
			  return (void*) CONF_DEF;
		  }
		  else
		  {
			  return (void*) CONF_NDEF;
		  }
		break;

	case SET_DEFAULT:
		flash_erase();
		__NVIC_SystemReset();
		break;

	case SET_L_CONFIG:
		N_FUTURE = GtB[1];
		if(N_FUTURE>0 && N_FUTURE<32)
			{
			FUTURE_RELAY = malloc(N_FUTURE*64);
			SetFutrConfF();
		}
		else{return  UVN_ER;}
		break;

	case SET_FAULT:
		if(GtB[1]<SET_FUTURE)
		{
			for(int i = 0;i<64;i++)
			{
			CURRENT_RELAY[i]=FUTURE_RELAY[i];
			}
			set_fault(CURRENT_RELAY);
		}
		else
		{
			set_fault(GtB);
		}
		break;

	case SET_NET:
		SetNET(GtB);
		__NVIC_SystemReset();
		break;

	case GET_CONFIG:
		return (void*)CURRENT_RELAY;
		break;

	case SET_FLAG:
		UVN_FLAGS =  UVN_FLAGS & 0b11111011;
		SetFlashF();
		break;

	case RESET_FLAG:
		UVN_FLAGS =  UVN_FLAGS & 0b11111011;
		break;

	case SAVE_CONF:
		UVN_FLAGS =  UVN_FLAGS & 0b11111011;
		SetFlashF();
		relay_save();
		SetFlashF();
		break;

	case TEST:
		return (void*)TEST;
		break;
	}
	return (void*)1;
}


