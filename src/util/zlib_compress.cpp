//
// Created by lxs on 17-4-2.
//

// This file is from https://github.com/nothings/stb/blob/master/stb_image_write.h

#include <stdlib.h>
#include <string.h>

#ifndef STBIW_MALLOC
#define STBIW_MALLOC(sz)        malloc(sz)
#define STBIW_REALLOC(p,newsz)  realloc(p,newsz)
#define STBIW_FREE(p)           free(p)
#endif

#ifndef STBIW_REALLOC_SIZED
#define STBIW_REALLOC_SIZED(p,oldsz,newsz) STBIW_REALLOC(p,newsz)
#endif

#ifndef STBIW_MEMMOVE
#define STBIW_MEMMOVE(a,b,sz) memmove(a,b,sz)
#endif

#ifndef STBIW_ASSERT
#include <assert.h>
#define STBIW_ASSERT(x) assert(x)
#endif

#define STBIW_UCHAR(x) (unsigned char) ((x) & 0xff)


#define stbiw__sbraw(a) ((int *) (a) - 2)
#define stbiw__sbm(a)   stbiw__sbraw(a)[0]
#define stbiw__sbn(a)   stbiw__sbraw(a)[1]

#define stbiw__sbneedgrow(a,n)  ((a)==0 || stbiw__sbn(a)+n >= stbiw__sbm(a))
#define stbiw__sbmaybegrow(a,n) (stbiw__sbneedgrow(a,(n)) ? stbiw__sbgrow(a,n) : 0)
#define stbiw__sbgrow(a,n)  stbiw__sbgrowf((void **) &(a), (n), sizeof(*(a)))

#define stbiw__sbpush(a, v)      (stbiw__sbmaybegrow(a,1), (a)[stbiw__sbn(a)++] = (v))
#define stbiw__sbcount(a)        ((a) ? stbiw__sbn(a) : 0)
#define stbiw__sbfree(a)         ((a) ? STBIW_FREE(stbiw__sbraw(a)),0 : 0)

typedef unsigned int stbiw_uint32;

static void *stbiw__sbgrowf(void **arr, int increment, int itemsize)
{
    int m = *arr ? 2*stbiw__sbm(*arr)+increment : increment+1;
    void *p = STBIW_REALLOC_SIZED(*arr ? stbiw__sbraw(*arr) : 0, *arr ? (stbiw__sbm(*arr)*itemsize + sizeof(int)*2) : 0, itemsize * m + sizeof(int)*2);
    STBIW_ASSERT(p);
    if (p) {
        if (!*arr) ((int *) p)[1] = 0;
        *arr = (void *) ((int *) p + 2);
        stbiw__sbm(*arr) = m;
    }
    return *arr;
}

static unsigned char *stbiw__zlib_flushf(unsigned char *data, unsigned int *bitbuffer, int *bitcount)
{
    while (*bitcount >= 8) {
        stbiw__sbpush(data, STBIW_UCHAR(*bitbuffer));
        *bitbuffer >>= 8;
        *bitcount -= 8;
    }
    return data;
}

static int stbiw__zlib_bitrev(int code, int codebits)
{
    int res=0;
    while (codebits--) {
        res = (res << 1) | (code & 1);
        code >>= 1;
    }
    return res;
}

static unsigned int stbiw__zlib_countm(unsigned char *a, unsigned char *b, int limit)
{
    int i;
    for (i=0; i < limit && i < 258; ++i)
        if (a[i] != b[i]) break;
    return i;
}

static unsigned int stbiw__zhash(unsigned char *data)
{
    stbiw_uint32 hash = data[0] + (data[1] << 8) + (data[2] << 16);
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;
    return hash;
}

#define stbiw__zlib_flush() (out = stbiw__zlib_flushf(out, &bitbuf, &bitcount))
#define stbiw__zlib_add(code,codebits) \
      (bitbuf |= (code) << bitcount, bitcount += (codebits), stbiw__zlib_flush())
#define stbiw__zlib_huffa(b,c)  stbiw__zlib_add(stbiw__zlib_bitrev(b,c),c)
// default huffman tables
#define stbiw__zlib_huff1(n)  stbiw__zlib_huffa(0x30 + (n), 8)
#define stbiw__zlib_huff2(n)  stbiw__zlib_huffa(0x190 + (n)-144, 9)
#define stbiw__zlib_huff3(n)  stbiw__zlib_huffa(0 + (n)-256,7)
#define stbiw__zlib_huff4(n)  stbiw__zlib_huffa(0xc0 + (n)-280,8)
#define stbiw__zlib_huff(n)  ((n) <= 143 ? stbiw__zlib_huff1(n) : (n) <= 255 ? stbiw__zlib_huff2(n) : (n) <= 279 ? stbiw__zlib_huff3(n) : stbiw__zlib_huff4(n))
#define stbiw__zlib_huffb(n) ((n) <= 143 ? stbiw__zlib_huff1(n) : stbiw__zlib_huff2(n))

