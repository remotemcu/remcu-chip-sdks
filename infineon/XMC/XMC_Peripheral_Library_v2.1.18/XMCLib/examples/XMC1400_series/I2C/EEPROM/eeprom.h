#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void eeprom_init(void);

void eeprom_write(uint16_t address, uint8_t *data, uint32_t size);

void eeprom_read(uint16_t address, uint8_t *data, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif
