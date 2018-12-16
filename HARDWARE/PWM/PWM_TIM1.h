/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __PWM_TIM1_H
#define __PWM_TIM1_H

#include <gd32f1x0.h>
#include "sys.h"

#define PWM_NUM 200  // 48MHz/ 200 = 240KHz


#ifndef YANMING1

#define SET_BOOST_REG(X)		(TIMER1->CHCC1 = (X))
#define SET_BUCK_REG(X)		(TIMER1->CHCC2 = (X))

#define	FZDY_EN()				GPIO_SetBits(GPIOF,GPIO_PIN_0)
#define	FZDY_DISABLE()	GPIO_ResetBits(GPIOF,GPIO_PIN_0)

#define PWM_OUT_EN()			GPIO_SetBits(GPIOB,GPIO_PIN_1)
#define PWM_OUT_DISABLE() GPIO_ResetBits(GPIOB,GPIO_PIN_1)

#else
#define SET_BOOST_REG(X)		(TIMER3->CHCC1 = (X))
#define SET_BUCK_REG(X)		(TIMER3->CHCC2 = (X))

#if defined SCREEN_SSD1306
#define	FZDY_EN()				GPIO_SetBits(GPIOB,GPIO_PIN_3)
#define	FZDY_DISABLE()	        GPIO_ResetBits(GPIOB,GPIO_PIN_3)
#elif defined SCREEN_SH1107
#define	FZDY_EN()				GPIO_SetBits(GPIOB,GPIO_PIN_3)
#define	FZDY_DISABLE()
#endif


#define PWM_OUT_EN()			GPIO_SetBits(GPIOA,GPIO_PIN_15)
#define PWM_OUT_DISABLE() GPIO_ResetBits(GPIOA,GPIO_PIN_15)
#endif

#define PWM_SET_TO_ZERO()			Set_PWM_HL(PWM_NUM + 20,0)
#define BYPASS_PWM_MODE()			Set_PWM_HL(0,PWM_NUM + 20)



void PWM_Configuration(void);

void Set_PWM_HL(uint32_t PWM_H, uint32_t PWM_L);


#endif
