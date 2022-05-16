CC= gcc
fast = -Ofast
debug = -g -fsanitize=address
thread = -pthread 
CPP=g++ -std=c++17

all: cod_benchmark_test.cpp lshensemble_benchmark_test.cpp bootstrap.cpp lshensemble.cpp  utils.cpp ./minhash/minhash.cpp ./minhash/fnv.cpp probability.cpp lshforest.cpp lsharray.cpp linearscan_benchmark_test.cpp accuracy_benchmark_test.cpp
	$(CPP) $(fast) -fopenmp -o cod_benchmark_test cod_benchmark_test.cpp lshensemble_benchmark_test.cpp bootstrap.cpp lshensemble.cpp  utils.cpp ./minhash/minhash.cpp ./minhash/fnv.cpp probability.cpp lshforest.cpp lsharray.cpp linearscan_benchmark_test.cpp accuracy_benchmark_test.cpp 

# cod_benchmark_test.o: cod_benchmark_test.cpp
# 	$(CPP) -c  cod_benchmark_test.cpp

# utils.o: utils.cpp utils.hpp
# 	$(CPP) -c  utils.cpp

# lshensemble.o: lshensemble.cpp lshensemble.hpp 
# 	$(CPP) -c  lshensemble.cpp

# lshensemble_benchmark_test.o: lshensemble_benchmark_test.cpp lshensemble_benchmark_test.hpp
# 	$(CPP) -c  lshensemble_benchmark_test.cpp

# minhash.o: ./LSH/minhash.cpp ./LSH/minhash.hpp
# 	$(CPP) -c  ./LSH/minhash.cpp 

# xxhash.o: ./LSH/xxHash/xxhash.c ./LSH/xxHash/xxhash.h
# 	$(CC) -c  ./LSH/xxHash/xxhash.c

# lshforest.o: lshforest.cpp lshforest.hpp
# 	$(CPP) -c  lshforest.cpp

# probability.o: probability.cpp probability.hpp
# 	$(CPP) -c  probability.cpp

# bootstrap.o: bootstrap.cpp bootstrap.hpp
# 	$(CPP) -c  bootstrap.cpp

clean:
	rm -f cod_benchmark_test cod_benchmark_test.o minhash.o xxhash.o lsh.o lshensemble.o lshensemble_benchmark_test.o utils.o probability.o lshforest.o bootstrap.o
