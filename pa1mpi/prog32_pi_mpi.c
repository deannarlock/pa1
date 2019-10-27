
/*
 * File:     prog32_pi_mpi.c
 *
 * Purpose:  Estimate pi using a monte carlo method
 *
 * IPP book:      Programming Assignment 3.2
 */

#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------------------------------
 * Estimate Pi in parallel using a monte carlo method
 * Only process 0 returns the correct pi estimation
 * In args:
 * 	number_of_tosses: No of tosses.
 *      my_rank: my process rank
 *      no_proc: number of processes
 *      comm: MPI communication group
 * Return: estimated pi
 */

double parallel_pi(long long int number_of_tosses, int my_rank, int no_proc,
                   MPI_Comm comm) {
  double pi_estimate = 0.0;
  double num_hits = 0.0;
  double x, y, distance_squared, sum;
  
  /* Your solution */
  
  for (int i = my_rank + 1; i <= number_of_tosses; i += no_proc) {
    x = 2 * random() / ((double)RAND_MAX) - 1.0;
    y = 2 * random() / ((double)RAND_MAX) - 1.0;

    distance_squared = x * x + y * y;
    if(distance_squared <= 1) {
      num_hits += 1.0;
    }
  }

  MPI_Reduce(&num_hits, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, comm);
  if(my_rank == 0) {
    pi_estimate = 4 * sum / ((double)number_of_tosses);
    return pi_estimate;
  }
}
