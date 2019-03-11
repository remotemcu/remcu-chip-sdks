#include "main.hpp"

void taskFunction(void *params) {
    (void)params;

    PRINTF("Setup (%s)... ", __FUNCTION__);
    uint8_t counter = 0;
    PRINTF("OK\r\n");

    for (;;) {
        switch (counter % 3) {
            case 0: {
                GPIO_TogglePinsOutput(LED_RED_GPIO, (1 << LED_RED_GPIO_PIN));
            } break;
            case 1: {
                GPIO_TogglePinsOutput(LED_GREEN_GPIO, (1 << LED_GREEN_GPIO_PIN));
            } break;
            case 2: {
                GPIO_TogglePinsOutput(LED_BLUE_GPIO, (1 << LED_BLUE_GPIO_PIN));
            } break;
            default: break;
        }

        counter++;

        vTaskDelay(75);
    }
}

extern "C" int main() {
    board::initDebugConsole();
    board::initLeds();

    PRINTF("\r\nApplication started\r\n");

    PRINTF("Creating tasks... ");
    xTaskCreate(taskFunction, NULL, configMINIMAL_STACK_SIZE, NULL,
                (tskIDLE_PRIORITY + 1), NULL);
    PRINTF("OK\r\n");

    vTaskStartScheduler();
}
