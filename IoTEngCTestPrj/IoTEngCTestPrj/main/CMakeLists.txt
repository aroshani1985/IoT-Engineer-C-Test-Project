idf_component_register(
                    SRCS main.c gpio/led.c test/comtest.c com/encdec.c com/pktformat.c
                    INCLUDE_DIRS "." gpio test com)
