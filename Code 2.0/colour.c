#include "qdbmp_1.0.0/qdbmp.h"
#include "stdio.h"
#include "stdlib.h"

void recolour_crystal(BMP* file, int x, int y, int r, int g, int b);
int black_checker(BMP* bmp, int x, int y);

//for just one crystal atm
//from the highest pixel, colour that crystal, go right until black, note the pixel, go left until no more, go back, go right until no more, go back to middle, repeat
//from the lowest pixel, colour that then keep going up until it hits the colour its trying to colour.
void recolour_crystal(BMP* file, int x, int y, int r, int g, int b) {

	int gucci = 1;
	int x_temp = x;
	int x_temp2 = x;
	int y_temp = y;

	//go down
	while(gucci == 1) {
		while(black_checker(file, x, y) != 1) {
			BMP_SetPixelRGB(file, x, y,  r, g, b);
			x++;
		}

		x = x_temp;

		while(black_checker(file, x, y) != 1) {
			BMP_SetPixelRGB(file, x, y,  r, g, b);
			x--;
		}
		x++;
		gucci = 0;
		while(black_checker(file, x, y) != 1) {
			if(black_checker(file, x, y+1) != 1) {
				gucci = 1;
				x_temp = x;
				break;
			}
			x++;
		}
		if(gucci == 0) break;
		else y++;
	}

	gucci = 1; x = x_temp2; x_temp = x_temp2;
	//goes up
	while(gucci == 1) {
		while(black_checker(file, x, y) != 1) {
			BMP_SetPixelRGB(file, x, y,  r, g, b);
			x++;
		}

		x = x_temp;

		while(black_checker(file, x, y) != 1) {
			BMP_SetPixelRGB(file, x, y,  r, g, b);
			x--;
		}
		x++;
		gucci = 0;
		while(black_checker(file, x, y) != 1) {
			if(black_checker(file, x, y-1) != 1) {
				gucci = 1;
				x_temp = x;
				break;
			}
			x++;
		}
		if(gucci == 0) break;
		else y--;
	}

}

int black_checker(BMP* bmp, int x, int y) {
	UCHAR r, g, b;
	BMP_GetPixelRGB(bmp, x , y, &r, &g, &b);
	if(r == 0 && g == 0 && b == 0) return 1;
	else return 0;
}



/*
int main(int argc, char* argv[]) {
	char *p = "tester.bmp";
printf("%s\n", p);

	BMP* image = BMP_ReadFile("tester.bmp");


	BMP* copy = malloc(sizeof(image));
	copy = image;
	recolour_crystal(copy);
printf("%s\n", p);

	BMP_WriteFile(copy, p);
printf("%s\n", p);

	return EXIT_SUCCESS;
}
*/
