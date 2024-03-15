# ifndef _INTERRUPT_H_
# define _INTERRUPT_H_
# include "main.h"
# include "stdbool.h"
struct keys{
	unsigned judge_status;
	bool key_status;
	bool signal_flag;
	unsigned int key_time;				// To record the pused time
	bool long_flag;
};
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif
