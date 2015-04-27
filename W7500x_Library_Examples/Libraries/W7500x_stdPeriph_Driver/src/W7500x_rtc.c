/**
  ******************************************************************************
  * @file    W7500x_rtc.c
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
 *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//#include "W7500x_uart.h"
#include "W7500x_rtc.h"
#include "W7500x_crg.h"


/*********************************************************************//**
 * @brief		De-initializes the RTC peripheral registers to their
*                  default reset values.
 * @param[in]	RTCx	RTC peripheral selected, should be W7500_RTC
 * @return 		None
 **********************************************************************/
void RTC_DeInit(void)
{
	RTC->RTCCON     = 0x0; 
    RTC->RTCINTE    = 0x0;
    RTC->RTCINTP    = 0x0;
    RTC->RTCAMR     = 0x0;
    RTC->BCDSEC     = 0x0;
    RTC->BCDMIN     = 0x0;
    RTC->BCDHOUR    = 0x0;
    RTC->BCDDAY     = 0x0;
    RTC->BCDDATE    = 0x0;
    RTC->BCDMON     = 0x0;
    RTC->BCDYEAR    = 0x0;
    RTC->PRESEC     = 0x0;
    RTC->PREMIN     = 0x0;
    RTC->PREHOUR    = 0x0;
    RTC->PREDAY     = 0x0;
    RTC->PREDATE    = 0x0;
    RTC->PREMON     = 0x0;
    RTC->PREYEAR    = 0xFFFF;
}

/********************************************************************//**
 * @brief		Initializes the RTC peripheral.
 * @param[in]	RTCx	RTC peripheral selected, should be W7500_RTC
 * @return 		None
 *********************************************************************/
void RTC_Init (W7500_RTC_TypeDef *RTCx)
{
	/* Set up clock and power for RTC module */
	//CRGx->RTCCLK_32K = 0x1; // 32K_OSC_CLK
	//CRGx->RTC_SSR = 0x01; // 32K_OSC_CLK
	//CRG_RTC_SourceSelect(CRG_CLK_LOW);
	CRG_RTC_SourceSelect(CRG_CLK_HIGH);

	// Clear all register to be default
	RTC->RTCCON = 
	RTCx->RTCINTE = 0x00;
	RTCx->RTCINTP = 0x03;
	RTCx->RTCAMR = 0x00;
}


void RTC_ResetClockTickCounter(W7500_RTC_TypeDef *RTCx)
{
	RTCx->RTCCON = 0x2; // clear divider
}

void RTC_Cmd (W7500_RTC_TypeDef *RTCx, FunctionalState NewState)
{
	//RTCx->RTCCON = 0x1;
	if (NewState == ENABLE)
	{
		//RTCx->CCR |= RTC_CCR_CLKEN;
		RTCx->RTCCON = 0x1;
	}
	else
	{
		//RTCx->CCR &= (~RTC_CCR_CLKEN) & RTC_CCR_BITMASK;
	}
}

void RTC_CntIncrIntConfig (W7500_RTC_TypeDef *RTCx, uint32_t CntIncrIntType, \
								FunctionalState NewState)
{
}

//void RTC_AlarmIntConfig (W7500_RTC_TypeDef *RTCx, uint32_t AlarmTimeType, \
//								FunctionalState NewState)

