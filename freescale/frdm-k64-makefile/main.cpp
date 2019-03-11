#include "FreeRTOS.h"
#include "task.h"
#include "mbed.h"

/* Prototypes for the standard FreeRTOS callback/hook functions implemented
 * within this file. The extern "C" is required to avoid name mangling
 * between C and C++ code. */
#if defined (__cplusplus)
extern "C" {
#endif

void vApplicationMallocFailedHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );

#if defined (__cplusplus)
}
#endif

static void task_body( void* params );

DigitalOut led_red(LED_RED);
DigitalOut led_blue(LED_BLUE);
DigitalOut led_green(LED_GREEN);

Serial pc(USBTX, USBRX);

int main() 
{
    vTraceEnable( TRC_INIT );

    pc.baud(9600);

    pc.printf("Hello World from FRDM-K64F board.\n");

    xTaskCreate( task_body, "T01", 256, NULL, configMAX_PRIORITIES - 1, NULL );
    
    vTraceEnable( TRC_START );

    vTaskStartScheduler();
    
    for(;;);
}

static void task_body( void* params )
{
    TickType_t xPrevRelease = xTaskGetTickCount();
    
    int sel = 0;
    
    for(;;)
    {
    	/* Leds OFF */
    	led_green = 1;
    	led_blue = 1;
    	led_red = 1;

    	switch(sel) {
    	case 0:
    		led_green = 0;
    		break;
    	case 1:
    		led_blue = 0;
    		break;
    	case 2:
    		led_red = 0;
			break;
    	}

    	sel = (sel + 1) % 3;

        vTaskDelayUntil(&xPrevRelease, 1000);
    }
    
    vTaskDelete( NULL );
}


void vApplicationMallocFailedHook( void )
{
	taskDISABLE_INTERRUPTS();
    
    led_green = 0;

	for( ;; )
	{
        led_red = 1;
        wait_ms(1000);
        led_red = 0;
        wait_ms(1000);
	}
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	taskDISABLE_INTERRUPTS();
    
	led_green = 0;

	for( ;; )
	{
        led_red = 1;
        wait_ms(500);
        led_red = 0;
        wait_ms(500);
	}
}

