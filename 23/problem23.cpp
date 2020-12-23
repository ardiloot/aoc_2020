#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cstring>

constexpr int N = 1000000;
std::array<int, N> buffers[2];

int get_dest_cup(const std::array<int, N>& arr) {
    const int cur_cup = arr[0];
    for (int i = cur_cup - 1; i >= std::max(1, cur_cup - 4); i--) {
        if (i == arr[1] || i == arr[2] || i == arr[3])
            continue;
        return i;
    }
    
    for (int i = N; i >= N - 4; i--) {
        if (i == arr[1] || i == arr[2] || i == arr[3])
            continue;
        return i;
    }   
    throw std::runtime_error("");
}

int main() {
    const std::vector<int> input_cups {6, 8, 5, 9, 7, 4, 2, 1, 3};
    for (int i = 0; i < N; i++)
        buffers[0][i] = i < input_cups.size() ?input_cups[i] : i + 1;

    int buf_ix = 0;
    for (int it = 0; it < 10000000; it++) {
        if (it % 10000 == 0)
            std::cout << it << std::endl;
        const auto& cups = buffers[buf_ix];
        const int cur_cup = cups[0];
        const int dest_cup = get_dest_cup(cups);
        const int dest_cup_ix = std::find(&cups[0], &cups[0] + N, dest_cup) - cups.begin();
      
        auto& tmp = buffers[(buf_ix + 1) % 2];
        {
            int index = 0;
            memcpy(&tmp[index], &cups[4], (dest_cup_ix - 3) * 4);
            index += dest_cup_ix - 3;
            tmp[index] = cups[1];
            tmp[index + 1] = cups[2];
            tmp[index + 2] = cups[3];
            index += 3;
            memcpy(&tmp[index], &cups[dest_cup_ix + 1], (N - dest_cup_ix - 1) * 4);
            index += N - dest_cup_ix - 1;
            tmp[index] = cups[0];
        }
        buf_ix = (buf_ix + 1) % 2;
    }
    
    {
        const auto& cups = buffers[buf_ix];
        const int ix = std::find(cups.begin(), cups.end(), 1) - cups.begin();
        std::cout << cups[ix + 1] << " " << cups[ix + 2] << std::endl; 
    }
    return 0;
}
