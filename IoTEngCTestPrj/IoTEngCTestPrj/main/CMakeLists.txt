idf_component_register(
                    SRCS main.c gpio/led.c test/comtest.c com/encdec.c
                    INCLUDE_DIRS "." gpio test com)
