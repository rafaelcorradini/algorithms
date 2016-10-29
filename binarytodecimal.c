#include <stdio.h>

int binaryToDecimalIt(int b) {
	int d = 0;
	int count = 1;

	while(b > 0) {
		d = d + (b%2)*count;
		b /= 10;	
		count = count*2;
	}

	return d;
}

int binaryToDecimalRec(int b, int count) {
	int d = 0;

	if(b == 0)
		return d;
	else 
		return (d + (b%2)*count) + binaryToDecimalRec(b/10, count*2);
}

int main() {
	int b[100], i = 0;

	while(b[i] != 7) {
		scanf("%d", &b[i]);
		printf("%c\n", binaryToDecimalIt(b[i++]));
	}
	
	
	// printf("%d\n", binaryToDecimalRec(b, 1));
}