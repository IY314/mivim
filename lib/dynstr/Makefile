CC := cc
WFLAGS := -Wall -Werror -Wextra
IFLAGS := -Iinclude
OFLAGS := -c ${WFLAGS} ${IFLAGS}

.PHONY: all compile clean

all: compile

compile: bin/dynstr.o
	${AR} rcs bin/libdynstr.a $^

bin/%.o: src/%.c bin
	${CC} $< -o $@ ${OFLAGS}

bin:
	@mkdir -p bin

clean:
	@rm -rf bin
