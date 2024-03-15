# include "interrupt.h"
struct keys key[4] = {0, 0, 0};																			// Initialize the struct
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)					// HAL_TIM_PeriodElapsedCallback
{
	if(htim->Instance == TIM3){																				// To figure out wheather it's from TIM3
			key[0].key_status = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);			// Read the value of GPIOB_0
		  key[1].key_status = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);	
	    key[2].key_status = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);	
			key[3].key_status = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);	
		
		  for(int i=0; i < 4; i++)																			// The code here is meant to eliminate the false movement
		{
				switch(key[i].judge_status){
				
					case 0:{
						if(key[i].key_status == 0)															 // we have four keys to detect
							key[i].judge_status = 1;															 // if we figure that the key is clicked
					}
					break;
					case 1:{
						if(key[i].key_status == 0)															 // we have four keys to detect
							key[i].judge_status = 2;															 // if we figure that the key is clicked
							key[i].signal_flag = 1;
					}
					break;
					case 2:{
						if(key[i].key_status == 1)
						{
							key[i].judge_status = 0;															 // rejudge the clicked circumstance
						}
				}
					break;
		}
	}
}
	}
