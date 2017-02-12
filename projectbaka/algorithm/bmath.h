#pragma once
#include "../core/base_object.h"
#include<vector>
#include "../core/bakamain.h"
#include<algorithm>
namespace math {
	template <typename T>
	class Set;
	template <typename T>
	class Vector2 :public ObjectBase {
	protected:
		float firstElement;
		float secondElement;
	public:
		Vector2(T x, T y);
		Vector2(Vector2 &v);
		Vector2(Vector2 *v);
		Vector2& operator +(Vector2 &b);
		Vector2& operator -(Vector2 &b);
		//dot 
		Vector2& operator =(Vector2 &b);
		bool operator ==(Vector2 &b);
		float operator *(Vector2 &b);
		Vector2& operator *(T times);
		Vector2& operator + (T amount);
	};
	class Vector2i :public ObjectBase {

	};
	template <typename T>
	class Interval :public Vector2<T> {
	protected:
		
		static Interval* IntervalsIntersection(Interval *a, Interval *b, int left, int right);
		bool leftOpen;
		bool rightOpen;
		int state;
		const  static int STATE_POINT = 0x01;
		const static int STATE_CONNECT = 0x02;
		const static int STATE_INVALID = 0x03;
		const static int STATE_INTERVAL = 0x00;
		const static int STATE_FIRST = 0x23;
		const static int STATE_LAST = 0x24;
	public:

		bool operator ==(Interval &i);
		Interval& operator =(Interval &i);
		Interval& operator <<(Interval &i);
		bool operator <(Interval &i);
		bool operator >(Interval &i);
		Interval(T left, T right);
		Interval(T left, T right, bool lOpen, bool rOpen);
		Interval(Interval &i);
		bool Include(T x);
		bool Include(Interval &i);
		bool Invalid();
		int CompareLeft(Interval &i);
		bool CompareRight(Interval &i);
		//Merge Intevals ,if no connection ,a empty interval will be created
		Interval& Merge(Interval &v);
		Interval& Merge(T x, T y);
		Interval& Intersection(Interval &v);
		 Set<Interval<T>*>* Split(T x);
	};
	template<typename T>
	class Set :public std::vector<T>, ObjectBase {
	public:
		void SortIncrease();
		void SortDecrease();
	};
}
template <typename T>
math::Vector2<T>::Vector2(T x, T y) {
	this->firstElement = x;
	this->secondElement = y;
}
template <typename T>
math::Vector2<T>::Vector2(Vector2<T> & v) :Vector2<T>(v.firstElement, v.secondElement) {

}
template <typename T>
math::Vector2<T>::Vector2(Vector2<T> * v) : Vector2<T>(v->firstElement, v->secondElement) {
}
template <typename T>
math::Vector2<T>& math::Vector2<T>::operator+(Vector2<T> & b) {
	Vector2<T> *temp = new Vector2<T>(this->firstElement + b.firstElement, this->secondElement + b.secondElement);
	return *temp;
}
template <typename T>
math::Vector2<T> & math::Vector2<T>::operator-(Vector2<T> & b) {
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
math::Vector2<T> & math::Vector2<T>::operator*(T times) {
	Vector2<T> *temp = new Vector2<T>(this->firstElement*times, this->secondElement*times);
	return *temp;
}
template <typename T>
math::Vector2<T> & math::Vector2<T>::operator+(T amount) {
	// TODO: �ڴ˴����� return ���
	Vector2<T> *temp = new Vector2<T>(this->firstElement - amount, this->secondElement - amount);
	return *temp;
}
template <typename T>
math::Interval<T> * math::Interval<T>::IntervalsIntersection(Interval<T> * a, Interval<T> * b,int left, int right) {
	if (left == right) {
		if (left == STATE_FIRST) {
			return new Interval<T>(*b);
		}
		else {
			return new Interval<T>(*a);
		}
	}
	T tleft, tright;
	bool lOpen, rOpen;
	if (STATE_FIRST != left) std::swap(a, b);
	tleft = b->firstElement;
	tright = a->secondElement;
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
//this merge i into itself and delete i;
template<typename T>
math::Interval<T> & math::Interval<T>::operator <<(Interval & i) {
	(*this) = Merge(i);
	delete &i;
	return *this;
}
template<typename T>
bool math::Interval<T>::operator<(Interval & i) {
	return this->firstElement < i.firstElement;
}
template<typename T>
bool math::Interval<T>::operator>(Interval & i) {
	return this->secondElement > i.secondElement;
}
template <typename T>
math::Interval<T>::Interval(T left, T right) :Interval<T>(left, right, false, false) {
}

template <typename T>
math::Interval<T>::Interval(T left, T right, bool lOpen, bool rOpen) : Vector2<T>(left, right) {
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
			this->state = Interval<T>::STATE_INTERVAL;
		}

	}
}
template <typename T>
math::Interval<T>::Interval(Interval<T> & i) :Vector2<T>(0, 0) {
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
template<typename T>
inline bool math::Interval<T>::Invalid() {
	return this->state == STATE_INVALID;
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
math::Interval<T> & math::Interval<T>::Merge(T x, T y) {
	Interval<T> it(x, y, false, false);
	return Merge(it);
}
template <typename T>
math::Interval<T> & math::Interval<T>::Intersection(Interval<T> & v) {
	int left = this->CompareLeft(v)< 0 ? STATE_LAST : STATE_FIRST;
	int right = this->CompareRight(v) < 0 ? STATE_LAST : STATE_FIRST;
	return *IntervalsIntersection(this, &v, left, right);
}

template<typename T>
math::Set<math::Interval<T>*>* math::Interval<T>::Split(T x) {
	math::Set<math::Interval<T>*> *s = new math::Set<math::Interval<T>*>;
	if (this->Include(x)) {
		Interval<T>* temp1 = new Interval(firstElement, x);
		Interval<T>* temp2 = new Interval(x, secondElement);
		s->push_back(temp1);
		s->push_back(temp2);
	}
	else {
		delete s;
	}
	return s;

}
template<typename T>
void cmp(T a, T b) {
	return b > a;
}
template<typename T>
void math::Set<T>::SortIncrease() {
	std::sort(this->begin(), this->end());
}
template<typename T>
void math::Set<T>::SortDecrease() {
	std::sort(this->begin(), this->end(), cmp);
}
