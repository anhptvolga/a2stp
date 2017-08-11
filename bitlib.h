#ifndef __bitlib_h__
#define __bitlib_h__

/**
 * turn on i-th bit of num
 */
void onbit(int &num, int i) {
    num |= 1 << i;
}

/**
 * turn off i-th bit of num
 */
void offbit(int &num, int i) {
    num &= ~(1 << i);
}

/**
 * check i-th bit of num
 */
bool testbit(int num, int i) {
    return (num & 1 << i) != 0;
}

#endif
