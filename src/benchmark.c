#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void fill_data(long long *data, long long n) {
    for (long long i = 0; i < n; i++) {
        data[i] = i + 1;
    }
}

long long sequential_sum(long long *data, long long n) {
    long long sum = 0;
    for (long long i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum;
}

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
    int threads = 4;
    if (argc >= 2) {
        threads = atoi(argv[1]);
        if (threads <= 0) {
            threads = 4;
        }
    }

    long long sizes[] = {100000, 1000000, 10000000};
    int count = sizeof(sizes) / sizeof(sizes[0]);

    printf("Benchmark Penjumlahan Bilangan OpenMP\n");
    printf("Jumlah thread = %d\n\n", threads);

    for (int i = 0; i < count; i++) {
        long long n = sizes[i];
        long long *data = malloc(sizeof(long long) * n);
        if (!data) {
            fprintf(stderr, "Gagal alokasi memori untuk %lld elemen\n", n);
            return 1;
        }

        fill_data(data, n);

        int repeat = (n <= 100000) ? 20 : (n <= 1000000) ? 10 : 3;
        long long sum_seq = 0;
        long long sum_par = 0;

        double start_seq = omp_get_wtime();
        for (int r = 0; r < repeat; r++) {
            sum_seq = sequential_sum(data, n);
        }
        double end_seq = omp_get_wtime();

        double start_par = omp_get_wtime();
        for (int r = 0; r < repeat; r++) {
            sum_par = parallel_sum(data, n, threads);
        }
        double end_par = omp_get_wtime();

        double time_seq = (end_seq - start_seq) / repeat;
        double time_par = (end_par - start_par) / repeat;
        double speedup = time_seq / time_par;
        double efficiency = (speedup / threads) * 100.0;

        printf("==============================\n");
        printf("Jumlah Bilangan : %lld\n", n);
        printf("Hasil sequential = %lld\n", sum_seq);
        printf("Hasil parallel   = %lld\n", sum_par);
        printf("Waktu sequential = %.6f detik\n", time_seq);
        printf("Waktu parallel   = %.6f detik\n", time_par);
        printf("Speedup = %.2fx\n", speedup);
        printf("Efisiensi = %.2f%%\n", efficiency);
        printf("==============================\n\n");

        free(data);
    }

    return 0;
}
