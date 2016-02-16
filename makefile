all:
	g++ Tests.cpp LinkedListImpl.cpp  LinkedList.cpp -std=c++11 -lgtest_main -lgtest -pthread -o LinkedList_Test.out
clean:
	rm -rf LinkedList_Test.out
	rm -rf *.gcno *.gcda