void RTC_SetTime (W7500_RTC_TypeDef *RTCx, uint32_t Timetype, uint32_t TimeValue)
{
//	CHECK_PARAM(PARAM_RTCx(RTCx));
//	CHECK_PARAM(PARAM_RTC_TIMETYPE(Timetype));

	switch ( Timetype)
	{
	case RTC_TIMETYPE_SECOND:
//		CHECK_PARAM(TimeValue <= RTC_SECOND_MAX);

		RTCx->BCDSEC = TimeValue & RTC_SEC_MASK;
		break;

	case RTC_TIMETYPE_MINUTE:
//		CHECK_PARAM(TimeValue <= RTC_MINUTE_MAX);

		RTCx->BCDMIN = TimeValue & RTC_MIN_MASK;
		break;

	case RTC_TIMETYPE_HOUR:
//		CHECK_PARAM(TimeValue <= RTC_HOUR_MAX);

		RTCx->BCDHOUR = TimeValue & RTC_HOUR_MASK;
		break;

	case RTC_TIMETYPE_DAYOFWEEK:
//		CHECK_PARAM(TimeValue <= RTC_DAYOFWEEK_MAX);

		RTCx->BCDDAY = TimeValue & RTC_DOW_MASK;
		break;

	case RTC_TIMETYPE_DAYOFMONTH:
//		CHECK_PARAM((TimeValue <= RTC_DAYOFMONTH_MAX) \
//				&& (TimeValue >= RTC_DAYOFMONTH_MIN));

		//RTCx->DOM = TimeValue & RTC_DOM_MASK;
		RTCx->BCDDATE = TimeValue & RTC_DOM_MASK;
		break;

/* Day of Year does not exist.
	case RTC_TIMETYPE_DAYOFYEAR:
		CHECK_PARAM((TimeValue >= RTC_DAYOFYEAR_MIN) \
				&& (TimeValue <= RTC_DAYOFYEAR_MAX));

		RTCx->DOY = TimeValue & RTC_DOY_MASK;
		break;
*/

	case RTC_TIMETYPE_MONTH:
//		CHECK_PARAM((TimeValue >= RTC_MONTH_MIN) \
//				&& (TimeValue <= RTC_MONTH_MAX));

		RTCx->BCDMON = TimeValue & RTC_MONTH_MASK;
		break;

	case RTC_TIMETYPE_YEAR:
//		CHECK_PARAM(TimeValue <= RTC_YEAR_MAX);

		//RTCx->BCDYEAR = TimeValue & RTC_YEAR_MASK;
		RTCx->BCDYEAR = TimeValue;
		break;
	}
}

/*
uint32_t RTC_GetTime(W7500_RTC_TypeDef *RTCx, uint32_t Timetype)
{
	CHECK_PARAM(PARAM_RTCx(RTCx));
	CHECK_PARAM(PARAM_RTC_TIMETYPE(Timetype));

	switch (Timetype)
	{
	case RTC_TIMETYPE_HOUR:
		return (RTCx->HOUR & RTC_HOUR_MASK);
	case RTC_TIMETYPE_DAY:
		return (RTCx->DOW & RTC_DOW_MASK);
	case RTC_TIMETYPE_DATE:
		return (RTCx->DOM & RTC_DOM_MASK);
	case RTC_TIMETYPE_MONTH:
		return (RTCx->MONTH & RTC_MONTH_MASK);
	case RTC_TIMETYPE_YEAR:
		return (RTCx->YEAR & RTC_YEAR_MASK);
	default:
		return (0);
	}
}		
*/

