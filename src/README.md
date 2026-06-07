# Implementasi Parallel Computing Menggunakan OpenMP pada Penjumlahan Bilangan

## Nama Penyusun
[Nama Anda]

## Deskripsi Proyek
Proyek ini membandingkan performa penjumlahan bilangan secara sequential dan parallel menggunakan OpenMP. Tujuan utamanya adalah melihat perbedaan waktu eksekusi, menghitung speedup, dan mengevaluasi efisiensi parallel computing.

## Tujuan
- Mengimplementasikan penjumlahan bilangan secara sequential dan parallel.
- Mengukur waktu eksekusi kedua implementasi.
- Menghitung speedup dan efisiensi dari eksekusi parallel.
- Menyajikan hasil dalam laporan yang siap dipresentasikan.

## Fitur Sistem
- Implementasi penjumlahan bilangan sequential.
- Implementasi penjumlahan bilangan parallel menggunakan OpenMP.
- Benchmark untuk tiga ukuran data: 100.000, 1.000.000, dan 10.000.000.
- Perhitungan speedup dan efisiensi.
- Ringkasan hasil dan analisis performa.

## Struktur Folder
```
project-arkom/
│
├── src/
│   ├── sequential.c
│   ├── parallel.c
│   ├── benchmark.c
│   └── Makefile
│
├── docs/
│   ├── laporan.pdf
│   ├── flowchart.png
│   ├── input_output.png
│   └── analisis_performa.md
│
├── test/
│   ├── hasil_uji_100000.txt
│   ├── hasil_uji_1000000.txt
│   └── hasil_uji_10000000.txt
│
└── README.md
```

## Cara Compile
Buka terminal, masuk ke folder `src`, lalu jalankan:

```bash
gcc -fopenmp sequential.c -o sequential
gcc -fopenmp parallel.c -o parallel
gcc -fopenmp benchmark.c -o benchmark
```

Atau gunakan `make`:

```bash
cd src
make
```

## Cara Menjalankan
Dari folder `src`:

```bash
./sequential
./parallel
./benchmark
```

Untuk menjalankan dengan N dan jumlah thread khusus:

```bash
./sequential 1000000
./parallel 1000000 4
./benchmark 4
```

## Penjelasan Kode
- `sequential.c` menghitung jumlah N bilangan menggunakan satu thread dan `omp_get_wtime()` untuk mengukur waktu.
- `parallel.c` menghitung jumlah N bilangan menggunakan OpenMP dengan `#pragma omp parallel for reduction(+:sum)` dan `omp_set_num_threads()`.
- `benchmark.c` menjalankan ketiga ukuran data, mencatat waktu sequential dan parallel, serta menghitung speedup dan efisiensi.

## Hasil Benchmark
Hasil benchmark akan ditampilkan pada output ketika menjalankan `./benchmark`.

## Tabel Perbandingan Sequential vs Parallel
Tabel perbandingan dapat ditemukan di laporan dan file hasil uji.

## Perhitungan Speedup
Speedup dihitung menggunakan rumus:
```
Speedup = Waktu Sequential / Waktu Parallel
```

## Perhitungan Efisiensi
Efisiensi dihitung menggunakan rumus:
```
Efisiensi = (Speedup / Jumlah Thread) × 100%
```

## Kesimpulan
Implementasi ini menunjukkan bagaimana OpenMP dapat meningkatkan performa penjumlahan bilangan untuk ukuran data besar, dengan catatan bahwa speedup bergantung pada jumlah thread, overhead, dan karakteristik perangkat keras.

## Kendala yang Ditemui
- Overhead pembuatan thread dapat mempengaruhi hasil pada ukuran data kecil.
- Bottleneck memori dan load imbalance dapat membuat speedup tidak linier.

## Link Video YouTube
[Link Video Presentasi](https://youtu.be/placeholder)
