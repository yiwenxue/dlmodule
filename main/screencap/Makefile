CC= clang
CFLAGS= -fPIC -I../ -I../../libyiwen/include/ `pkgconf --cflags cairo`
LIBS=  -ldl -lcairo -lX11 -L../../lib/ -lyiwen `pkgconf --libs cairo`
LDFLAGS= -shared ${LIBS}

module=screencap

all:${module}.ko
	@echo Module $< generated! 

${module}.ko:${module}.o
	${CC} ${LDFLAGS} $< -o $@
	@ echo "remove trash"
	@ rm $<

${module}.o:${module}.c
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean: 
	rm -rf ${module}.ko
