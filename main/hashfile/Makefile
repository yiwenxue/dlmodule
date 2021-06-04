CC= clang

SSL_LIBS=-L/usr/local/lib -lssl -lcrypto
SSL_FLAGS=-I/usr/local/include

CFLAGS= -fPIC -I../ -I../../libyiwen/include/ ${SSL_FLAGS}
LIBS=  -ldl -L../../lib/ -lyiwen ${SSL_LIBS}
LDFLAGS= -shared ${LIBS}

module=hashfile

all:${module}.ko
	@echo Module $< generated! 

${module}.ko:${module}.o
	${CC} ${LDFLAGS} $< -o $@
	@echo "remove trash"
	@rm $<

${module}.o:${module}.c
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean: 
	rm -rf ${module}.ko
