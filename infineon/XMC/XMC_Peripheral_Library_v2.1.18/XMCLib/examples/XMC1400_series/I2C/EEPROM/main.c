#include <xmc_common.h>
#include <stdlib.h>

#include "eeprom.h"

#define DATA_LEN 16

int main(void)
{
  uint8_t read_data[DATA_LEN];
  uint8_t write_data[DATA_LEN];
 
  eeprom_init();

  srand(0);
  for (int i = 0; i < DATA_LEN; ++i)
  {
	  write_data[i] = rand();
  }

  eeprom_write(1, write_data, DATA_LEN);
  eeprom_read(1, read_data, DATA_LEN);

  if (memcmp(write_data, read_data, DATA_LEN) != 0)
  {
	  while(1);
  }

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {

  }
}
