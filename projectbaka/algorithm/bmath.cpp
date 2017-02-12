#include "bmath.h"
#include<ctime>
void init(tinymt32_t &tinymt, int arg1, int arg2, int arg3, int seed) {
	tinymt.mat1 = arg1;
	tinymt.mat2 = arg2;
	tinymt.tmat = arg3;
	tinymt32_init(&tinymt, seed);
}
math::RIG::RIG(int seed) {
	this->seed = seed;
	init(t, 0x8f7011ee, 0xfc78ff1f, 0x3793fdff,seed);
	
}


math::RIG::RIG() {
	this->seed = (unsigned int)time(0);
	init(t, 0x8f7011ee, 0xfc78ff1f, 0x3793fdff,seed);
}
int math::RIG::rand_int(int min, int max) {
	return min+__rand() % (max - min+1);
}
unsigned int math::RIG::__rand() {
	return tinymt32_generate_uint32(&t);
}
