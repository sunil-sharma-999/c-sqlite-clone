C_FLAGS=-Wall
C_FLAGS+=-Wextra
C_FLAGS+=-pedantic
C_FLAGS+=-std=c99

editor: main.c main.h
	gcc $(C_FLAGS) main.c -o db

.PHONY: mem
mem:
	gcc -g main.c -o db.out && valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-log.txt \
         ./db.out $(ARGS)

.PHONY: clean
clean:
	rm -rf *.out valgrind-log.txt