void RTC_SetFullTime (W7500_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{

	//	CHECK_PARAM(PARAM_RTCx(RTCx));

	//RTCx->DOM = pFullTime->DOM & RTC_DOM_MASK;
	RTCx->BCDDATE = pFullTime->DOM;
	RTCx->BCDDAY = pFullTime->DOW;
	RTCx->BCDHOUR = pFullTime->HOUR;
	RTCx->BCDMIN = pFullTime->MIN;
	RTCx->BCDSEC = pFullTime->SEC;
	RTCx->BCDMON = pFullTime->MONTH;
	RTCx->BCDYEAR = pFullTime->YEAR;
}

void RTC_GetFullTime (W7500_RTC_TypeDef *RTCx, RTC_CONTIME_Type *pFullTime)
{
	//CHECK_PARAM(PARAM_RTCx(RTCx));

	pFullTime->TIME0 = RTCx->RTCTIME0;
	pFullTime->TIME1 = RTCx->RTCTIME1;
}

void RTC_SetAlarmTime (W7500_RTC_TypeDef *RTCx, uint32_t Timetype, uint32_t ALValue)
{
	//CHECK_PARAM(PARAM_RTCx(RTCx));

	switch (Timetype)
	{
	case RTC_TIMETYPE_SECOND:
//		CHECK_PARAM(ALValue <= RTC_SECOND_MAX);

		RTCx->PRESEC = ALValue & RTC_SEC_MASK;
		break;

	case RTC_TIMETYPE_MINUTE:
//		CHECK_PARAM(ALValue <= RTC_MINUTE_MAX);

		RTCx->PREMIN = ALValue & RTC_MIN_MASK;
		break;

	case RTC_TIMETYPE_HOUR:
//		CHECK_PARAM(ALValue <= RTC_HOUR_MAX);

		RTCx->PREHOUR = ALValue & RTC_HOUR_MASK;
		break;

	case RTC_TIMETYPE_DAYOFWEEK:
//		CHECK_PARAM(ALValue <= RTC_DAYOFWEEK_MAX);

		RTCx->PREDAY = ALValue & RTC_DOW_MASK;
		break;

	case RTC_TIMETYPE_DAYOFMONTH:
//		CHECK_PARAM((ALValue <= RTC_DAYOFMONTH_MAX) \
//				&& (ALValue >= RTC_DAYOFMONTH_MIN));

		RTCx->PREDATE = ALValue & RTC_DOM_MASK;
		break;

//	case RTC_TIMETYPE_DAYOFYEAR:
//		CHECK_PARAM((ALValue >= RTC_DAYOFYEAR_MIN) \
//				&& (ALValue <= RTC_DAYOFYEAR_MAX));
//
//		RTCx->ALDOY = ALValue & RTC_DOY_MASK;
//		break;

	case RTC_TIMETYPE_MONTH:
//		CHECK_PARAM((ALValue >= RTC_MONTH_MIN) \
//				&& (ALValue <= RTC_MONTH_MAX));

		RTCx->PREMON = ALValue & RTC_MONTH_MASK;
		break;

	case RTC_TIMETYPE_YEAR:
//		CHECK_PARAM(ALValue <= RTC_YEAR_MAX);

		//RTCx->PREYEAR = ALValue & RTC_YEAR_MASK;
		RTCx->PREYEAR = ALValue;
		break;
	}
}



//uint32_t RTC_GetAlarmTime (W7500_RTC_TypeDef *RTCx, uint32_t Timetype)

void RTC_SetFullAlarmTime (W7500_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{
	RTCx->PREDATE = pFullTime->DOM;
	RTCx->PREDAY = pFullTime->DOW;
	RTCx->PREHOUR = pFullTime->HOUR;
	RTCx->PREMIN = pFullTime->MIN;
	RTCx->PRESEC = pFullTime->SEC;
	RTCx->PREMON = pFullTime->MONTH;
	RTCx->PREYEAR = pFullTime->YEAR;
}

void RTC_GetFullAlarmTime (W7500_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime)
{
	pFullTime->DOM = RTCx->PREDATE;
	pFullTime->DOW = RTCx->PREDAY;
	pFullTime->HOUR = RTCx->PREHOUR;
	pFullTime->MIN = RTCx->PREMIN;
	pFullTime->SEC = RTCx->PRESEC;
	pFullTime->MONTH = RTCx->PREMON;
	pFullTime->YEAR = RTCx->PREYEAR;
}

/*
IntStatus RTC_GetIntPending (W7500_RTC_TypeDef *RTCx, uint32_t IntType)
{
	RTCx->RTCINTE = 0x00;
	RTCx->RTCINTP = 0x03;
	return ((RTCx->RTCINTP & IntType) ? SET : RESET);
}
*/

void RTC_ClearIntPending (W7500_RTC_TypeDef *RTCx, uint32_t IntType)
{
	RTCx->RTCINTP |= IntType;
}

/*
void RTC_ClearIntPending (W7500_RTC_TypeDef *RTCx)
{
	RTCx->RTCINTP = 0x03;
}
*/

void RTC_EnableInt (W7500_RTC_TypeDef *RTCx, FunctionalState NewState)
{
	if (NewState == ENABLE)
	{
		//RTCx->RTCINTE = 0x00000001;
		RTCx->RTCINTE = 0x01;
	}
	else
	{
		//RTCx->RTCINTE = 0x00000000;
		RTCx->RTCINTE = 0x00;
	}
}


//void RTC_WriteGPREG (W7500_RTC_TypeDef *RTCx, uint8_t Channel, uint32_t Value)
//uint32_t RTC_ReadGPREG (W7500_RTC_TypeDef *RTCx, uint8_t Channel)


void rtc_wrw( uint32_t addr, uint32_t data)
{
	*(volatile uint32_t *)(addr) = data;
}

uint32_t rtc_rdw( uint32_t addr)
{
	return *(volatile uint32_t *)(addr);
}

