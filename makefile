

# The pre-processor and compiler options.
MY_CFLAGS = -std=c++11 -Wl,--no-as-needed -I ~/local/boost_install_1_55_0/include -I.

COMPFLAG = -c

# The linker options.
MY_LIBS   = -std=c++11 -Wl,--no-as-needed -L ~/local/boost_install_1_55_0/lib -lboost_system -lpthread

CXX=g++

proj2_bfs: main.o AdjacencyList.o AdjacencyMatrix.o GraphVertex.o
	$(CXX) -o proj2_bfs $(MY_LIBS) main.o AdjacencyList.o AdjacencyMatrix.o GraphVertex.o

main.o: main.cpp
	$(CXX) $(COMPFLAG) $(MY_CFLAGS) main.cpp -lpthread

AdjacencyList.o: AdjacencyList.cpp
	$(CXX) $(COMPFLAG) $(MY_CFLAGS) AdjacencyList.cpp

AdjancencyMatrix.o: AdjacencyMatrix.cpp
	$(CXX) $(COMPFLAG) $(MY_CFLAGS) AdjacencyMatrix.cpp

GraphVertex.o: GraphVertex.cpp
	$(CXX) $(COMPFLAG) $(MY_CFLAGS) GraphVertex.cpp

clean: 
	rm -rf *.o ./proj2_bfs

