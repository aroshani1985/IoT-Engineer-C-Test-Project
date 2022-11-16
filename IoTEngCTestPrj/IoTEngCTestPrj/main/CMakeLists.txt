idf_component_register(
                    SRCS
                    	main.c
                    	gpio/led.c
                    	test/comtest.c
                    	com/encdec.c
                    	com/pktformat.c
                    	com/pktreceive.c
                    	com/cmdhandler.c
                    	com/pktsend.c
                    INCLUDE_DIRS "." gpio test com)
