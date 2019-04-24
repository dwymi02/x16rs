#include "x16rs.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

void print_byte_list(char* name, void *data, int len, int wide);

#include "sha3/sph_blake.h"
#include "sha3/sph_bmw.h"
#include "sha3/sph_groestl.h"
#include "sha3/sph_jh.h"
#include "sha3/sph_keccak.h"
#include "sha3/sph_skein.h"
#include "sha3/sph_luffa.h"
#include "sha3/sph_cubehash.h"
#include "sha3/sph_shavite.h"
#include "sha3/sph_simd.h"
#include "sha3/sph_echo.h"
#include "sha3/sph_hamsi.h"
#include "sha3/sph_fugue.h"
#include "sha3/sph_shabal.h"
#include "sha3/sph_whirlpool.h"
#include "sha3/sph_sha2.h"
#include "sha3_256/sha3.h"


void print_byte_list(char* name, void *data, int len, int wide)
{
    if(len > 0){
        int i;
        printf("%s: %d", name, ((uint8_t*)data)[0]);
        for(i=1; i<len; i++){
            if(wide>0 && i%wide==0) printf("\n");
            printf(",%d", ((uint8_t*)data)[i]);
        }
    }else{
        printf("%s", name);
    }
    printf("\n");
    fflush(stdout);
}

void sha3_256(const char *input, const int in_size, char *output)
{

    sha3_ctx ctx;
    rhash_sha3_256_init(&ctx);
    rhash_sha3_update(&ctx, input, in_size);
    rhash_sha3_final(&ctx, output);

}


enum Algo {
    BLAKE = 0,
    BMW,
    GROESTL,
    JH,
    KECCAK,
    SKEIN,
    LUFFA,
    CUBEHASH,
    SHAVITE,
    SIMD,
    ECHO,
    HAMSI,
    FUGUE,
    SHABAL,
    WHIRLPOOL,
    SHA512,
    HASH_FUNC_COUNT
};

static void getAlgoString(const uint8_t* prevblock, char *output)
{
    char *sptr = output;
    int j;
    for (j = 0; j < HASH_FUNC_COUNT; j++) {
        char b = (15 - j) >> 1; // 16 ascii hex chars, reversed
        uint8_t algoDigit = (j & 1) ? prevblock[b] & 0xF : prevblock[b] >> 4;
        if (algoDigit >= 10)
            sprintf(sptr, "%c", 'A' + (algoDigit - 10));
        else
            sprintf(sptr, "%u", (uint32_t) algoDigit);
        sptr++;
    }
    *sptr = '\0';
}

