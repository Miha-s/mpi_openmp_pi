#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <num_points>" << std::endl;
        return 1;
    }

    long num_points = std::stol(argv[1]);
    long points_in_circle = 0;

    #pragma omp parallel num_threads(4)
    {
        unsigned int seed = time(NULL) + omp_get_thread_num();
        long local_points_in_circle = 0;

        #pragma omp for
        for (long i = 0; i < num_points; ++i) {
            double x = rand_r(&seed) / (double)RAND_MAX;
            double y = rand_r(&seed) / (double)RAND_MAX;
            if (x * x + y * y <= 1.0) {
                local_points_in_circle++;
            }
        }

        #pragma omp atomic
        points_in_circle += local_points_in_circle;
    }

    double pi_estimate = 4.0 * points_in_circle / num_points;
    std::cout << "Estimated value of Pi: " << pi_estimate << std::endl;
    return 0;
}
