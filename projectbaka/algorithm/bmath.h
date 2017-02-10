#pragma once
#include "../core/base_object.h"
namespace math{
	template <typename T>
	class Vector2 :public ObjectBase{
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
	class Vector2i :public ObjectBase{

	};
	template <typename T>
	class Interval:public Vector2<T>{
	private:
		const  static int STATE_POINT = 0x01;
		const static int STATE_CONNECT = 0x02;
		const static int STATE_INVALID = 0x03;
		const static int STATE_INTERVAL = 0x00;
		const static int STATE_FIRST = 0x23;
		const static int STATE_LAST = 0x24;
		static Interval* IntervalsIntersection(Interval *a, Interval *b, int left, int right);
	protected:
		bool leftOpen;
		bool rightOpen;
		int state;
	public:
		bool operator ==(Interval &i);
		Interval& operator =(Interval &i);
	
		Interval(T left, T right);
		Interval(T left, T right, bool lOpen, bool rOpen);
		Interval(Interval &i);
		bool Include(T x);
		bool Include(Interval &i);
		bool Invalid;
		int CompareLeft(Interval &i);
		bool CompareRight(Interval &i);
		//Merge Intevals ,if no connection ,a empty interval will be created
		Interval& Merge(Interval &v);
		Interval& Merge(float x,float y);
		Interval& Intersection(Interval &v);
	};
}
