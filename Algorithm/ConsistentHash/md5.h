#pragma once

/* typedef a 32 bit type */
typedef unsigned long int UINT4;

/* Data structure for MD5 (Message Digest) computation */
typedef struct {
    UINT4         i[2];       /* number of _bits_ handled mod 2^64 */
    UINT4         buf[4];     /* scratch buffer */
    unsigned char in[64];     /* input buffer */
    unsigned char digest[16]; /* actual digest after MD5Final call */
} MD5_CTX;

void        MD5Init(MD5_CTX* mdContext);
void        MD5Update(MD5_CTX* mdContext, unsigned char* inBuf, unsigned int inLen);
void        MD5Final(MD5_CTX* mdContext);
static void Transform(UINT4* buf, UINT4* in);

/**
 * @brief 根据指定的文件内容计算出MD5加密串
 *
 * @param path 文件路径
 * @param md5_len MD5加密串的长度
 * @return char* 返回MD5加密串
 */
char* MD5_file(const char* path, int md5_len = 32);

/**
 * @brief 从原始的字符串中得到加密后的MD5串
 *
 * @param buf 原始的字符串
 * @param md5_len MD5串的长度
 * @return char* 返回加密后的串
 */
char* MD5(const char* buf, int md5_len = 32);

/**
 * @brief 将32位的MD5串处理为unsigned int返回
 *
 * @param buf 要处理的MD5串
 * @return unsigned int 处理后的unsigned int
 */
unsigned int getMD5(const char* buf);
