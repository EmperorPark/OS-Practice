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
counting_semaphore<BUFFER_SIZE> producer_semaphore(BUFFER_SIZE);
counting_semaphore<BUFFER_SIZE> consumer_semaphore(0);

item next_produced;

auto producer = []()
{
    int i = 100;
    while (true)
    {
        //this_thread::sleep_for(chrono::seconds(1));
        
        // while (count == BUFFER_SIZE)
        //     ; /* do nothing */
        producer_semaphore.acquire();

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
        /* produce an item in next produced */
        buffer[in] = next_produced;
        in = (in + 1) % BUFFER_SIZE;
        //cout << "produce an item: " << next_produced.name << "\n";
        printf("(count: %d) produce an item: %s\n", cnt, next_produced.name.c_str());
        //Exit Section
        exclusion.release();
        consumer_semaphore.release();

        //this_thread::sleep_for(chrono::milliseconds(1000));
    }
};

item next_consumed;

auto consumer = []()
{
    int i = 100;
    while (true)
    {
        // while (count == 0)
        //     ; /* do nothing */
        consumer_semaphore.acquire();

        next_consumed = buffer[out];
        //Entry Section
        exclusion.acquire();
        /* CS - add next_produced
        to the buffer */
        cnt--;
        //cout << "consume an item: " << next_consumed.idx << "\n";
        printf("(count: %d) consume an item: %d\n", cnt, next_consumed.idx);
        out = (out + 1) % BUFFER_SIZE;
        //Exit Section
        exclusion.release();
        
        producer_semaphore.release();
        this_thread::sleep_for(chrono::milliseconds(1000));
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