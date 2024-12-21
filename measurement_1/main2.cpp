#include <cstdio>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <tuple>
#include <random>
#include <omp.h>  // Include OpenMP header

using namespace std;
#define MAX 10000


// Function to generate an arithmetic sequence with a difference of 26
void generate_sequence(vector<double> &x, double diff) {
    double start = 0;
    while(start < MAX){
        x.push_back(start);
        start += diff;
    }
}

// Function to print a sequence
void print_sequence(vector<double> &x) {
    int size = x.size();
    printf("id  position\n");
    for (int i = 0; i < size; i++) {
        printf("%2d  %lf\n", i, x[i]);
    }
}

int main(int argc, char* argv[]) {
    // Default values for parameters
    double range;    // Transmission range
    double mu;       // Default mu value
    double diff;     // Default diff value
    int times;

    // Check if enough arguments are provided
    if (argc == 5) {
        // Parse command-line arguments
        range = atof(argv[1]); // Convert first argument to double
        mu = atof(argv[2]);    // Convert second argument to double
        diff = atof(argv[3]);  // Convert third argument to double
        times = atoi(argv[4]);
    } else {
        printf("Usage: %s <range> <mu> <diff> <times>\n", argv[0]);
        return 1; // Exit with error code
    }

    // Variables
    vector<double> x;
    int size;

    // Generate the sequence and nodes
    generate_sequence(x, diff);
    size = x.size();

    random_device rd;
    mt19937 gen(rd());  // Mersenne Twister generator
    uniform_real_distribution<> dis(0.0, 1.0);  // Uniform distribution between 0.0 and 1.0
    vector<int> total(size, 0);

    // Run experiments in parallel using OpenMP
    #pragma omp parallel for
    for (int i = 0; i < times; i++) {
        vector<bool> equipped(size, false);
        for (int j = 0; j < size; j++) {
            double random_prob = dis(gen);  // Generate random number between 0 and 1
            
            if (random_prob < mu) {
                equipped[j] = true;
            } else {
                equipped[j] = false;
            }
        }

        int last_id = 0;
        int index = 0;
        while(x[index] - x[last_id] <= range){
            if(equipped[index]){
                last_id = index;
            }
            index++;
        }

        #pragma omp atomic
        total[last_id] += 1;
    }
    total[0] = 0;

    // Print the results
    for (int i = 0; i < size; i++) {
        printf("%lf %lf\n", x[i], (static_cast<double>(total[i])) / times);
    }

    return 0;
}