void x16r_hash(const char* input, char* output)
{
    uint32_t hash[64/4];
    char hashOrder[HASH_FUNC_COUNT + 1] = { 0 };

    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_skein512_context     ctx_skein;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_luffa512_context     ctx_luffa;
    sph_cubehash512_context  ctx_cubehash;
    sph_shavite512_context   ctx_shavite;
    sph_simd512_context      ctx_simd;
    sph_echo512_context      ctx_echo;
    sph_hamsi512_context     ctx_hamsi;
    sph_fugue512_context     ctx_fugue;
    sph_shabal512_context    ctx_shabal;
    sph_whirlpool_context    ctx_whirlpool;
    sph_sha512_context       ctx_sha512;

    void *in = (void*) input;
    int size = 80;

    getAlgoString((uint8_t*)&input[4], hashOrder);
    
    int i;
    for (i = 0; i < 16; i++) {
        const char elem = hashOrder[i];
        const uint8_t algo = elem >= 'A' ? elem - 'A' + 10 : elem - '0';

        switch (algo) {
            case BLAKE:
            sph_blake512_init(&ctx_blake);
            sph_blake512(&ctx_blake, in, size);
            sph_blake512_close(&ctx_blake, hash);
            break;
            case BMW:
            sph_bmw512_init(&ctx_bmw);
            sph_bmw512(&ctx_bmw, in, size);
            sph_bmw512_close(&ctx_bmw, hash);
            break;
            case GROESTL:
            sph_groestl512_init(&ctx_groestl);
            sph_groestl512(&ctx_groestl, in, size);
            sph_groestl512_close(&ctx_groestl, hash);
            break;
            case SKEIN:
            sph_skein512_init(&ctx_skein);
            sph_skein512(&ctx_skein, in, size);
            sph_skein512_close(&ctx_skein, hash);
            break;
            case JH:
            sph_jh512_init(&ctx_jh);
            sph_jh512(&ctx_jh, in, size);
            sph_jh512_close(&ctx_jh, hash);
            break;
            case KECCAK:
            sph_keccak512_init(&ctx_keccak);
            sph_keccak512(&ctx_keccak, in, size);
            sph_keccak512_close(&ctx_keccak, hash);
            break;
            case LUFFA:
            sph_luffa512_init(&ctx_luffa);
            sph_luffa512(&ctx_luffa, in, size);
            sph_luffa512_close(&ctx_luffa, hash);
            break;
            case CUBEHASH:
            sph_cubehash512_init(&ctx_cubehash);
            sph_cubehash512(&ctx_cubehash, in, size);
            sph_cubehash512_close(&ctx_cubehash, hash);
            break;
            case SHAVITE:
            sph_shavite512_init(&ctx_shavite);
            sph_shavite512(&ctx_shavite, in, size);
            sph_shavite512_close(&ctx_shavite, hash);
            break;
            case SIMD:
            sph_simd512_init(&ctx_simd);
            sph_simd512(&ctx_simd, in, size);
            sph_simd512_close(&ctx_simd, hash);
            break;
            case ECHO:
            sph_echo512_init(&ctx_echo);
            sph_echo512(&ctx_echo, in, size);
            sph_echo512_close(&ctx_echo, hash);
            break;
            case HAMSI:
            sph_hamsi512_init(&ctx_hamsi);
            sph_hamsi512(&ctx_hamsi, in, size);
            sph_hamsi512_close(&ctx_hamsi, hash);
            break;
            case FUGUE:
            sph_fugue512_init(&ctx_fugue);
            sph_fugue512(&ctx_fugue, in, size);
            sph_fugue512_close(&ctx_fugue, hash);
            break;
            case SHABAL:
            sph_shabal512_init(&ctx_shabal);
            sph_shabal512(&ctx_shabal, in, size);
            sph_shabal512_close(&ctx_shabal, hash);
            break;
            case WHIRLPOOL:
            sph_whirlpool_init(&ctx_whirlpool);
            sph_whirlpool(&ctx_whirlpool, in, size);
            sph_whirlpool_close(&ctx_whirlpool, hash);
            break;
            case SHA512:
            sph_sha512_init(&ctx_sha512);
            sph_sha512(&ctx_sha512,(const void*) in, size);
            sph_sha512_close(&ctx_sha512,(void*) hash);
            break;
        }
        in = (void*) hash;
        size = 64;
    }
    memcpy(output, hash, 32);
}

// input length must more than 32
void x16rs_hash(const char* input, char* output)
{
    int insize = 32;
    x16rs_hash_sz(input, output, insize);
}



