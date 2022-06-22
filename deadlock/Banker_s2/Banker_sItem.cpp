#include "Banker_sItem.h"

Banker_sItem::Banker_sItem(/* args */)
{
}

Banker_sItem::Banker_sItem(int A, int B, int C)
{
    this->setItem(A, B, C);
}

Banker_sItem::~Banker_sItem()
{
}

int Banker_sItem::getA() {
    return this->A;
}

int Banker_sItem::getB() {
    return this->B;
}

int Banker_sItem::getC() {
    return this->C;
}

void Banker_sItem::setItem(int A, int B, int C) {
    this->A = A;
    this->B = B;
    this->C = C;

    return;
}

void Banker_sItem::setA(int val){
    this->A = val;

    return;
}

void Banker_sItem::setB(int val){
    this->B = val;

    return;
}

void Banker_sItem::setC(int val){
    this->C = val;

    return;
}

Banker_sItem Banker_sItem::operator+(Banker_sItem &rval){
    return Banker_sItem(this->A + rval.getA(), this->B + rval.getB(), this->C + rval.getC());
}

Banker_sItem Banker_sItem::operator+=(Banker_sItem &rval){
    this->A += rval.getA();
    this->B += rval.getB();
    this->C += rval.getC();

    return *this;
}

Banker_sItem Banker_sItem::operator-(Banker_sItem &rval){
    return Banker_sItem(this->A - rval.getA(), this->B - rval.getB(), this->C - rval.getC());
}

Banker_sItem Banker_sItem::operator-=(Banker_sItem &rval){
    this->A -= rval.getA();
    this->B -= rval.getB();
    this->C -= rval.getC();

    return *this;
}


bool Banker_sItem::operator<=(Banker_sItem &rval){
    return this->A <= rval.getA() && this->B <= rval.getB() && this->C <= rval.getC();
}

bool Banker_sItem::operator>=(Banker_sItem &rval){
    return this->A >= rval.getA() && this->B >= rval.getB() && this->C >= rval.getC();
}

bool Banker_sItem::operator<(Banker_sItem &rval){
    return this->A < rval.getA() && this->B < rval.getB() && this->C < rval.getC();
}

bool Banker_sItem::operator>(Banker_sItem &rval){
    return this->A > rval.getA() && this->B > rval.getB() && this->C > rval.getC();
}

void Banker_sItem::operator=(Banker_sItem rval){
    this->A = rval.getA();
    this->B = rval.getB();
    this->C = rval.getC();

    return;
}