CC = gcc
FLAGS = -Wall -g 
OBJ =codecA.c codecB.c
LM = -lm

all: encode decode

encode: encode.o 
	$(CC) $(FLAGS) -o encode encode.o ./libcodecA.so $(LM)

decode: decode.o
	$(CC) $(FLAGS) -o decode decode.o ./ 

encode.o: encode.c codecA.h codecB.h
	$(CC) $(FLAGS) -c encode.c $(LM)

decode.o: decode.c codecA.h codecB.h 
	$(CC) $(FLAGS) -c decode.c $(LM)

libcodecA.so: codecA.c codecA.h
	$(CC) $(FLAGS) -shared -o $@ codecA.c
# libclassrec.so: basicClassification.o advancedClassificationRecursion.o
# 	$(CC) -shared -o libclassrec.so basicClassification.o advancedClassificationRecursion.o


libcodecB.so: codecB.c codecB.h
	$(CC) $(FLAGS) -shared -o $@ codecB.c

.PHONY: clean all

clean:
	rm -f *.o *.a *.so encode decode 

//////////////////
all: loops recursived recursives loopd mains maindloop maindrec 

loops: libclassloops.a
 
libclassloops.a: basicClassification.o advancedClassificationLoop.o
	$(AR) -rcs libclassloops.a basicClassification.o advancedClassificationLoop.o

recursives: libclassrec.a

libclassrec.a: basicClassification.o advancedClassificationRecursion.o
	$(AR) -rcs libclassrec.a basicClassification.o advancedClassificationRecursion.o

recursived: libclassrec.so

libclassrec.so: basicClassification.o advancedClassificationRecursion.o
	$(CC) -shared -o libclassrec.so basicClassification.o advancedClassificationRecursion.o


loopd: libclassloops.so

libclassloops.so: basicClassification.o advancedClassificationLoop.o
	$(CC) -shared -o libclassloops.so  basicClassification.o advancedClassificationLoop.o



mains: main.o
	$(CC) $(FLAGS) -o mains main.o libclassrec.a 

maindloop: main.o
	$(CC) $(FLAGS) -o maindloop main.o ./libclassloops.so

maindrec: main.o
	$(CC) $(FLAGS) -o maindrec main.o ./libclassrec.so

main.o: main.c NumClass.h 
	$(CC) $(FLAGS) -c main.c 

basicClassification.o: basicClassification.c NumClass.h
		$(CC) $(FLAGS) -fPIC -c basicClassification.c 

advancedClassificationLoop.o: advancedClassificationLoop.c NumClass.h
		$(CC) $(FLAGS) -fPIC -c advancedClassificationLoop.c 

advancedClassificationRecursion.o: advancedClassificationRecursion.c NumClass.h
		$(CC) $(FLAGS) -fPIC -c advancedClassificationRecursion.c 

.PHONY: clean all

clean:
	rm -f *.o *.a *.so mains maindloop maindrec
