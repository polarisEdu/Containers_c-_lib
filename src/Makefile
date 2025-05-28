CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17
OS = $(shell uname)

SRCS = s21_set.cpp 
OBJS = $(SRCS:.cpp=.o)
HDRS = s21_containers.h

ifeq ($(OS),Linux)
    det_OS = -lcheck -lrt -lc -lpthread -lsubunit -lm
else
    det_OS = -lcheck -lc -lpthread -lm 
endif

all: clean s21_containers.a test

s21_containers.a: $(OBJS)
	ar rcs s21_containers.a $(OBJS)
	ranlib s21_containers.a

s21_set.o: s21_set.cpp s21_set.h s21_map.h
	$(CC) $(CFLAGS) -c s21_set.cpp -o s21_set.o

test: s21_containers.a
	$(CC) $(CFLAGS) --coverage $(OBJS) test/*.cpp -lgtest -lstdc++ -lgtest_main -lpthread -o testresult $(det_OS)
	./testresult

clang:
	clang-format -style=Google -n *.cpp *.h test/*.cpp

style:
	clang-format -style=Google -i *.cpp *.h test/*.cpp

clean:
	rm -rf testresult *.gcda *.gcno *.o *.info *.a test/*.gcno test/report test.dSYM
