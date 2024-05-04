test: test.o
	@echo "Linking"
	gcc $^ -o $@
test.o: test.c
	@echo "Compile test.c"
	gcc -Wall -c test.c
