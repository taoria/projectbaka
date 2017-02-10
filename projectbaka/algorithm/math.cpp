#include "bmath.h"
#include <algorithm>
template <typename T>
math::Vector2<T>::Vector2(T x, T y){
	this->firstElement = x;
	this->secondElement = y;
}
template <typename T>
math::Vector2<T>::Vector2(Vector2<T> & v):Vector2<T>(v.firstElement,v.secondElement){

}
template <typename T>
math::Vector2<T>::Vector2(Vector2<T> * v):Vector2<T>(v->firstElement,v->secondElement){
}
template <typename T>
math::Vector2<T>& math::Vector2<T>::operator+(Vector2<T> & b){
	Vector2<T> *temp = new Vector2<T>(this->firstElement+b.firstElement, this->secondElement + b.secondElement);
	return *temp;
}
template <typename T>
math::Vector2<T> & math::Vector2<T>::operator-(Vector2<T> & b){
	Vector2<T> *temp = new Vector2<T>(this->firstElement - b.firstElement, this->secondElement - b.secondElement);
	return *temp;
}

template <typename T>
math::Vector2<T> & math::Vector2<T>::operator=(Vector2<T> & b) {
	this->firstElement = b.firstElement;
	this->secondElement = b.secondElement;
	return *this;
}
template <typename T>
bool  math::Vector2<T>::operator==(Vector2<T> & b) {
	return firstElement == b.firstElement&&this->secondElement == b.secondElement;
}
template <typename T>
float math::Vector2<T>::operator*(Vector2<T> & b) {
	return this->firstElement*b.firstElement + this->secondElement*b.secondElement;
}
template <typename T>
math::Vector2<T> & math::Vector2<T>::operator*(T times){
	Vector2<T> *temp = new Vector2<T>(this->firstElement*times, this->secondElement*times);
	return *temp;
}
template <typename T>
math::Vector2<T> & math::Vector2<T>::operator+(T amount) {
	// TODO: 在此处插入 return 语句
	Vector2<T> *temp = new Vector2<T>(this->firstElement-amount, this->secondElement-amount);
	return *temp;
}
template <typename T>
math::Interval<T> * math::Interval<T>::IntervalsIntersection(Interval<T> * a, Interval<T> * b, int left, int right) {
	if (left == right) {
		if (left == STATE_FIRST) {
			return new Interval<T>(*b);
		}
		else {
			return new Interval<T>(*a);
		}
	}
	float left, right;
	bool lOpen, rOpen;
	if (STATE_FIRST != left) std::swap(a, b);
	left = b->firstElement;
	right = a->secondElement;
	lOpen = b->leftOpen;
	rOpen = a->rightOpen;
	return new Interval<T>(left, right, lOpen, rOpen);
}
template <typename T>
bool math::Interval<T>::operator==(Interval<T> & i) {
	return firstElement == i.firstElement&&this->secondElement == i.secondElement&&this->leftOpen == i.leftOpen&&rightOpen == i.rightOpen;
}
template <typename T>
math::Interval<T> & math::Interval<T>::operator=(Interval<T> & i) {
	this->firstElement = i.firstElement;
	this->secondElement = i.secondElement;
	this->leftOpen = i.leftOpen;
	this->rightOpen = i.rightOpen;
	this->state = i.state;
	return *this;
}
template <typename T>
math::Interval<T>::Interval(T left, T right):Interval<T>(left,right,false,false) {
}

template <typename T>
math::Interval<T>::Interval(T left, T right, bool lOpen, bool rOpen):Vector2<T>(left,right) {
	this->leftOpen = lOpen;
	this->rightOpen = rOpen;
	if (left > right) {
		left = right = 0;
		this->state = Interval<T>::STATE_INVALID;
	}
	else {
		if (left == right) {
			if (lOpen && rOpen) {
				this->state = Interval<T>::STATE_POINT;
			}
			else {
				if (lOpen || rOpen)
					this->state = Interval<T>::STATE_CONNECT;
				else
					this->state = Interval<T>::STATE_INVALID;
			}
				
		}
		else {
			this-> state = Interval<T>::STATE_Interval<T>;
		}

	}
}
template <typename T>
math::Interval<T>::Interval(Interval<T> & i):Vector2<T>(0,0){
	(*this) = i;
}
template <typename T>
bool math::Interval<T>::Include(T x) {
	if (x<this->secondElement&&x>this->firstElement) return true;
	if (x == this->firstElement) return !leftOpen;
	if (x == this->secondElement) return !rightOpen;
	return false;
}
template <typename T>
bool math::Interval<T>::Include(Interval<T> & i) {
	return this->CompareLeft(i) >= 0 && this->CompareRight(i) >= 0;
}
template <typename T>
//if equals return 0 if i is lefter,return -1,else return 1;
int math::Interval<T>::CompareLeft(Interval<T> & i) {
	if (this->firstElement == i.firstElement)
		return i.leftOpen - leftOpen;
	else
		return this->firstElement < i.firstElement ? 1 : -1;
}
template <typename T>
bool math::Interval<T>::CompareRight(Interval<T> & i) {
	if (this->secondElement == i.secondElement)
		return i.rightOpen - rightOpen;
	else
		return this->secondElement > i.secondElement ? 1 : -1;
}
template <typename T>
math::Interval<T>& math::Interval<T>::Merge(Interval<T> & v) {
	int left = this->CompareLeft(v) < 0 ? STATE_LAST : STATE_FIRST;
	int right = this->CompareRight(v) < 0 ? STATE_LAST : STATE_FIRST;
	Interval<T> *temp = IntervalsIntersection(this, &v, left, right);
	Interval<T>* pLeft = this, *pRight = &v;
	if (STATE_FIRST != left)
		std::swap(pLeft, pRight);
	if (temp->state != STATE_INVALID) {
		delete temp;
		return *new Interval<T>(pLeft->firstElement, pRight->secondElement, pLeft->leftOpen, pRight->rightOpen);
	}
	else {
		delete temp;
		return *new Interval<T>(1, -1);
	}
}
template <typename T>
math::Interval<T> & math::Interval<T>::Merge(float x, float y) {
	Interval<T> it(x, y, false, false);
	return Merge(it);
}
template <typename T>
math::Interval<T> & math::Interval<T>::Intersection(Interval<T> & v) {
	int left = this->CompareLeft(v)< 0 ? STATE_LAST : STATE_FIRST;
	int right = this->CompareRight(v) < 0 ? STATE_LAST : STATE_FIRST;
	return *IntervalsIntersection(this, &v, left, right);
}


