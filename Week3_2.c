#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int n) {
    int F[2] = { 0, 1 };
    int result;
    for (int i = 2; i <= n; i++) {
        result = (F[0] + F[1]) % 1234567;
        F[0] = F[1] % 1234567;
        F[1] = result % 1234567;
    }
    return result;
}

int main(void) {
	
	int N;
	scanf("%d", &N);

    printf("%d", solution(N));
}