

pi_open_mp: pi_open_mp.cpp
	g++ -O0 -fopenmp -o pi_open_mp pi_open_mp.cpp

pi_mpi: pi_mpi.cpp
	mpic++ -o pi_mpi pi_mpi.cpp

pi_sequential: pi_sequential.cpp
	g++ -O0 -o pi_sequential pi_sequential.cpp

run_pi_mpi: pi_mpi
	mpirun --use-hwthread-cpus -n 4 ./pi_mpi $(POINTS)

