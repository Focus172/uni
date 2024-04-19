PROG = social-network
# DEST = zig-out/bin/${PROG}
DEST = ${PROG}
# SRCS = src/social_network.c src/network.c src/user.c
SRCS = social_network.c network.c user.c

CFLAGS := -O2 -Wall -Wextra
CXX := g++

all: ${PROG}

OBJS := ${SRCS:.c=.o}

${PROG}: ${OBJS}
	${CXX} ${CFLAGS} $^ -o ${DEST}

clean:
	rm -f ${DEST} ${OBJS}

# -include ${OBJS:.o=.d}

.PHONY: all clean install uninstall
