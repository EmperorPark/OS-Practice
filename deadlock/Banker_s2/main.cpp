/*
5
0 1 0
3 0 2
3 0 2
2 1 1
0 0 2

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

2 3 0

4
0 2 0

*/
#include<iostream>
#include<cstring>
#include "Banker_sItem.h"

int numOfP = 0;
Banker_sItem allocation[1001];
Banker_sItem need[1001];
Banker_sItem max[1001];
Banker_sItem available;
int arrivedProcess;
Banker_sItem arrivedResource;

bool checkSafety();
void allocateAdditionalResource();

int main(int argc, char* argv[], char* envp[]) {


    /**
     * 
     * 입력
     * 
     **/
    int a, b, c;
    // 프로세스 개수 입력
    std::cin >> numOfP;
    // 프로세스에 현재 할당된 자원 입력(A:0, B:1, C:2)(allocation)
    for(int i = 0; i < numOfP; i++) {
        std::cin >> a >> b >> c;
        allocation[i].setItem(a, b, c);
    }

    // 프로세스가 처리되는 자원 입력(A:0, B:1, C:2)(max)
    for(int i = 0; i < numOfP; i++) {
        std::cin >> a >> b >> c;
        max[i].setItem(a, b, c);
    }

    // 현재 가용 자원 입력(available)
    std::cin >> a >> b >> c;
    available.setItem(a, b, c);

    // 추가자원을 요구하는 프로세스
    std::cin >> arrivedProcess;

    // 프로세스가 요구하는 추가 자원(A:0, B:1, C:2)
    std::cin >> a >> b >> c;
    arrivedResource.setItem(a, b, c);

    /**
     * 
     * 처리
     * 
     **/

    //기본 상태 확인
    std::cout << "===기본 상태 확인===\n";
    checkSafety();
    std::cout << "===================\n\n";

    //자원 요청
    std::cout << ">>>>>자원 요청>>>>>>\n";
    allocateAdditionalResource();
    std::cout << "===================\n";

    return 0;
}


bool checkSafety() {

    Banker_sItem avail = available;
    int solved[1001] = {0,}; // 모두 실패로 가정


    // 프로세스가 처리되기 위해 추가로 필요한 자원 연산(A:0, B:1, C:2)(need)
    for(int i = 0; i < numOfP; i++) {
        need[i] = max[i] - allocation[i];
    }

    for(int i = 0; i < numOfP; i++) {
        
        if(solved[i] == 1 ) continue;

        // need보다 available이 크거나 같으면 해결가능(A,B,C 모두 충족해야함)
        if(need[i] <= avail) {
            std::cout << "[P" << i << "처리]";
            solved[i] = 1;
            avail += allocation[i];
            i = -1; // 프로세스가 처리가 가능하면 처음부터 다시 확인
        }
    }
    std::cout << "\n";


    // 처리 안되는 프로세스가 하나라도 존재한다면 불안정 상태임
    int result = 1;
    for(int i = 0; i < numOfP; i++) {
        result = result && solved[i];
    }

    std::string rtnStr;

    rtnStr = result ? "해결 가능" : "해결 불가(불안정 상태)";
    
    std::cout << rtnStr << "\n";

    return result;
}

void allocateAdditionalResource() {
    std::cout << "요청 프로세스: [P" << arrivedProcess << "]\n";
    std::cout << "요청 자원: [A: " << arrivedResource.getA() << "], [B: " << arrivedResource.getB() << "], [C: " << arrivedResource.getC() << "]\n";

    // 요구하는 자원을 할당한다고 가정
    allocation[arrivedProcess] += arrivedResource;
    available -= arrivedResource;


    int check;
    if(available.getA() < 0 || available.getB() < 0 || available.getC() < 0) {
        std::cout << "해결불가(가용자원 초과)\n" ;
        check = 0;
    } else {
        check = checkSafety();
    }

    std::string rtnStr;

    rtnStr = check ? "자원 요청 수락" : "자원 요청 거부";
    
    std::cout << rtnStr << "\n";

    return;
}