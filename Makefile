
CC=$(T) cc
EXECS=genInput merge mergeP mergeSort mergeSortPv1_omp mergeSortPv2_omp mergeSortPv1_mpi mergeSortPv1_mpi2  
MPICC?=mpicc

.PHONY: all
all: ${EXECS}

.PHONY: clean
clean:
	rm -f ${EXECS}

#### Serial builds

merge: merge.c
	cc $(addprefix -D, $(D)) merge.c -o merge

mergeSort: mergeSort.c
	cc $(addprefix -D, $(D)) mergeSort.c -o mergeSort

#### Parallel builds

mergeP: mergeP.c
	$(CC) $(addprefix -D, $(D)) -fopenmp mergeP.c -o mergeP

mergeSortPv1_omp: mergeSortPv1_omp.c
	$(CC) $(addprefix -D, $(D)) -fopenmp mergeSortPv1_omp.c -o mergeSortPv1_omp 

mergeSortPv2_omp: mergeSortPv2_omp.c
	$(CC) $(addprefix -D, $(D)) -fopenmp mergeSortPv2_omp.c -o mergeSortPv2_omp 	

mergeSortPv1_mpi: mergeSortPv1_mpi.c
	${MPICC} $(addprefix -D, $(D)) mergeSortPv1_mpi.c -o mergeSortPv1_mpi

mergeSortPv1_mpi2: mergeSortPv1_mpi2.c
	${MPICC} $(addprefix -D, $(D)) mergeSortPv1_mpi2.c -lm -o mergeSortPv1_mpi2

#### Auxiliary builds

genInput: genInput.c
	cc $(addprefix -D, $(D)) genInput.c -o genInput

