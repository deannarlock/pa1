/*
 * File:     treesum_mpi.c
 *
 * Purpose:  Use tree-structured communication to find the global sum
 *           of a random collection of ints.  This version doesn't
 *           require that comm_sz be a power of 2.
 *
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------------------------------
 * Function:
 *  global_sum
 *
 * Purpose:
 *  Implement a global sum using tree-structured communication
 *
 * Notes:
 *  1.  The return value for global sum is only valid on process 0
 */
int global_sum(int my_int /* in */, int my_rank /* in */, int comm_sz /* in */,
               MPI_Comm comm /* in */) {
  int my_sum = my_int;
  int receive_val;
  int iteration_size = 1;
  int step = 2;
  int count, included_max;
  MPI_Status status;
  while(iteration_size < comm_sz) {
    count = comm_sz / step;
    included_max = count * step - 1;
    if( (my_rank % step == iteration_size)) {
      MPI_Send(&my_sum, 1, MPI_INT, my_rank - iteration_size, my_rank, comm);
    }
    else if(my_rank % step == 0 && (my_rank <= included_max || included_max == -1)) {
      MPI_Recv(&receive_val, 1, MPI_INT, my_rank + iteration_size, my_rank + iteration_size, comm, &status);
      my_sum = my_sum + receive_val;
    }
    iteration_size = iteration_size * 2;
    step = step * 2;
  }
  
  /* Your solution */
  return my_sum;
} /* Global_sum */
