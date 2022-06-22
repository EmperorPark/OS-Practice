class Banker_sItem
{
private:
    int A;
    int B;
    int C;
public:
    int getA();
    int getB();
    int getC();
    void setItem(int A, int B, int C);
    void setA(int val);
    void setB(int val);
    void setC(int val);
    Banker_sItem(/* args */);
    Banker_sItem(int A, int B, int C);
    ~Banker_sItem();
    Banker_sItem operator+(Banker_sItem &rval);
    Banker_sItem operator-(Banker_sItem &rval);
    Banker_sItem operator+=(Banker_sItem &rval);
    Banker_sItem operator-=(Banker_sItem &rval);
    
    bool operator<=(Banker_sItem &rval);
    bool operator>=(Banker_sItem &rval);
    bool operator<(Banker_sItem &rval);
    bool operator>(Banker_sItem &rval);

    void operator=(Banker_sItem ref);
};


