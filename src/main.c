#include "host.h"

int main (int argc, char *argv[]){
	int option = 0;
	int ROW_A = VEC_LENG, COL_A = VEC_LENG, COL_B = VEC_LENG;

	if( argc < 2 ){
		printf(ANSI_COLOR_RED);
		printf("[ERR] you must INPUT ./opencl [number]\n");
		printf(ANSI_COLOR_RESET);
		exit(0);
	}
	
	option = atoi(argv[1]);
	float *A = (float *)malloc(sizeof(float) *ROW_A*COL_A);
	float *B = (float *)malloc(sizeof(float) *COL_A*COL_B);
	float *C = (float *)malloc(sizeof(float) *ROW_A*COL_B);

	for(int i = 0; i < ROW_A*COL_A; i++){
		A[i] = rand() % 100;
	}
	for(int j = 0; j < COL_A*COL_B; j++){
		B[j] = rand() % 100;
	}
	
	if( option == 0 ){
		NOTICE("Sequential version...");
		double start_time = get_time();
		mat_mul_seq(A, B, C, ROW_A, COL_A, COL_B);
		double end_time = get_time();
		printf("Elapsed time:\t%f sec\n", end_time - start_time);
	} else if ( option == 1 ) {
		NOTICE("OpenCL version...");
		double start_time = get_time();
		mat_mul_opencl(A, B, C, ROW_A, COL_A, COL_B);
		double end_time = get_time();
		printf("Elapsed time (including initialization): %f sec\n", end_time - start_time);
	}

//	for(int k = 0; k < ROW_A *COL_B; k++){
//		printf("C[%d] : %f\n", k, C[k]);
//	}

	free(A);
	free(B);
	free(C);
	NOTICE("Finish Program!");
	return 0;
}
