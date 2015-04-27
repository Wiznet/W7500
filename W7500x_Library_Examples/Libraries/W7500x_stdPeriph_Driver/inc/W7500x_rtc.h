/*
 *********************************************************************
 * @file
 * @version
 * @author
 * @data
 * @brief
 *********************************************************************
 * @attention
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __W7500X_RTC_H
#define __W7500X_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

// register address
#define RTC_SYS_BASE	0x4000E000
#define RTC_CON			0x4000E000
#define RTC_INTE		0x4000E004
#define RTC_INTP		0x4000E008
#define RTC_AMR			0x4000E00C

#define RTC_BCDSEC		0x4000E010
#define RTC_BCDMIN		0x4000E014
#define RTC_BCDHOUR		0x4000E018
#define RTC_BCDDAY		0x4000E01C

#define RTC_BCDDATE		0x4000E020
#define RTC_BCDMON		0x4000E024
#define RTC_BCDYEAR		0x4000E028
#define RTC_PRESEC		0x4000E02C

#define RTC_PREMIN		0x4000E030
#define RTC_PREHOUR		0x4000E034
#define RTC_PREDAY		0x4000E038
#define RTC_PREDATE		0x4000E03C

#define RTC_PREMON		0x4000E040
#define RTC_PREYEAR		0x4000E044

#define RTC_TIME0		0x4000E048
#define RTC_TIME1		0x4000E04C

#define RTCCLK_SEL		0x41001130
#define RTCCLK_PRE		0x41001134
#define RTCCLK_32K		0x4100113C



/* Includes ------------------------------------------------------------------*/
#include "W7500x.h"


/*@}*/ /* end of group CMSDK_Peripherals */
typedef struct
{
  __IO uint32_t RTCCON;     
  __IO uint32_t RTCINTE;   
  __IO uint32_t RTCINTP;
  __IO uint32_t RTCAMR;
  __IO uint32_t BCDSEC;
  __IO uint32_t BCDMIN;
  __IO uint32_t BCDHOUR;
  __IO uint32_t BCDDAY;
  __IO uint32_t BCDDATE;
  __IO uint32_t BCDMON;
  __IO uint32_t BCDYEAR;
  __IO uint32_t PRESEC;
  __IO uint32_t PREMIN;
  __IO uint32_t PREHOUR;
  __IO uint32_t PREDAY;
  __IO uint32_t PREDATE;
  __IO uint32_t PREMON;
  __IO uint32_t PREYEAR;
  __I  uint32_t RTCTIME0;
  __I  uint32_t RTCTIME1;
} RTC_TypeDef;


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/

#define W7500_APB_BASE          (0x40000000UL)
#define W7500_RTC_BASE          (W7500_APB_BASE + 0x0000E000UL)

#define RTC                     ((RTC_TypeDef *) W7500_RTC_BASE)


/* ----------------------- BIT DEFINITIONS ----------------------------------- */
#define RTC_CON_CLKEN_Disable       (0x00ul << 0)
#define RTC_CON_CLKEN_Enable        (0x01ul << 0)
#define RTC_CON_DIVRST_Reset        (0x01ul << 1)
#define RTC_CON_INTEN_Disable       (0x00ul << 5)
#define RTC_CON_INTEN_Enable        (0x01ul << 5)
/**********************************************************************
* RTCINTP register definitions
**********************************************************************/
/** RTCINTP register mask */
#define RTC_INTP_BITMASK		((0x00000003))
/** Bit inform the source interrupt is counter increment*/
#define RTC_INTP_CIF			((1<<0))
/** Bit inform the source interrupt is alarm match*/
#define RTC_INTP_ALF			((1<<1))


/**********************************************************************
* Time Counter Group and Alarm register group
**********************************************************************/
/** SEC register mask */
#define RTC_SEC_MASK			(0x0000007F)
/** MIN register mask */
#define RTC_MIN_MASK			(0x0000007F)
/** HOUR register mask */
#define RTC_HOUR_MASK			(0x0000002F)
/** DOM register mask */
#define RTC_DOM_MASK			(0x0000002F)
/** DOW register mask */
#define RTC_DOW_MASK			(0x00000007)
/** DOY register mask */
#define RTC_DOY_MASK			(0x000001FF)
/** MONTH register mask */
#define RTC_MONTH_MASK			(0x0000001F)
/** YEAR register mask */
#define RTC_YEAR_MASK			(0x0000FFFF)

#define RTC_SECOND_MAX		59 /*!< Maximum value of second */
#define RTC_MINUTE_MAX		59 /*!< Maximum value of minute*/
#define RTC_HOUR_MAX		23 /*!< Maximum value of hour*/
#define RTC_MONTH_MIN		1 /*!< Minimum value of month*/
#define RTC_MONTH_MAX		12 /*!< Maximum value of month*/
#define RTC_DAYOFMONTH_MIN 	1 /*!< Minimum value of day of month*/
#define RTC_DAYOFMONTH_MAX 	31 /*!< Maximum value of day of month*/
#define RTC_DAYOFWEEK_MIN	1 /*!< Minimum value of day of week*/
#define RTC_DAYOFWEEK_MAX	7 /*!< Maximum value of day of week*/
#define RTC_YEAR_MAX		4095 /*!< Maximum value of year*/


