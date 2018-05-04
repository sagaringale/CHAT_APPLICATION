CC = gcc
PARAMS = -lpthread
FILE = whatsapp.c
OBJFILE = whatsapp.o

whatsapp : ${OBJFILE}
	${CC} -o $@ ${OBJFILE} ${PARAMS}

whatsapp.o : 
	${CC} -c ${FILE} ${PARAMS}

clean:
	rm -rf *.o


