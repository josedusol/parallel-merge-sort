
BIN=build
CC=$(T) cc
EXECS=genInput merge mergeP mergeSort mergeSortPv1_omp mergeSortPv2_omp mergeSortPv1_mpi mergeSortPv1_mpi2  
MPICC?=mpicc

.PHONY: all
all: ${EXECS}

.PHONY: clean
clean:
	rm -f build/*

#### Serial builds

merge: merge.c
	cc $(addprefix -D, $(D)) merge.c -o $(BIN)/merge

mergeSort: mergeSort.c
	cc $(addprefix -D, $(D)) mergeSort.c -o $(BIN)/mergeSort

#### Parallel builds

mergeP: mergeP.c
	$(CC) $(addprefix -D, $(D)) -fopenmp mergeP.c -o $(BIN)/mergeP

mergeSortPv1_omp: mergeSortPv1_omp.c
	$(CC) $(addprefix -D, $(D)) -fopenmp mergeSortPv1_omp.c -o $(BIN)/mergeSortPv1_omp 

mergeSortPv2_omp: mergeSortPv2_omp.c
	$(CC) $(addprefix -D, $(D)) -fopenmp mergeSortPv2_omp.c -o $(BIN)/mergeSortPv2_omp 	

mergeSortPv1_mpi: mergeSortPv1_mpi.c
	${MPICC} $(addprefix -D, $(D)) mergeSortPv1_mpi.c -o $(BIN)/mergeSortPv1_mpi

mergeSortPv1_mpi2: mergeSortPv1_mpi2.c
	${MPICC} $(addprefix -D, $(D)) mergeSortPv1_mpi2.c -lm -o $(BIN)/mergeSortPv1_mpi2

#### Auxiliary builds

genInput: genInput.c
	cc $(addprefix -D, $(D)) genInput.c -o $(BIN)/genInput

