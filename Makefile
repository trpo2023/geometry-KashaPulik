all: circle
circle: circle.c
	gcc -Wall -Werror -o circle circle.c
clean:
	rm circle
normal:
	./circle normal.txt
circleError:
	./circle circleError.txt
bracketError1:
	./circle bracketError1.txt
bracketError2:
	./circle bracketError2.txt
doubleError:
	./circle doubleError.txt
unt:
	./circle unt.txt
commaError:
	./circle commaError.txt
inputError1:
	./circle
inputError2:
	./circle unt.txt commaError.txt
readError:
	./circle something
lineError:
	./circle lineError.txt