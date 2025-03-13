
# Info
This is comparison of calculation PI using method Monte Carlo with different parallelization technologies:
 - MPI
 - OpenMP


All command to run tests are in Makefile


# MPI
installing mpi
```
sudo apt-get update
sudo apt-get install mpich
```

verifiing instalation
```
mpiexec --version
```


# Time comparison


| Number of dots | sequential (s) | OpenMP (s) | MPI (s) | Speedup OpenMP | Speedup MPI
| ----  | -----  |  ----  | ---- | ----- | ----
| 100M  | 0.93   | 0.2    | 0.67 | 4.65  | 1.39
| 500M  | 4.71   | 0.98   | 1.45 | 4.8   | 3.24
| 1000M | 9.57   | 2      | 2.45 | 4.78  | 3.9