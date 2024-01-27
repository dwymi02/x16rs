#ifndef X16RX_MAIN_CL
#define X16RX_MAIN_CL

#include "util.cl"
#include "sha3_256.cl"
#include "x16rs.cl"

void hash_x16rs_choice_step(hash_t* stephash){

	uint8_t algo = stephash->h4[7] % 16;

	if(algo == 0){ hash_x16rs_func_0 ( stephash ); }
	if(algo == 1){ hash_x16rs_func_1 ( stephash ); }
	if(algo == 2){ hash_x16rs_func_2 ( stephash ); }
	if(algo == 3){ hash_x16rs_func_3 ( stephash ); }
	if(algo == 4){ hash_x16rs_func_4 ( stephash ); }
	if(algo == 5){ hash_x16rs_func_5 ( stephash ); }
	if(algo == 6){ hash_x16rs_func_6 ( stephash ); }
	if(algo == 7){ hash_x16rs_func_7 ( stephash ); }
	if(algo == 8){ hash_x16rs_func_8 ( stephash ); }
	if(algo == 9){ hash_x16rs_func_9 ( stephash ); }
	if(algo == 10){ hash_x16rs_func_10 ( stephash ); }
	if(algo == 11){ hash_x16rs_func_11 ( stephash ); }
	if(algo == 12){ hash_x16rs_func_12 ( stephash ); }
	if(algo == 13){ hash_x16rs_func_13 ( stephash ); }
	if(algo == 14){ hash_x16rs_func_14 ( stephash ); }
	if(algo == 15){ hash_x16rs_func_15 ( stephash ); }
}



// diff hx
int diff_big_hash(hash_t* src, hash_t* tar) {
	for(int i=0; i<32; i++) {
		if(src->h1[i] > tar->h1[i]){
			return 1;
		}else if(src->h1[i] < tar->h1[i]){
			return 0;
		}
	}
	return 0;
}
int diff_big_hash_local(__local hash_t* src, __local hash_t* tar) {
	for(int i=0; i<32; i++) {
		if(src->h1[i] > tar->h1[i]){
			return 1;
		}else if(src->h1[i] < tar->h1[i]){
			return 0;
		}
	}
	return 0;
}
int diff_big_hash_global(__global hash_t* src, __global hash_t* tar) {
	for(int i=0; i<32; i++) {
		if(src->h1[i] > tar->h1[i]){
			return 1;
		}else if(src->h1[i] < tar->h1[i]){
			return 0;
		}
	}
	return 0;
}

// x16rs hash miner 算法 V3
__kernel void miner_do_hash_x16rs_v3(
   __constant unsigned char* target_difficulty_hash_32,
   __constant unsigned char* input_stuff_89,
   const unsigned int   x16rs_repeat, // x16rs根据区块高度执行的次数
   const unsigned int   nonce_start, // nonce开始值
   const unsigned int   item_loop, // 单次执行循环次数，建议 20 ～ 100
   __global unsigned char* global_nonces,
   __global hash_32* global_results )
{
	// group_size
	unsigned int global_id = get_global_id(0);
	unsigned int local_id = get_local_id(0);
	unsigned int group_size = get_local_size(0);
	unsigned int group_quantity = get_global_size(0) / group_size;
	// const unsigned int group_size = 64;
	// const unsigned int group_quantity = 64;
	unsigned int group_id = global_id / group_size;

	// group results
	hash_t local_results_ret;
	unsigned int local_nonces_ret;

	__local hash_32 group_results[128];
	__local unsigned int group_nonces[128];

	// global results
	// __global hash_t global_results[group_quantity];
	// __global unsigned int global_nonces[group_quantity];

	// stuff copy
	unsigned char base_stuff[89];
	for(int i=0; i<89; i++){
		base_stuff[i] = input_stuff_89[i];
	}

	// do loop
	unsigned int nonce = nonce_start + (global_id * item_loop);

	for(unsigned loop=0; loop<item_loop; loop++){

		// insert nonce
		write_nonce_to_bytes(79, base_stuff, nonce);

		// hash results
		hash_t hxres;

		// hash 256
		sha3_256_hash(base_stuff, 89, hxres.h1);

		// hash x16rs
		for(int xr=0; xr < x16rs_repeat; xr++){
			hash_x16rs_choice_step(&hxres);
		}

		// smallest hx and nonce
		if(loop==0 || diff_big_hash(&local_results_ret, &hxres) == 1){
			local_results_ret = hxres;
			local_nonces_ret = nonce;
		}

		// next loop
		nonce = nonce + 1;
	}

	group_results[local_id] = cutout_hash_with_32(&local_results_ret);
	group_nonces[local_id] = local_nonces_ret;

	barrier(CLK_LOCAL_MEM_FENCE);

	// diff res hx & do reduction in shared memory
	unsigned int local_size = group_size;
	for(unsigned int smax = local_size >> 1; smax > 0; smax >>= 1)
	{
		if(local_id < smax) {
			if(diff_big_hash_local(&group_results[local_id], &group_results[local_id + smax]) == 1) {
				group_results[local_id] = group_results[local_id + smax];
				group_nonces[local_id] = group_nonces[local_id + smax];
			}
		}
		barrier(CLK_LOCAL_MEM_FENCE);
	}

	if(local_id == 0) {
		global_results[group_id] = group_results[0];
		// global_nonces[group_id] = group_nonces[0];
		write_nonce_to_global_bytes(group_id * 4, global_nonces, group_nonces[0]);
	}
}
#endif // X16RX_MAIN_CL