#include <cstdio>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <tuple>

using namespace std;
#define SIZE 700
#define MAX 10000


// Variables
int K;           // number of vehicles
double range;    // transmission range R
double mu;       // penetration rate
double diff;     // distance between two vehicles (uniform distribution)
vector<double> x;
vector<int> node;
vector<int> cell;
vector<int> x_bar;
vector<int> x_under_bar;


double p_node_map[SIZE+10][SIZE+10];
double p_end_map[SIZE+10][SIZE+10];
double p_hop_map[SIZE+10][SIZE+10][SIZE+10];

void generate_sequence() {
    double start = 0;
    while(start < MAX){
        x.push_back(start);
        start += diff;
    }
}
void initialize_map(){
    for(int i = 0; i <= SIZE; i++){
        for(int j = 0; j <= SIZE; j++){
            p_node_map[i][j] = -1;
            p_end_map[i][j] = -1;
        }
    }
    for(int i = 0; i <= SIZE; i++){
        for(int j = 0; j <= SIZE; j++){
            for(int k = 0; k <= SIZE; k++){
                p_hop_map[i][j][k] = -1;
            }
        }
    }
}
// Function to find nodes and cells
void find_node() {
    node.push_back(0);
    double previous_node = 0;
    int previous_vehicle_id = 0;
    double previous_vehicle = 0;
    int count = 1;

    // We only consider a continuous traffic stream
    int size = x.size();
    for (int i = 0; i < size; i++) {
        int current = x[i];
        if ((current - previous_node) > range) {
            node.push_back(previous_vehicle_id);
            previous_node = previous_vehicle;
            count++;
        }
        previous_vehicle = current;
        previous_vehicle_id = i;
        cell.push_back(count);
    }
    cell[0] = 0;
}

void find_bar(){
    int size = x.size();
    for(int i = 0;i < size; i++){
        int temp = i;
        while(temp > 0 && (x[i] - x[temp-1] <= range)){
            temp--;
        }
        x_under_bar.push_back(temp);

        temp = i;
        while(temp < size-1 && (x[temp+1] - x[i] <= range)){
            temp++;
        }
        x_bar.push_back(temp);
    }
}

// Function to print a sequence
void print_sequence() {
    int size = x.size();
    printf("id cell   position\n");
    for (int i = 0; i < size; i++) {
        printf("%2d %4d   %lf\n", i, cell[i], x[i]);
    }
    //
    printf("\n\n");
    printf("nodes:\n");
    size = node.size();
    for(int i = 0; i < size; i++){
        printf("%d ", node[i]);
    }

    //
    printf("\n\n");
    printf("bar:\n");
    size = x_bar.size();
    for(int i = 0; i < size; i++){
        printf("%d ", x_bar[i]);
    }

    //
    printf("\n\n");
    printf("under bar:\n");
    size = x_under_bar.size();
    for(int i = 0; i < size; i++){
        printf("%d ", x_under_bar[i]);
    }

    printf("\n");



}
double p_node(int k, int h);
double p_hop(int k, int l, int h);
double p_end(int k, int h);

double p_node(int k, int h){
    if(p_node_map[k][h] != -1){
        return p_node_map[k][h];
    }
    double total;
    if(k == 0 && h == 0){
        total = 1;
    }
    else if(h < cell[k] || h > 2 * cell[k] - 1){
        total = 0;
    }
    else{
        total = 0;
        for(int j = x_under_bar[k]; j <= k - 1; j++){
            total += p_hop(j, k, h);
        }
    }
    p_node_map[k][h] = total;
    return total;
}
double p_end(int k, int h){
    if(p_end_map[k][h] != -1){
        return p_end_map[k][h];
    }
    double total;
    if(k < 0 || h < 0){
        printf("error end! k = %d h = %d\n",k, h);
        exit(-1);
    }
    total = p_node(k, h);
    for(int l = k + 1; l <= x_bar[k]; l++){
        total -= p_hop(k, l, h + 1);
    }
    p_end_map[k][h] = total;
    return total;
}
double p_hop(int k, int l, int h){
    if(p_hop_map[k][l][h] != -1){
        return p_hop_map[k][l][h];
    }
    double total;
    if(k < x_under_bar[l] || l > x_bar[k]){
        total = 0;
    }
    else if(cell[l] == 1 && k == 0 && h == 1){
        total = mu;
        for(int i = 0; i < node[1] - l; i++){
            total *= (1 - mu);
        }
    }
    else if(h < cell[l] || h > 2 * cell[l] - 1){
        total = 0;
    }
    else if(h - 1 < cell[k] || h - 1 > 2 * cell[k] - 1){
        total = 0;
    }
    else if(cell[l] == 1 && k != 0){
        total = 0;
    }
    else{
        total = p_node(k, h - 1);
        for(int j = x_under_bar[l]; j <= k-1; j++){
            total -= p_hop(j, k, h - 1);
        }
        total *= mu;
        for(int i = 0; i < x_bar[k] - l; i++){
            total *= (1 - mu);
        }
    }
    //printf("p_hop(%d, %d, %d) = %lf\n", k, l, h, total);
    p_hop_map[k][l][h] = total;
    return total;
}
double function_1(int k){
    double total = 0;
    for(int h = cell[k]; h <= 2 * cell[k] - 1; h++){
        total += p_end(k,h);
    }
    return total;
}
double function_2(int k){
    double total = 0;
    for(int i = k; i <= K; i++){
        total += function_1(i);
    }
    return total;
}
double function_3(int h){
    double total = 0;
    for(int k = 1; k <= K; k++){
        total += p_end(k, h);
    }
    return total;
}
double function_4(){
    double total = 0;
    for(int h = 1; h <= K; h++){
        total += h * function_3(h);
    }
    return total;
}
double function_5(){
    double total = 0;
    for(int k = 1; k <= K; k++){
        total += x[k] * function_1(k);
    }
    return total;
}
double function_6(int k){
    if(cell[k] == 1 || cell[k] == 0){
        return 1;
    }
    return function_2(x_under_bar[k]);
}
int main(int argc, char* argv[]) {
    // Check if enough arguments are provided
    if (argc == 4) {
        range = std::atof(argv[1]);
        mu = std::atof(argv[2]);
        diff = std::atof(argv[3]);
    }
    else{
        printf("Usage: %s <range> <mu> <diff>\n", argv[0]);
        return 1; // Exit with error code
    }

    if((MAX / diff) >= SIZE){
        printf("diff too small\n");
        return 1;
    }

    // Generate the sequence and nodes
    generate_sequence();
    find_node();
    find_bar();
    initialize_map();
    K = x.size();

    for(int i = 0; i < K; i++){
        printf("%lf %lf\n", x[i] ,function_2(i));
    }

    return 0;
}
