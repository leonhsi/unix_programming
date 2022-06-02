all: logger.so logger 

.PHONY: logger.so logger

logger.so:
	gcc -Wall -shared -o logger.so -fPIC logger.c -D_GNU_SOURCE -ldl

logger:
	gcc -Wall hw2.c -o logger