#define stbiw__ZHASH   16384

unsigned char* stbi_zlib_compress(unsigned char *data, int data_len, int *out_len, int quality)
{
    static unsigned short lengthc[] = { 3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258, 259 };
    static unsigned char  lengtheb[]= { 0,0,0,0,0,0,0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4,  4,  5,  5,  5,  5,  0 };
    static unsigned short distc[]   = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577, 32768 };
    static unsigned char  disteb[]  = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13 };
    unsigned int bitbuf=0;
    int i,j, bitcount=0;
    unsigned char *out = NULL;
    unsigned char ***hash_table = (unsigned char***) STBIW_MALLOC(stbiw__ZHASH * sizeof(char**));
    if (quality < 5) quality = 5;

    stbiw__sbpush(out, 0x78);   // DEFLATE 32K window
    stbiw__sbpush(out, 0x5e);   // FLEVEL = 1
    stbiw__zlib_add(1,1);  // BFINAL = 1
    stbiw__zlib_add(1,2);  // BTYPE = 1 -- fixed huffman

    for (i=0; i < stbiw__ZHASH; ++i)
        hash_table[i] = NULL;

    i=0;
    while (i < data_len-3) {
        // hash next 3 bytes of data to be compressed
        int h = stbiw__zhash(data+i)&(stbiw__ZHASH-1), best=3;
        unsigned char *bestloc = 0;
        unsigned char **hlist = hash_table[h];
        int n = stbiw__sbcount(hlist);
        for (j=0; j < n; ++j) {
            if (hlist[j]-data > i-32768) { // if entry lies within window
                int d = stbiw__zlib_countm(hlist[j], data+i, data_len-i);
                if (d >= best) best=d,bestloc=hlist[j];
            }
        }
        // when hash table entry is too long, delete half the entries
        if (hash_table[h] && stbiw__sbn(hash_table[h]) == 2*quality) {
            STBIW_MEMMOVE(hash_table[h], hash_table[h]+quality, sizeof(hash_table[h][0])*quality);
            stbiw__sbn(hash_table[h]) = quality;
        }
        stbiw__sbpush(hash_table[h],data+i);

        if (bestloc) {
            // "lazy matching" - check match at *next* byte, and if it's better, do cur byte as literal
            h = stbiw__zhash(data+i+1)&(stbiw__ZHASH-1);
            hlist = hash_table[h];
            n = stbiw__sbcount(hlist);
            for (j=0; j < n; ++j) {
                if (hlist[j]-data > i-32767) {
                    int e = stbiw__zlib_countm(hlist[j], data+i+1, data_len-i-1);
                    if (e > best) { // if next match is better, bail on current match
                        bestloc = NULL;
                        break;
                    }
                }
            }
        }

        if (bestloc) {
            int d = (int) (data+i - bestloc); // distance back
            STBIW_ASSERT(d <= 32767 && best <= 258);
            for (j=0; best > lengthc[j+1]-1; ++j);
            stbiw__zlib_huff(j+257);
            if (lengtheb[j]) stbiw__zlib_add(best - lengthc[j], lengtheb[j]);
            for (j=0; d > distc[j+1]-1; ++j);
            stbiw__zlib_add(stbiw__zlib_bitrev(j,5),5);
            if (disteb[j]) stbiw__zlib_add(d - distc[j], disteb[j]);
            i += best;
        } else {
            stbiw__zlib_huffb(data[i]);
            ++i;
        }
    }
    // write out final bytes
    for (;i < data_len; ++i)
        stbiw__zlib_huffb(data[i]);
    stbiw__zlib_huff(256); // end of block
    // pad with 0 bits to byte boundary
    while (bitcount)
        stbiw__zlib_add(0,1);

    for (i=0; i < stbiw__ZHASH; ++i)
        (void) stbiw__sbfree(hash_table[i]);
    STBIW_FREE(hash_table);

    {
        // compute adler32 on input
        unsigned int s1=1, s2=0;
        int blocklen = (int) (data_len % 5552);
        j=0;
        while (j < data_len) {
            for (i=0; i < blocklen; ++i) s1 += data[j+i], s2 += s1;
            s1 %= 65521, s2 %= 65521;
            j += blocklen;
            blocklen = 5552;
        }
        stbiw__sbpush(out, STBIW_UCHAR(s2 >> 8));
        stbiw__sbpush(out, STBIW_UCHAR(s2));
        stbiw__sbpush(out, STBIW_UCHAR(s1 >> 8));
        stbiw__sbpush(out, STBIW_UCHAR(s1));
    }
    *out_len = stbiw__sbn(out);
    // make returned pointer freeable
    STBIW_MEMMOVE(stbiw__sbraw(out), out, *out_len);
    return (unsigned char *) stbiw__sbraw(out);
}