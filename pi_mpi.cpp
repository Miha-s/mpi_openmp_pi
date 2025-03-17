#include <iostream>
#include <random>
#include <mpi.h>
#include <cmath>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    long long total_points;

    if (world_rank == 0) {
        if (argc != 2) {
            std::cerr << "Usage: " << argv[0] << " <num_points>" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        total_points = std::stoll(argv[1]);
    }

    MPI_Bcast(&total_points, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    long long points_per_process = total_points / world_size;

    unsigned int seed = static_cast<unsigned int>(time(NULL)) + world_rank;

    long long local_count = 0;
    for (long long i = 0; i < points_per_process; ++i) {
        double x = rand_r(&seed) / static_cast<double>(RAND_MAX);
        double y = rand_r(&seed) / static_cast<double>(RAND_MAX);
        if (x * x + y * y <= 1.0) {
            local_count++;
        }
    }

    long long global_count;
    MPI_Reduce(&local_count, &global_count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        double pi_estimate = 4.0 * static_cast<double>(global_count) / total_points;
        std::cout << "Estimated value of Pi: " << pi_estimate << std::endl;
    }

    MPI_Finalize();
    return 0;
}
