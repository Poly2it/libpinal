.POSIX:


CCFLAGS = 
CCPATHS =
CC_OPT_O = -O3
CC_OPT_LTO = -flto
CCFLAGS_FULL = ${CC_OPT_LTO} ${CC_OPT_O} ${CCPATHS} ${CCFLAGS}

LDFLAGS = 
LDPATHS =
LD_OPT_O = -O3
LD_OPT_LTO = -flto
LDFLAGS_FULL = ${LD_OPT_LTO} ${LD_OPT_O} ${LDPATHS} ${LDFLAGS}

PREFIX = /usr/local
SOURCE = src
BUILD = .build
BUILD_INCLUDE = dist/include/libpinal
BUILD_LIB = dist/lib

CC = clang
LD = ${CC}
AR = ar
CP = cp
RM = rm
TC = touch
MD = mkdir


.PHONY: all build clean install uninstall lib include

all: build

build: lib include
	${CP} ${SOURCE}/*.h ${BUILD_INCLUDE}

clean:
	${RM} ${BUILD} -rf
	${MD} ${BUILD} -p
	${TC} ${BUILD}/.gitkeep

	${RM} ${BUILD_LIB} -rf
	${MD} ${BUILD_LIB} -p
	${TC} ${BUILD_LIB}/.gitkeep

	${RM} ${BUILD_INCLUDE} -rf
	${MD} ${BUILD_INCLUDE} -p
	${TC} ${BUILD_INCLUDE}/.gitkeep

install: uninstall
	${CP} -T -r ${BUILD_INCLUDE} ${PREFIX}/include/libpinal
	${CP} -T -r ${BUILD_LIB}/libpinal.a ${PREFIX}/lib/libpinal.a

uninstall:
	${RM} -rf ${PREFIX}/include/libpinal
	${RM} -f  ${PREFIX}/lib/libpinal.a

include: \
	src/primitives.h \
	src/string.h \
	src/string_slice.h

lib: ${BUILD}/string.o ${BUILD}/string_slice.o
	${AR} \
		rcs \
		${BUILD_LIB}/libpinal.a \
		${BUILD}/string.o \
		${BUILD}/string_slice.o \

${BUILD}/string.o: ${SOURCE}/string.h
	${CC} -c ${CCFLAGS_FULL} \
		-o ${BUILD}/string.o \
		${SOURCE}/string.c \

${BUILD}/string_slice.o: ${SOURCE}/string_slice.h
	${CC} -c ${CCFLAGS_FULL} \
		-o ${BUILD}/string_slice.o \
		${SOURCE}/string_slice.c \

