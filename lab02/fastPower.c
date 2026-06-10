
#include <stdio.h>
#include <stdlib.h>

long long fastPower(int a, int n);

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s <a> <n>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int a = 0;
	int n = 0;
	char c;
	if (sscanf(argv[1], "%d %c", &a, &c) != 1
			|| sscanf(argv[2], "%d %c", &n, &c) != 1) {
		fprintf(stderr, "error: invalid integer(s)\n");
		exit(EXIT_FAILURE);
	} else if (n < 0 || (a == 0 && n == 0)) {
		fprintf(stderr, "error: invalid integer(s)\n");
		exit(EXIT_FAILURE);
	}

	long long ans = fastPower(a, n);
	printf("%d^%d = %lld\n", a, n, ans);
	return 0;
}

// !!! DO NOT MODIFY THE CODE ABOVE !!!
////////////////////////////////////////////////////////////////////////
// Your task

// Returns a^n
long long fastPower(int a, int n) {
	if(n == 0) return 1;

	if (n % 2 == 1) {
		return a * fastPower(a, (n - 1) / 2) *fastPower(a, (n - 1) / 2);
	} else {
		return fastPower(a, (n) / 2) *fastPower(a, (n) / 2);
	}
}

