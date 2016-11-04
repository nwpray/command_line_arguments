all: setporter tester
	
setporter: portsetter.cpp
	g++-5 -std=c++11 portsetter.cpp -o setport
	
tester: tests.cpp
	g++-5 -std=c++11 tests.cpp -o tests
	
clean:
	rm setport tests