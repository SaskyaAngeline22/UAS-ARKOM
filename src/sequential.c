#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long long sequential_sum(long long *data, long long n) {
    long long sum = 0;
    for (long long i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    long long n = 10000000;
    if (argc >= 2) {
        n = atoll(argv[1]);
    }

    long long *data = malloc(sizeof(long long) * n);
    if (!data) {
        fprintf(stderr, "Gagal alokasi memori untuk %lld elemen\n", n);
        return 1;
    }

    for (long long i = 0; i < n; i++) {
        data[i] = i + 1;
    }

    double start = omp_get_wtime();
    long long sum = sequential_sum(data, n);
    double end = omp_get_wtime();

    printf("Jumlah Bilangan : %lld\n\n", n);
    printf("Sequential:\n");
    printf("Hasil = %lld\n", sum);
    printf("Waktu = %.6f detik\n", end - start);

    free(data);
    return 0;
}
