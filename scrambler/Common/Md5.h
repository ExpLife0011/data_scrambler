#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MD5.h : header file
//
#ifndef _PUBLIC_MD5_H_
#define _PUBLIC_MD5_H_


#ifndef	WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif


#define MAXSTRLEN   1024

// F, G, H and I are basic MD5 functions. 
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

// ROTATE_LEFT rotates x left n bits. 
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation. 
#define FF(a, b, c, d, x, s, ac) { \
    (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
    }
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
    }
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
    }
#define II(a, b, c, d, x, s, ac) { \
    (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
    }

// POINTER defines a generic pointer type 
typedef unsigned char *POINTER; 

// UINT2 defines a two byte words
typedef unsigned short int UINT2;

// UINT4 defines a four byte word 
typedef unsigned long int UINT4;

// Constants for MD5Transform routine. 
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

// MD5 context. 
typedef struct {
    UINT4 state[4];             // state (ABCD) 
    UINT4 count[2];             // number of bits, modulo 2^64 (lsb first) 
    unsigned char buffer[64];   // input buffer 
} MD5_CTX;

static unsigned char PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

class  CMd5
{
public:
	//BOOL MDFile(const std::string& strFileName, unsigned char digest[16]);
	//char * MD5( unsigned char * input);
//private:

	static void MD5Transform(UINT4 [4], unsigned char [64]);
	static void Encode(unsigned char *, UINT4 *, unsigned int);
	static void Decode(UINT4 *, unsigned char *, unsigned int);
	static void MD5_memcpy(POINTER, POINTER, unsigned int);
	static void MD5_memset(POINTER, int, unsigned int);
	static void MD5Init(MD5_CTX *context);
	static void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen);
	static void MD5Final (unsigned char digest[16], MD5_CTX *context);
};
#endif
