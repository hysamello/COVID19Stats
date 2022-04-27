all: clean
	gcc -o project -flto -march=native -pipe -faggressive-loop-optimizations \
		main.c \
		src/date.c \
		src/patient.c \
		src/utils.c \
		src/region.c \
		ADT/ADTList/listArrayList.c \
		ADT/ADTList/listElem.c \
		ADT/ADTMap/mapArrayList.c \
		ADT/ADTMap/mapElem.c \
		ADT/ADTMap/keyString.c \
		src/commandHandler.c -lm

debug: clean
	gcc -o project -g -flto -march=native -pipe -faggressive-loop-optimizations \
		main.c \
		src/date.c \
		src/patient.c \
		src/utils.c \
		src/region.c \
		ADT/ADTList/listArrayList.c \
		ADT/ADTList/listElem.c \
		ADT/ADTMap/mapArrayList.c \
		ADT/ADTMap/mapElem.c \
		ADT/ADTMap/keyString.c \
		src/commandHandler.c -lm

clean:
	rm -rf project
