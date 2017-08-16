#ifndef __bitlib_h__
#define __bitlib_h__

#define CHAR_SIZE 8

#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "../utils/su.h"

using namespace std;

/**
 * Turn on i-th bit of num.
 */
void onbit(byte &num, int i);

/**
 * Check i-th bit of num.
 */
bool testbit(byte num, int i);

/**
 * Check i-th bit of buffer buff has buff_size bytes.
 */
bool arr_testbit(const byte *buff, int i);

/**
 * Turn on pos-th bit of buffer (buff), know size of buffer. 
 */
void arr_onbit(byte *buff, int pos);

/**
 * Convert a unsigned short number to char *.
 */
byte *short2buff(unsigned short x);

/**
 * Convert a unsigned char * to unsigned short number.
 */
unsigned short buff2short(byte * b);
 

/**
 * Print signal unit as readable format.
 */
void print_su(struct signal_unit su);

/**
 * Print all bit of byte c.
 */
void bin_print_char(byte c);

/**
 * Print all bits of buffer buff, know it size.
 */
void bin_print_buff(const byte *buff, int size);

/**
 * Print all bits of buffer buff, know it size.
 */
void hex_print_buff(const byte *buff, int size);

/**
 * Print all bits of buffer buff, know it size.
 */
void hex_print_buff(ofstream &os, const byte *buff, int size);

/**
 * Concatenate all field of a party address as a array of octets.
 */
byte *pa_to_buffer(struct party_address p);

/**
 * Concatenate all field of a signal unit as a array of octets.
 */
byte *su_to_buffer(struct signal_unit s);

/**
 * Convert a global title (string) to array of octets
 */
byte *strgtt_to_buff(string strgtt);

/**
 * Convert array of bytes to string (apply to global title).
 */
string buffgt_to_str(byte *gtt);

/**
 * Generate new su from strings - for quickly testing.
 * All fields give by strings.
 */
struct signal_unit new_su(string sbitg, string sgt, string spc, string sssn, string dgt, string dpc, string dssn);

/**
 * Set party address by give it all fields.
 */
void set_party_address(struct party_address &pa, string bitg, string gt, string pc, string ssn);

#endif
