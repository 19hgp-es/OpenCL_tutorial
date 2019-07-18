#include "main.h"


__kernel void maskCalculate(__global){
	const int x = get_global_id(0);
	const int y = get_global_id(1);

	// check target pixel

	// cross mask matrix with selected pixels
	for(int i=-1; i<=1; ++i){
		for(int j=-1; j<=1; ++j){
			// calculate part
		}
	}
	// initialize output image

}
