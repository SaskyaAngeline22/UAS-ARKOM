#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long long parallel_sum(long long *data, long long n, int threads) {
    long long sum = 0;
    omp_set_num_threads(threads);

    #pragma omp parallel for reduction(+:sum)
    for (long long i = 0; i < n; i++) {
        sum += data[i];
    }

    return sum;
}

int main(int argc, char *argv[]) {
    long long n = 10000000;
    int threads = 4;

    if (argc >= 2) {
        n = atoll(argv[1]);
    }
    if (argc >= 3) {
        threads = atoi(argv[2]);
        if (threads <= 0) {
            threads = 4;
        }
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
    long long sum = parallel_sum(data, n, threads);
    double end = omp_get_wtime();

    printf("Jumlah Bilangan : %lld\n\n", n);
    printf("Parallel:\n");
    printf("Jumlah thread = %d\n", threads);
    printf("Hasil = %lld\n", sum);
    printf("Waktu = %.6f detik\n", end - start);

    free(data);
    return 0;
}
