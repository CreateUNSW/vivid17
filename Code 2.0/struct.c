array = {1604,1286}
	{1609,1505}
	{1541,1596}
	{1595,1670}
	{1667,1618}
	{1739,1747}
	{1568,1770}
	{1565,1916}
	{1669,1864}
	{1753,1947}
	{1821,1862}
	{1887,1741}
	{2014,1837}
	{1932,1935}
	{2137,1933}
	{2312,1919}
	{2420,1890}
	{2536,1945}
	{2676,1925}
	{2598,1812}
	{2401,1758} //20
	{2417,1614}
	{2426,1502}
	{2578,1530}
	{2549,1667}
	{2687,1664}
	{2755,1541}
	{2914,1501}
	{2895,1658}
	{2754,1754}
	{2893,1808} //30
	{2879,1921}
	{1561,1163}
	{1721,1179}
	{1753,1290}
	{1680,1398}
	{1742,1514}
	{1807,1635}
	{1869,1534}
	{1806,1414}
	{














































#include "stdio.h"
#include "stdlib.h"


typedef struct pixels {
	int x;
	int y;
} pixels;

typedef struct pixels *Pixels;

Pixels new_pixel();

int main(int argc, char* argv[]) {
	Pixels a = new_pixel();

	

	printf("input x:\n");
	scanf("%d", &a[2].x);
	printf("input y:\n");
	scanf("%d", &a[3].y);
	
	printf("%d\n", a[2].x);
	printf("%d\n", a[3].y);
	return EXIT_SUCCESS;
}

Pixels new_pixel() {
	Pixels p;
	p = malloc(290*sizeof(pixels));
	return p;
}
