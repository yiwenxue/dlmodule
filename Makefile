CC= clang
CFLAGS= -I/include/ -fPIC
LIBS= -ldl
LDFLAGS= ${LIBS} -shared

incyiwen= ./include/log.h\
		  ./include/list.h\
		  ./include/module.h\
		  ./include/command.h\
		  ./include/yiwen_int.h\
		  ./include/yiwen_fatal.h\
		  ./include/yiwen_string.h\
		  ./include/yiwen_memview.h\
		  ./include/yiwen_pcolor.h

srcyiwen= ./src/module.c \
		  ./src/command.c \
		  ./src/yiwen_int.c

tempyiwen= $(patsubst %.c, %.o, $(srcyiwen))

library=lib/libyiwen.so
all: details library

details: 
	@echo "CFLAGS:  " ${CFLAGS}
	@echo "LDFLAGS: " ${LDFLAGS}

library: ${tempyiwen}
	mkdir -p lib 
	${CC} ${LDFLAGS} ${tempyiwen} -o lib/libyiwen.so
	rm ${tempyiwen}

module.o: ${incyiwen} ./src/module.c
	${CC} ${CFLAGS} -c ./src/module.c -o ./src/module.o

command.o: ${incyiwen} ./src/command.c
	${CC} ${CFLAGS} -c ./src/command.c -o ./src/command.o

yiwen_int.o: ${incyiwen} ./src/yiwen_int.c
	${CC} ${CFLAGS} -c ./src/yiwen_int.c -o ./src/yiwen_int.o

.PHONY: clean

clean: 
	rm -rf lib/libyiwen.so ${tempyiwen}
