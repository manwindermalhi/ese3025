#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#define Red_Led_GPIO_PORT_NUM                   0
#define Red_Led_GPIO_BIT_NUM                   22
#define Blue_Led_GPIO_PORT_NUM                  3
#define Blue_Led_GPIO_BIT_NUM                  26
#define Green_Led_GPIO_PORT_NUM                 3
#define Green_Led_GPIO_BIT_NUM                  25

void Delay_time()
   {
   	int i;
   	for(i=0;i<=4500000;i++);
   }

static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();


	Board_LED_Set(0, false);
}


static void vLEDTask1(void *pvParameters)
{

		while(1)
		    {

		    	Chip_GPIO_WriteDirBit(LPC_GPIO, Red_Led_GPIO_PORT_NUM, Red_Led_GPIO_BIT_NUM, 1);

		    	Delay_time();
		    	Chip_GPIO_WriteDirBit(LPC_GPIO, Red_Led_GPIO_PORT_NUM, Red_Led_GPIO_BIT_NUM,0);
		    	Chip_GPIO_WriteDirBit(LPC_GPIO, Green_Led_GPIO_PORT_NUM, Green_Led_GPIO_BIT_NUM,1);

		    	Delay_time();
		    	Chip_GPIO_WriteDirBit(LPC_GPIO, Green_Led_GPIO_PORT_NUM, Green_Led_GPIO_BIT_NUM,0);
		    	Chip_GPIO_WriteDirBit(LPC_GPIO, Blue_Led_GPIO_PORT_NUM, Blue_Led_GPIO_BIT_NUM,1);
		    	Delay_time();
		    	Chip_GPIO_WriteDirBit(LPC_GPIO, Blue_Led_GPIO_PORT_NUM, Blue_Led_GPIO_BIT_NUM, 0);
		    }

}




/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	prvSetupHardware();

	xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);


	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
