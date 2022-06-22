#include <semaphore>
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
int in = 0, out = 0, cnt = 0;

counting_semaphore<1> exclusion(1);

item next_produced;

auto producer = []()
{
    int i = 100;
    while (true)
    {
        /* produce an item in next produced */
        while (cnt == BUFFER_SIZE)
            ; /* do nothing */
        
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, 100);
        int product = dis(gen);

        next_produced.idx = product;
        next_produced.name = "name" + to_string(product);
        
        //Entry Section
        exclusion.acquire();
        /* CS - add next_produced
        to the buffer */
        cnt++;
        buffer[in] = next_produced;
        //cout << "produce an item: " << next_produced.name << "\n";
        printf("(count: %d)(in: %d) produce an item: %s\n", cnt, in, next_produced.name.c_str());
        
        //Exit Section
        exclusion.release();
        
        in = (in + 1) % BUFFER_SIZE;
        //this_thread::sleep_for(chrono::seconds(1));
    }
};

item next_consumed;

auto consumer = []()
{
    int i = 100;
    while (true)
    {
        this_thread::sleep_for(chrono::seconds(1));
        while (cnt == 0)
            ; /* do nothing */
        
        //Entry Section
        exclusion.acquire();
        cnt--;
        //cout << "consume an item: " << next_consumed.idx << "\n";
        next_consumed = buffer[out];
        printf("(count: %d)(out: %d) consume an item: %d\n", cnt, out, next_consumed.idx);
        
        //Exit Section
        exclusion.release(); 
        
        out = (out + 1) % BUFFER_SIZE;
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