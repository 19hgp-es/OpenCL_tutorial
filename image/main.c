#include "main.h"

int main (int argc, char *argv[])
{
	int num = 0;
	unsigned char tt[60], buf[4], file[20];
	long Red, Green, Blue, None, pixel;
	FILE *fpr, *fpw;
	
	if( argc < 3 ){
		printf("[ERROR] Usage\t: %s <src file> <dest file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}	
	
	fpr = connectFile(argv[0], "rb");
	fpw = connectFile("output.bmp", "wb");
	
	fread(tt, 54, 1, fpr);
	fwrite(tt, 54, 1, fpw);

	//int image_width = *(int *)&tt[18];
	//int image_height = *(int *)&tt[22];

	while(fread(buf, 4, 1, fpr) != 0){
		num += 1;
	
		Red = (long)buf[2];
		Green = (long)buf[1];
		Blue = (long)buf[0];
		None = (long)buf[3];

		pixel = pixel_processing(Red, Green, Blue, None);
		fwrite(&pixel, 4, 1, fpw);
	}

	free(fpw);
	free(fpr);
	
	return 0;
}