/* ---------------- CHECK PARAMETER DEFINITIONS ---------------------------- */
/** Macro to determine if it is valid RTC peripheral */
#define PARAM_RTCx(x)	(((uint32_t *)x)==((uint32_t *)W7500_RTC0))



/** @brief Time structure definitions for easy manipulate the data */
//typedef struct {
//	uint32_t SEC; 		/*!< Seconds Register */
//	uint32_t MIN; 		/*!< Minutes Register */
//	uint32_t HOUR; 		/*!< Hours Register */
//	uint32_t DOM;		/*!< Day of Month Register */
//	uint32_t DOW; 		/*!< Day of Week Register */
//	uint32_t DOY; 		/*!< Day of Year Register */
//	uint32_t MONTH; 	/*!< Months Register */
//	uint32_t YEAR; 		/*!< Years Register */
//} RTC_TIME_Type;
typedef struct {
	uint32_t SEC; 		/*!< Seconds Register */
	uint32_t MIN; 		/*!< Minutes Register */
	uint32_t HOUR; 		/*!< Hours Register */
	uint32_t DOM;		/*!< Day of Month Register */
	uint32_t DOW; 		/*!< Day of Week Register */
	uint32_t MONTH; 	/*!< Months Register */
	uint32_t YEAR; 		/*!< Years Register */
} RTC_TIME_Type;


/** @brief Consolidated RTC Time */
typedef struct {
	uint32_t TIME0; 	/*!< RTCTIME0 Register */
	uint32_t TIME1; 	/*!< RTCTIME1 Register */
} RTC_CONTIME_Type;


/** @brief RTC time type option */
typedef enum {
	RTC_TIMETYPE_SECOND = 0, 		/*!< Second */
	RTC_TIMETYPE_MINUTE = 1, 		/*!< Month */
	RTC_TIMETYPE_HOUR = 2, 			/*!< Hour */
	RTC_TIMETYPE_DAYOFWEEK = 3, 	/*!< Day of week */
	RTC_TIMETYPE_DAYOFMONTH = 4, 	/*!< Day of month */
	RTC_TIMETYPE_MONTH = 5, 		/*!< Month */
	RTC_TIMETYPE_YEAR = 6 			/*!< Year */
} RTC_TIMETYPE_Num;


/** @brief RTC interrupt source */
typedef enum {
	RTC_INT_COUNTER_INCREASE = RTC_INTP_CIF, 	/*!<  Counter Increment Interrupt */
	RTC_INT_ALARM = RTC_INTP_ALF 				/*!< The alarm interrupt */
} RTC_INT_OPT;


/* Public Functions ----------------------------------------------------------- */
/** @defgroup RTC_Public_Functions RTC Public Functions
 * @{
 */

void RTC_Init (W7500_RTC_TypeDef *RTCx);
void RTC_DeInit(W7500_RTC_TypeDef *RTCx);
void RTC_ResetClockTickCounter(W7500_RTC_TypeDef *RTCx);
void RTC_Cmd (W7500_RTC_TypeDef *RTCx, FunctionalState NewState);
void RTC_CntIncrIntConfig (W7500_RTC_TypeDef *RTCx, uint32_t CntIncrIntType, \
								FunctionalState NewState);
void RTC_AlarmIntConfig (W7500_RTC_TypeDef *RTCx, uint32_t AlarmTimeType, \
								FunctionalState NewState);
void RTC_SetTime (W7500_RTC_TypeDef *RTCx, uint32_t Timetype, uint32_t TimeValue);
uint32_t RTC_GetTime(W7500_RTC_TypeDef *RTCx, uint32_t Timetype);
void RTC_SetFullTime (W7500_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);
void RTC_GetFullTime (W7500_RTC_TypeDef *RTCx, RTC_CONTIME_Type *pFullTime);
void RTC_SetAlarmTime (W7500_RTC_TypeDef *RTCx, uint32_t Timetype, uint32_t ALValue);
uint32_t RTC_GetAlarmTime (W7500_RTC_TypeDef *RTCx, uint32_t Timetype);
void RTC_SetFullAlarmTime (W7500_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);
void RTC_GetFullAlarmTime (W7500_RTC_TypeDef *RTCx, RTC_TIME_Type *pFullTime);
//IntStatus RTC_GetIntPending (W7500_RTC_TypeDef *RTCx, uint32_t IntType);
void RTC_ClearIntPending (W7500_RTC_TypeDef *RTCx, uint32_t IntType);
void RTC_EnableInt (W7500_RTC_TypeDef *RTCx, FunctionalState NewState);
void RTC_WriteGPREG (W7500_RTC_TypeDef *RTCx, uint8_t Channel, uint32_t Value);
uint32_t RTC_ReadGPREG (W7500_RTC_TypeDef *RTCx, uint8_t Channel);

void rtc_wrw( uint32_t addr, uint32_t data);
uint32_t rtc_rdw( uint32_t addr);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*  __W7500X_RTC_H */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */



