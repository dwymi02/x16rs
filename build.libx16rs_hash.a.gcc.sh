﻿
gcc -c x16rs.c sha3/blake.c sha3/bmw.c sha3/groestl.c sha3/jh.c sha3/keccak.c sha3/skein.c sha3/cubehash.c sha3/echo.c sha3/luffa.c sha3/simd.c sha3/hamsi.c sha3/hamsi_helper.c sha3/fugue.c sha3/shavite.c sha3/shabal.c sha3/whirlpool.c sha3/sha2big.c sha3_256/sha3.c

ar rcs libx16rs_hash.a x16rs.o blake.o bmw.o groestl.o jh.o keccak.o skein.o cubehash.o echo.o luffa.o simd.o hamsi.o hamsi_helper.o fugue.o shavite.o shabal.o whirlpool.o sha2big.o sha3.o

rm -f *.o



###
## go build -ldflags '-w -s' -o miner_pool_worker_2019_07_24.exe  github.com/hacash/x16rs/pool/main/





