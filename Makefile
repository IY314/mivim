CC := cc
WFLAGS := -Wall -Werror -Wextra
IFLAGS := -Iinclude
OFLAGS := -c ${WFLAGS} ${IFLAGS}
LFLAGS := -lncurses
CFLAGS := -o bin/myvi ${LFLAGS} ${WFLAGS}

.PHONY: all link clean

all: link

clean:
	@rm -rf bin

bin:
	@mkdir -p bin

link: bin/main.o bin/dynstr.o
	${CC} bin/*.o ${CFLAGS}

bin/%.o: src/%.c bin
	${CC} $< -o $@ ${OFLAGS}
