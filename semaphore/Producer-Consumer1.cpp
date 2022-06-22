#include <thread>
#include <iostream>
#include <random>

using namespace std;

#define BUFFER_SIZE 100

typedef struct {
    int idx;
    string name;
} item;

item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int cnt = 0;

item next_produced;

auto producer = []()
{
    int i = 100;
    while (true)
    {
        /* produce an item in next produced */
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, 100);
        int product = dis(gen);

        next_produced.idx = product;
        next_produced.name = "name" + to_string(product);

        while ((in + 1) % BUFFER_SIZE == BUFFER_SIZE)
            ; /* do nothing */
        
        cnt++;
        buffer[in] = next_produced;
        in = (in + 1) % BUFFER_SIZE;
        //cout << "produce an item: " << next_produced.name << "\n";
        printf("(count: %d) produce an item: %d\n", cnt, next_produced.idx);
    }
};

item next_consumed;

auto consumer = []()
{
    int i = 100;
    while (true)
    {
        while (in == out)
            ; /* do nothing */
        next_consumed = buffer[out];
        /* consume the item in next consumed */
        //cout << "consume an item: " << next_consumed.idx << "\n";
        printf("(count: %d) consume an item: %d\n", cnt, next_consumed.idx);
        out = (out + 1) % BUFFER_SIZE;
        cnt--;
        this_thread::sleep_for(chrono::seconds(1));
        
    }
};

int main(int argc, char* argv[], char* envp[])
{
    std::thread thread1 = std::thread(producer);
    std::thread thread2 = std::thread(consumer);

    thread1.join();
    thread2.join();

    return 0;
}