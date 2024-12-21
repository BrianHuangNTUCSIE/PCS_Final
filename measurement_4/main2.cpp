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

    int hop_count = 0;
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

        int hops = 0;
        int last_vehicle = 0;
        double last_position = 0;
        while(true){
            bool has_next = false;
            int next_index;
            int temp_index = last_vehicle + 1;
            while((temp_index < size) && (x[temp_index] - last_position <= range)){
                if(equipped[temp_index]){
                    has_next = true;
                    next_index = temp_index;
                }
                temp_index++;
            }
            if(has_next){
                hops++;
                last_vehicle = next_index;
                last_position = x[next_index];
            }
            else{
                break;
            }
        }
        
        // Safely update the total array
        #pragma omp atomic
        hop_count += hops;
    }

    // Print the results
    printf("%lf",(static_cast<double>(hop_count))/times);

    return 0;
}
