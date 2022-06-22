#include <semaphore>
#include <thread>
#include <iostream>

using namespace std;

counting_semaphore<1> rw_mutex(1), r_mutex(1);
int read_count = 0;
int line_count = 0;

auto threadA = []()
{
    int i = 100;
    while (i--) {

        rw_mutex.acquire();
        
        /* CS – writing is performed*/
        //cout << ++line_count << ". " << "A" << "\n";
        printf("%d. A\n", ++line_count);

        rw_mutex.release();
    }
};

auto threadB = []()
{
    int i = 100;
    while (i--) {
        r_mutex.acquire();
        read_count++;
        if (read_count == 1)
            rw_mutex.acquire();
        r_mutex.release();

        /* CS – reading is performed */
        //cout << ++line_count << ". " << "B" << "\n";
        printf("%d. B\n", ++line_count);
        printf("%d. %d명이 읽는 중\n", line_count, read_count);
        

        r_mutex.acquire();
        read_count--;
        if (read_count == 0)
            rw_mutex.release();
        r_mutex.release();
    }
};

auto threadC = []()
{
    int i = 100;
    while (i--) {
        r_mutex.acquire();
        read_count++;
        if (read_count == 1)
            rw_mutex.acquire();
        r_mutex.release();
        
        /* CS – reading is performed */
        //cout << ++line_count << ". " << "C" << "\n";
        printf("%d. C\n", ++line_count);
        printf("%d. %d명이 읽는 중\n", line_count, read_count);

        r_mutex.acquire();
        read_count--;
        if (read_count == 0)
            rw_mutex.release();
        r_mutex.release();
    }
};

int main(int argc, char* argv[], char* envp[])
{

    std::thread thread3 = std::thread(threadC);
    std::thread thread1 = std::thread(threadA);
    std::thread thread2 = std::thread(threadB);

    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}