// input length must more than 32
void x16rs_hash_sz(const char* input, char* output, int insize)
{
    //    printf("%s\n", input);
    // print_byte_list("x16rs_hash_sz input", (void*)input, 32, 0);

    uint32_t hash[64/4];

    // char hashOrder[HASH_FUNC_COUNT + 1] = { 0 };

    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_skein512_context     ctx_skein;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_luffa512_context     ctx_luffa;
    sph_cubehash512_context  ctx_cubehash;
    sph_shavite512_context   ctx_shavite;
    sph_simd512_context      ctx_simd;
    sph_echo512_context      ctx_echo;
    sph_hamsi512_context     ctx_hamsi;
    sph_fugue512_context     ctx_fugue;
    sph_shabal512_context    ctx_shabal;
    sph_whirlpool_context    ctx_whirlpool;
    sph_sha512_context       ctx_sha512;

    void *in = (void*) input;

    memcpy((void*)hash, input, 32); // first

    int size = insize;

    int i;
    for(i = 0; i < 1; i++) {

        uint8_t algo = hash[7] % 16;

        // print_byte_list("x16rs_hash_sz hash", (void*)hash, 4, 0);
        // print_byte_list("x16rs_hash_sz hash[7]", (void*)&hash[7], 4, 0);
        // print_byte_list("x16rs_hash_sz algo", (void*)&algo, 1, 0);

        switch (algo) {
            case BLAKE:
            sph_blake512_init(&ctx_blake);
            sph_blake512(&ctx_blake, in, size);
            sph_blake512_close(&ctx_blake, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case BMW:
            sph_bmw512_init(&ctx_bmw);
            sph_bmw512(&ctx_bmw, in, size);
            sph_bmw512_close(&ctx_bmw, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case GROESTL:
            sph_groestl512_init(&ctx_groestl);
            sph_groestl512(&ctx_groestl, in, size);
            sph_groestl512_close(&ctx_groestl, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case SKEIN:
            sph_skein512_init(&ctx_skein);
            sph_skein512(&ctx_skein, in, size);
            sph_skein512_close(&ctx_skein, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case JH:
            sph_jh512_init(&ctx_jh);
            sph_jh512(&ctx_jh, in, size);
            sph_jh512_close(&ctx_jh, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case KECCAK:
            sph_keccak512_init(&ctx_keccak);
            sph_keccak512(&ctx_keccak, in, size);
            sph_keccak512_close(&ctx_keccak, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case LUFFA:
            sph_luffa512_init(&ctx_luffa);
            sph_luffa512(&ctx_luffa, in, size);
            sph_luffa512_close(&ctx_luffa, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case CUBEHASH:
            sph_cubehash512_init(&ctx_cubehash);
            sph_cubehash512(&ctx_cubehash, in, size);
            sph_cubehash512_close(&ctx_cubehash, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case SHAVITE:
            sph_shavite512_init(&ctx_shavite);
            sph_shavite512(&ctx_shavite, in, size);
            sph_shavite512_close(&ctx_shavite, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case SIMD:
            sph_simd512_init(&ctx_simd);
            sph_simd512(&ctx_simd, in, size);
            sph_simd512_close(&ctx_simd, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case ECHO:
            sph_echo512_init(&ctx_echo);
            sph_echo512(&ctx_echo, in, size);
            sph_echo512_close(&ctx_echo, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case HAMSI:
            sph_hamsi512_init(&ctx_hamsi);
            sph_hamsi512(&ctx_hamsi, in, size);
            sph_hamsi512_close(&ctx_hamsi, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case FUGUE:
            sph_fugue512_init(&ctx_fugue);
            sph_fugue512(&ctx_fugue, in, size);
            sph_fugue512_close(&ctx_fugue, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case SHABAL:
            sph_shabal512_init(&ctx_shabal);
            sph_shabal512(&ctx_shabal, in, size);
            sph_shabal512_close(&ctx_shabal, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case WHIRLPOOL:
            sph_whirlpool_init(&ctx_whirlpool);
            sph_whirlpool(&ctx_whirlpool, in, size);
            sph_whirlpool_close(&ctx_whirlpool, hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
            case SHA512:
            sph_sha512_init(&ctx_sha512);
            sph_sha512(&ctx_sha512,(const void*) in, size);
            sph_sha512_close(&ctx_sha512,(void*) hash);
            /*printf("switch (algo) = %d \n", algo);
            for(int i=0; i<8; i++){
                printf("hash %d = %d\n", i, hash[i]);
            }*/
            break;
        }
        in = (void*) hash;
    }

    memcpy(output, hash, 32);

    // print_byte_list("x16rs_hash_sz output", (void*)output, 32, 0);
}


// input length must more than 32
static const int x16rs_hash_insize = 32;
void x16rs_hash_optimize(const char* input, char* output)
{
    // uint32_t hash[64/4];
    uint32_t *hash = (uint32_t*) input;
    // uint8_t algo = hash[7] % 16;
    uint8_t algo = *(hash+7) % 16;

    if( algo == BLAKE  ){
        sph_blake512_context     ctx_blake;
        sph_blake512_init(&ctx_blake);
        sph_blake512(&ctx_blake, input, x16rs_hash_insize);
        sph_blake512_close(&ctx_blake, output);
    }else if( algo == BMW ){
        sph_bmw512_context       ctx_bmw;
        sph_bmw512_init(&ctx_bmw);
        sph_bmw512(&ctx_bmw, input, x16rs_hash_insize);
        sph_bmw512_close(&ctx_bmw, output);
    }else if( algo == GROESTL ){
        sph_groestl512_context   ctx_groestl;
        sph_groestl512_init(&ctx_groestl);
        sph_groestl512(&ctx_groestl, input, x16rs_hash_insize);
        sph_groestl512_close(&ctx_groestl, output);
    }else if( algo == SKEIN ){
        sph_skein512_context     ctx_skein;
        sph_skein512_init(&ctx_skein);
        sph_skein512(&ctx_skein, input, x16rs_hash_insize);
        sph_skein512_close(&ctx_skein, output);
    }else if( algo == JH ){
        sph_jh512_context        ctx_jh;
        sph_jh512_init(&ctx_jh);
        sph_jh512(&ctx_jh, input, x16rs_hash_insize);
        sph_jh512_close(&ctx_jh, output);
    }else if( algo == KECCAK ){
        sph_keccak512_context    ctx_keccak;
        sph_keccak512_init(&ctx_keccak);
        sph_keccak512(&ctx_keccak, input, x16rs_hash_insize);
        sph_keccak512_close(&ctx_keccak, output);
    }else if( algo == LUFFA ){
        sph_luffa512_context     ctx_luffa;
        sph_luffa512_init(&ctx_luffa);
        sph_luffa512(&ctx_luffa, input, x16rs_hash_insize);
        sph_luffa512_close(&ctx_luffa, output);
    }else if( algo == CUBEHASH ){
        sph_cubehash512_context  ctx_cubehash;
        sph_cubehash512_init(&ctx_cubehash);
        sph_cubehash512(&ctx_cubehash, input, x16rs_hash_insize);
        sph_cubehash512_close(&ctx_cubehash, output);
    }else if( algo == SHAVITE ){
        sph_shavite512_context   ctx_shavite;
        sph_shavite512_init(&ctx_shavite);
        sph_shavite512(&ctx_shavite, input, x16rs_hash_insize);
        sph_shavite512_close(&ctx_shavite, output);
    }else if( algo == SIMD ){
        sph_simd512_context      ctx_simd;
        sph_simd512_init(&ctx_simd);
        sph_simd512(&ctx_simd, input, x16rs_hash_insize);
        sph_simd512_close(&ctx_simd, output);
    }else if( algo == ECHO ){
        sph_echo512_context      ctx_echo;
        sph_echo512_init(&ctx_echo);
        sph_echo512(&ctx_echo, input, x16rs_hash_insize);
        sph_echo512_close(&ctx_echo, output);
    }else if( algo == HAMSI ){
        sph_hamsi512_context     ctx_hamsi;
        sph_hamsi512_init(&ctx_hamsi);
        sph_hamsi512(&ctx_hamsi, input, x16rs_hash_insize);
        sph_hamsi512_close(&ctx_hamsi, output);
    }else if( algo == FUGUE ){
        sph_fugue512_context     ctx_fugue;
        sph_fugue512_init(&ctx_fugue);
        sph_fugue512(&ctx_fugue, input, x16rs_hash_insize);
        sph_fugue512_close(&ctx_fugue, output);
    }else if( algo == SHABAL ){
        sph_shabal512_context    ctx_shabal;
        sph_shabal512_init(&ctx_shabal);
        sph_shabal512(&ctx_shabal, input, x16rs_hash_insize);
        sph_shabal512_close(&ctx_shabal, output);
    }else if( algo == WHIRLPOOL ){
        sph_whirlpool_context    ctx_whirlpool;
        sph_whirlpool_init(&ctx_whirlpool);
        sph_whirlpool(&ctx_whirlpool, input, x16rs_hash_insize);
        sph_whirlpool_close(&ctx_whirlpool, output);
    }else if( algo == SHA512 ){
        sph_sha512_context       ctx_sha512;
        sph_sha512_init(&ctx_sha512);
        sph_sha512(&ctx_sha512,(const void*) input, x16rs_hash_insize);
        sph_sha512_close(&ctx_sha512,(void*) output);
    }
    

}



// input length must be 32
static const uint8_t diamond_hash_base_stuff[17] = "0WTYUIAHXVMEKBSZN";
void diamond_hash(const char* hash32, char* output16)
{
    uint8_t *stuff32 = (uint8_t*)hash32;
    int i;
    for(i=0; i<16; i++){
        int num = (int)stuff32[i*2] * (int)stuff32[i*2+1];
        output16[i] = diamond_hash_base_stuff[num % 17];
    }
}


// input length must be 32
void miner_diamond_hash(const char* stop_mark1, const char* input32, const char* addr21, char* nonce8, char* diamond16)
{

    // 停止标记
    uint8_t *is_stop = (uint8_t*)stop_mark1;

    uint32_t basestuff[8+2+6];
    memcpy( (void*)basestuff, (void*)input32, 32);
    memcpy( (void*)basestuff+40, (void*)addr21, 21);

    uint8_t sha3res[32];
    uint8_t hashnew[32];
    uint8_t diamond[16];

    uint32_t noncenum1;
    uint32_t noncenum2;
    for(noncenum1=1; noncenum1<4294967294; noncenum1++){
        basestuff[8] = noncenum1;
        for(noncenum2=1; noncenum2<4294967294; noncenum2++){
            basestuff[9] = noncenum2;

            // 停止
            if( is_stop[0] != 0 ) {
                uint8_t noncenum_empty[8] = {0,0,0,0,0,0,0,0};
                memcpy( nonce8, noncenum_empty, 8);
                return; // 返回空
            }

            // 哈希计算
            sha3_256((char*)basestuff, 61, (char*)sha3res);
            x16rs_hash((char*)sha3res, (char*)hashnew);
            diamond_hash((char*)hashnew, (char*)diamond);
            /*
            printf("hash: ");
            uint8_t *input32p = (uint8_t*)hashnew;
            int j;
            for(j=0; j<32; j++){
                printf("%u,", input32p[j]);
            }
            printf("\n");
            */
            // 判断结果是否为钻石
            uint8_t success = 1;
            uint8_t haschar = 0;
            int k;
            for( k=0; k<16; k++ ) {
                if(k<5){
                    if( diamond[k] != 48 ){
                        success = 0;
                        break;
                    }
                }else{
                    if( haschar && diamond[k] == 48 ){
                        success = 0;
                        break;
                    }
                    if( diamond[k] != 48 ){
                        haschar = 1;
                    }
                }
            }

            // 挖出钻石
            if( success == 1 ) {
                uint32_t nonce[2] = {0, 0};
                nonce[0] = noncenum1;
                nonce[1] = noncenum2;
                memcpy( (char*)nonce8, (char*)nonce, 8);
                memcpy( (char*)diamond16, (char*)diamond, 16);
                return; // 拷贝值，返回成功
            }
        }
    }





    /*

    int zerofront = 8;

    uint8_t diamond[16];

    uint8_t noncenum[8] = {0,0,0,0,0,0,0,0};
    uint8_t i0;
    for(i0=0; i0<255; i0++){
    noncenum[0] = i0;
    uint8_t i1;
    for(i1=0; i1<255; i1++){
    noncenum[1] = i1;
    uint8_t i2;
    for(i2=0; i2<255; i2++){
    noncenum[2] = i2;
    uint8_t i3;
    for(i3=0; i3<255; i3++){
    noncenum[3] = i3;
    uint8_t i4;
    for(i4=0; i4<255; i4++){
    noncenum[4] = i4;
    uint8_t i5;
    for(i5=0; i5<255; i5++){
    noncenum[5] = i5;
    uint8_t i6;
    for(i6=0; i6<255; i6++){
    noncenum[6] = i6;
    uint8_t i7;
    for(i7=0; i7<255; i7++){
    noncenum[7] = i7;


        diamond_hash(input32, addr21, noncenum, diamond);
        uint8_t isok = 1;
        uint8_t isnchar = 0;
        int k;
        for( k=0; k<16; k++ ) {
            if( k<zerofront && diamond[k] != 48 ){
                isok = 0;
                break;
            }
            if( k>=zerofront ) {
                if( diamond[k] == 48 ){
                    if( isnchar == 1 ){
                        isok = 0;
                        break;
                    }
                }else{
                    isnchar = 1;
                }
            }
        }


        if(isok == 1){


            memcpy(nonce8, noncenum, 8);
            memcpy(output16, diamond, 16);

            int i;

            printf("hash: ");
            uint8_t *input32p = (uint8_t*)input32;
            for(i=0; i<32; i++){
                printf("%u,", input32p[i]);
            }
            printf("  addr: ");
            uint8_t *addr21p = (uint8_t*)addr21;
            for(i=0; i<21; i++){
                printf("%u,", addr21p[i]);
            }
            printf("  nonce: ");
            for(i=0; i<8; i++){
                printf("%u,", noncenum[i]);
            }
            uint8_t noncenum_swap[8];
            for(i=0; i<8; i++){ noncenum_swap[i] = noncenum[7-i]; }
            uint64_t *nnum = (uint64_t*)noncenum;
            uint64_t *nnum_swap = (uint64_t*)noncenum_swap;
            printf("  diamond nonce = %ld/%ld, value = %16.16s \n", *nnum_swap, *nnum, diamond);


        }


    }}}}}}}}


    */


}


// 挖矿算法
void miner_x16rs_hash_v1(const char* stop_mark1, const char* target_difficulty_hash32, const char* input_stuff89, char* nonce4)
{
//    printf("miner_x16rs_hash_v1()\n");
    // 签名信息
    uint8_t stuffnew_base[90];
    uint8_t *stuffnew = stuffnew_base+1;
    memcpy( stuffnew, input_stuff89, 89);
    uint32_t *stuffnew_uint32 = (uint32_t*)stuffnew_base;

    // 计算 sha3的结果
    unsigned char sha3res[32];

    // x16rs hash的结果
    uint8_t hashnew[32];

    // 判断哈希是否满足要求
    uint8_t iscalcok = 0;

    // 检查结果的for循环值
    uint8_t pi = 0;

    // 停止标记
    uint8_t *is_stop = (uint8_t*)stop_mark1;

    // nonce值
    uint32_t noncenum;
    for(noncenum=1; noncenum<4294967294; noncenum++){
        // 停止标记检测
        if( is_stop[0] != 0 )
        {
            return;
        }
        // 重置nonce
        stuffnew_uint32[20] = noncenum;
//        memcpy(&stuffnew[79], &noncenum, 4);
        // 计算 sha3
        sha3_256(stuffnew, 89, sha3res);
        /*
            printf("  hash: ");
            uint8_t i;
            for(i=0; i<32; i++){
                printf("%u,", sha3res[i]);
            }
            printf("\n");
        */
        x16rs_hash(((void*)sha3res), ((void*)hashnew));
        // x16rs_hash_optimize(((void*)sha3res), ((void*)hashnew));
        /*
            printf("  hash: ");
            uint8_t i;
            for(i=0; i<32; i++){
                printf("%u,", hashnew[i]);
            }
            printf("\n");
        */
        iscalcok = 0;
        for(pi=0; pi<32; pi++){
            uint8_t o1 = target_difficulty_hash32[pi];
            uint8_t o2 = hashnew[pi];
            if(o2>o1){
                break;
            }
            if(o2<o1){
                iscalcok = 1;
                break;
            }
        }
        // 结果判断
        if(iscalcok == 1) {
        /*
            printf("finish hash: ");
            uint8_t i;
            for(i=0; i<32; i++){
                printf("%u,", hashnew[i]);
            }
            printf("\n");
        */
            // 返回 copy to out
            memcpy(nonce4, &noncenum, 4);
            return; // success
        }
        // 继续下一次计算
    }

    // 循环完毕，失败
    noncenum = 0;
    memcpy(nonce4, &noncenum, 4);
    return;

}









///////////////////// TEST /////////////////////



void test_print_x16rs(const char* input, char* output32x16)
{
    int insize = 32;
    int size = insize;
    int i = 0;
//    printf("%s\n", input);

    uint32_t hash[64/4];

    // char hashOrder[HASH_FUNC_COUNT + 1] = { 0 };

    sph_blake512_context     ctx_blake;
    sph_bmw512_context       ctx_bmw;
    sph_groestl512_context   ctx_groestl;
    sph_skein512_context     ctx_skein;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_luffa512_context     ctx_luffa;
    sph_cubehash512_context  ctx_cubehash;
    sph_shavite512_context   ctx_shavite;
    sph_simd512_context      ctx_simd;
    sph_echo512_context      ctx_echo;
    sph_hamsi512_context     ctx_hamsi;
    sph_fugue512_context     ctx_fugue;
    sph_shabal512_context    ctx_shabal;
    sph_whirlpool_context    ctx_whirlpool;
    sph_sha512_context       ctx_sha512;

    void *in = (void*) input;
    uint8_t output[32];
    // memcpy((void*)hash, input, 32); // first

    
    sph_blake512_init(&ctx_blake);
    sph_blake512(&ctx_blake, in, size);
    sph_blake512_close(&ctx_blake, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*0, (void*)hash, 32);
    
    
    sph_bmw512_init(&ctx_bmw);
    sph_bmw512(&ctx_bmw, in, size);
    sph_bmw512_close(&ctx_bmw, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*1, (void*)hash, 32);
    

    
    sph_groestl512_init(&ctx_groestl);
    sph_groestl512(&ctx_groestl, in, size);
    sph_groestl512_close(&ctx_groestl, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*2, (void*)hash, 32);
    
    
    
    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, in, size);
    sph_skein512_close(&ctx_skein, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*3, (void*)hash, 32);
    
    
    
    sph_jh512_init(&ctx_jh);
    sph_jh512(&ctx_jh, in, size);
    sph_jh512_close(&ctx_jh, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*4, (void*)hash, 32);
    
    
    

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512(&ctx_keccak, in, size);
    sph_keccak512_close(&ctx_keccak, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*5, (void*)hash, 32);
    
    
    
    sph_luffa512_init(&ctx_luffa);
    sph_luffa512(&ctx_luffa, in, size);
    sph_luffa512_close(&ctx_luffa, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*6, (void*)hash, 32);
    
    
    
    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512(&ctx_cubehash, in, size);
    sph_cubehash512_close(&ctx_cubehash, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*7, (void*)hash, 32);
    
    
    
    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, in, size);
    sph_shavite512_close(&ctx_shavite, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*8, (void*)hash, 32);
    

    
    
    sph_simd512_init(&ctx_simd);
    sph_simd512(&ctx_simd, in, size);
    sph_simd512_close(&ctx_simd, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*9, (void*)hash, 32); 


 
    sph_echo512_init(&ctx_echo);
    sph_echo512(&ctx_echo, in, size);
    sph_echo512_close(&ctx_echo, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*10, (void*)hash, 32);
    
    
    
    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512(&ctx_hamsi, in, size);
    sph_hamsi512_close(&ctx_hamsi, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*11, (void*)hash, 32);  

    
    sph_fugue512_init(&ctx_fugue);
    sph_fugue512(&ctx_fugue, in, size);
    sph_fugue512_close(&ctx_fugue, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*12, (void*)hash, 32);
    

    
    sph_shabal512_init(&ctx_shabal);
    sph_shabal512(&ctx_shabal, in, size);
    sph_shabal512_close(&ctx_shabal, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*13, (void*)hash, 32);
    

    
    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool(&ctx_whirlpool, in, size);
    sph_whirlpool_close(&ctx_whirlpool, hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*14, (void*)hash, 32);
    

    
    sph_sha512_init(&ctx_sha512);
    sph_sha512(&ctx_sha512,(const void*) in, size);
    sph_sha512_close(&ctx_sha512,(void*) hash);
    in = (void*) hash;
    memcpy(output32x16 + 32*15, (void*)hash, 32);
    
}