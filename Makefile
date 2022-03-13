CC := cc
WFLAGS := -Wall -Werror -Wextra
IFLAGS := -Iinclude -Ilib/dynstr/include
OFLAGS := -c ${WFLAGS} ${IFLAGS}
LFLAGS := -Llib/dynstr/bin -lncurses -ldynstr
CFLAGS := -o bin/mivim ${LFLAGS} ${WFLAGS}

.PHONY: all link dynstr clean

all: link

dynstr: lib/dynstr
	cd $< && ${MAKE}

clean: lib/dynstr
	@rm -rf bin
	@cd $< && ${MAKE} clean

bin:
	@mkdir -p bin

link: bin/main.o bin/display.o dynstr
	${CC} bin/*.o ${CFLAGS}

bin/%.o: src/%.c bin
	${CC} $< -o $@ ${OFLAGS}
