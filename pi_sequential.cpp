#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_points>" << std::endl;
        return 1;
    }

    int num_points = std::atoi(argv[1]);
    if (num_points <= 0) {
        std::cerr << "Number of points must be a positive integer." << std::endl;
        return 1;
    }

    unsigned int seed = 3;
    int inside_circle = 0;

    for (int i = 0; i < num_points; ++i) {
        double x = rand_r(&seed)/ double(RAND_MAX);
        double y = rand_r(&seed) / double(RAND_MAX);
        if (x * x + y * y <= 1.0) {
            ++inside_circle;
        }
    }

    double pi_estimate = 4.0 * inside_circle / num_points;
    std::cout << "Estimated value of Pi: " << pi_estimate << std::endl;

    return 0;
}