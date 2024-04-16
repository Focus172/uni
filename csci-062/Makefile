PROG = social-network
DEST = zig-out/bin/${PROG}
SRCS = src/social_network.c src/network.c src/user.c

CFLAGS := -O2 -Wall -Wextra
CXX := zig c++

all: ${PROG}

OBJS := ${SRCS:.c=.o}

${PROG}: ${OBJS}
	mkdir -p zig-out/bin/
	${CXX} ${CFLAGS} $^ -o ${DEST}

clean:
	rm -f ${DEST} ${OBJS} ${OBJS:.o=.d}

-include ${OBJS:.o=.d}

.PHONY: all clean install uninstall
