
CC = gcc

C_FLAGS = -I remcu_include/
L_FLAGS = -lremcu -L./ -Wl,-rpath=./

all:
	$(CC) DAC_DMA_Escalator.c $(C_FLAGS) $(L_FLAGS) -o DAC_DMA_Escalator
	$(CC) TriangleWave.c $(C_FLAGS) $(L_FLAGS) -o TriangleWave