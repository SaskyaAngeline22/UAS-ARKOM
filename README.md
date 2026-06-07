# Implementasi Parallel Computing Menggunakan OpenMP pada Penjumlahan Bilangan

## Nama Penyusun
Aulia Suci Firmadhani (25032014004)
Saskya Angeline Yunina Kristy (25032014028)
Raihana Ayla Azzahra (25032014077)

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

### sequential.c
Program ini mengimplementasikan penjumlahan bilangan secara **sequential** (berurutan):
- Menerima parameter N (jumlah bilangan) dari command line
- Mengalokasikan array untuk menyimpan bilangan 1 hingga N
- Menggunakan satu loop sederhana untuk menjumlahkan seluruh array
- Menggunakan `omp_get_wtime()` untuk mengukur waktu eksekusi dengan presisi tinggi
- Output menampilkan jumlah bilangan, hasil penjumlahan, dan waktu eksekusi

Kode utama:
```c
long long sum = 0;
for (long long i = 0; i < n; i++) {
    sum += data[i];
}
```

### parallel.c
Program ini mengimplementasikan penjumlahan bilangan secara **parallel** menggunakan OpenMP:
- Menerima parameter N (jumlah bilangan) dan jumlah thread
- Mengalokasikan array untuk menyimpan bilangan 1 hingga N
- Menggunakan `omp_set_num_threads()` untuk mengatur jumlah thread
- Menggunakan `#pragma omp parallel for reduction(+:sum)` untuk paralelisasi
- Setiap thread memproses sebagian dari array secara bersamaan
- Hasil partial sum dari setiap thread digabungkan dengan **reduction operator**
- Mengukur waktu eksekusi dengan `omp_get_wtime()`

Kode utama:
```c
long long sum = 0;
omp_set_num_threads(threads);
#pragma omp parallel for reduction(+:sum)
for (long long i = 0; i < n; i++) {
    sum += data[i];
}
```

### benchmark.c
Program ini menjalankan **benchmark lengkap** untuk membandingkan performa sequential dan parallel:
- Menguji dengan 3 ukuran data: 100.000, 1.000.000, dan 10.000.000 bilangan
- Untuk data kecil (100.000): mengulangi 20 kali untuk mendapatkan pengukuran yang stabil
- Untuk data medium (1.000.000): mengulangi 10 kali
- Untuk data besar (10.000.000): mengulangi 3 kali
- Mengukur waktu rata-rata untuk setiap implementasi
- Menghitung speedup dan efisiensi
- Menampilkan hasil dalam format tabel yang mudah dibaca

## Hasil Benchmark

### Output Lengkap Program
Ketika menjalankan `./benchmark 4`, output yang dihasilkan adalah:

```
Benchmark Penjumlahan Bilangan OpenMP
Jumlah thread = 4

==============================
Jumlah Bilangan : 100000
Hasil sequential = 5000050000
Hasil parallel   = 5000050000
Waktu sequential = 0.000350 detik
Waktu parallel   = 0.000400 detik
Speedup = 0.88x
Efisiensi = 21.88%
==============================

==============================
Jumlah Bilangan : 1000000
Hasil sequential = 500000500000
Hasil parallel   = 500000500000
Waktu sequential = 0.003700 detik
Waktu parallel   = 0.001100 detik
Speedup = 3.36x
Efisiensi = 84.09%
==============================

==============================
Jumlah Bilangan : 10000000
Hasil sequential = 50000005000000
Hasil parallel   = 50000005000000
Waktu sequential = 0.024667 detik
Waktu parallel   = 0.006000 detik
Speedup = 4.11x
Efisiensi = 102.78%
==============================
```

### Penjelasan Output

**Untuk N = 100.000:**
- Hasil: Kedua implementasi menghasilkan nilai yang sama (5.000.050.000)
- Waktu sequential: 0.000350 detik
- Waktu parallel: 0.000400 detik
- Speedup: 0.88x (parallel lebih lambat)
- **Penjelasan**: Untuk data kecil, overhead pembuatan thread dan synchronization lebih besar dari manfaat paralelisasi. Thread creation cost dan management overhead menyebabkan parallel lebih lambat dari sequential.

**Untuk N = 1.000.000:**
- Hasil: Kedua implementasi menghasilkan nilai yang sama (500.000.500.000)
- Waktu sequential: 0.003700 detik
- Waktu parallel: 0.001100 detik
- Speedup: 3.36x (parallel 3.36 kali lebih cepat)
- **Penjelasan**: Ukuran data sudah cukup besar sehingga overhead thread dapat diamortisasi. Keuntungan paralelisasi mulai terlihat dengan peningkatan performa yang signifikan.

**Untuk N = 10.000.000:**
- Hasil: Kedua implementasi menghasilkan nilai yang sama (50.000.005.000.000)
- Waktu sequential: 0.024667 detik
- Waktu parallel: 0.006000 detik
- Speedup: 4.11x (parallel 4.11 kali lebih cepat)
- **Penjelasan**: Beban kerja sangat besar, sehingga distribusi ke 4 thread memberikan keuntungan maksimal. Speedup mendekati nilai ideal (4x untuk 4 thread), menunjukkan load balancing yang baik.

## Tabel Perbandingan Sequential vs Parallel

| N Bilangan | Sequential (detik) | Parallel 4T (detik) | Speedup | Efisiensi |
|---|---|---|---|---|
| 100.000 | 0.000350 | 0.000400 | 0.88x | 21.88% |
| 1.000.000 | 0.003700 | 0.001100 | 3.36x | 84.09% |
| 10.000.000 | 0.024667 | 0.006000 | 4.11x | 102.78% |

### Interpretasi Tabel
- **Sequential time semakin meningkat** seiring dengan bertambahnya jumlah bilangan
- **Parallel time juga meningkat** tetapi dengan laju yang lebih lambat
- **Speedup meningkat** dari 0.88x ke 4.11x seiring bertambahnya ukuran data
- **Efisiensi meningkat** dari 21.88% ke 102.78%

## Perhitungan Speedup

### Rumus Speedup
```
Speedup = Waktu Sequential / Waktu Parallel
```

### Perhitungan Detail

**N = 100.000:**
```
Speedup = 0.000350 / 0.000400 = 0.875 ≈ 0.88x
```

**N = 1.000.000:**
```
Speedup = 0.003700 / 0.001100 = 3.364 ≈ 3.36x
```

**N = 10.000.000:**
```
Speedup = 0.024667 / 0.006000 = 4.111 ≈ 4.11x
```

### Analisis Speedup
- **Speedup < 1** pada data kecil menunjukkan parallel overhead lebih dominan
- **Speedup meningkat** mendekati jumlah thread (4) seiring pertumbuhan data
- **Speedup > 4** pada data besar (102.78%) mungkin disebabkan:
  - Caching effect yang lebih baik dengan distribusi load
  - Pola akses memori yang lebih optimal
  - Pengurangan cache miss rate

## Perhitungan Efisiensi

### Rumus Efisiensi
```
Efisiensi = (Speedup / Jumlah Thread) × 100%
```

### Perhitungan Detail

**N = 100.000:**
```
Efisiensi = (0.88 / 4) × 100% = 21.88%
```
Artinya: Hanya 21.88% dari kapasitas parallel yang dimanfaatkan.

**N = 1.000.000:**
```
Efisiensi = (3.36 / 4) × 100% = 84.09%
```
Artinya: 84.09% dari kapasitas parallel sudah dimanfaatkan, hampir optimal.

**N = 10.000.000:**
```
Efisiensi = (4.11 / 4) × 100% = 102.78%
```
Artinya: Efisiensi melebihi 100%, menunjukkan super-linear speedup (kemungkinan karena caching behavior yang lebih baik).

## Analisis Teori Lengkap

### Pengertian Parallel Computing
Parallel computing adalah teknik pemrosesan data di mana beberapa operasi dijalankan secara bersamaan pada beberapa prosesor atau core untuk mempercepat waktu eksekusi keseluruhan. Dalam konteks proyek ini, kami menggunakan shared-memory parallelism dengan OpenMP.

### Konsep Thread
Thread adalah unit eksekusi terkecil dalam program yang dapat dijalankan secara independen. Setiap thread:
- Memiliki stack sendiri
- Berbagi memori global (heap) dengan thread lain
- Dapat dijalankan secara concurrent pada core berbeda
- Memerlukan overhead untuk pembuatan dan synchronization

Dalam OpenMP, thread diatur oleh runtime library dan dapat dikonfigurasi jumlahnya melalui `omp_set_num_threads()`.

### Konsep Shared Memory
Model shared memory memungkinkan semua thread mengakses ruang memori yang sama secara langsung. Keuntungan:
- Komunikasi antar thread cepat (tidak perlu message passing)
- Sinkronisasi lebih mudah

Tantangan:
- Race condition jika tidak ada synchronization
- Memory bottleneck jika terlalu banyak akses ke memory yang sama
- Cache coherency overhead

### OpenMP Memory Model
OpenMP mengikuti model memori flush-based:
- Variabel dapat bersifat **shared** (diakses semua thread) atau **private** (setiap thread punya copy)
- Implicit barriers untuk sinkronisasi
- Critical sections untuk melindungi akses concurrent
- Reduction operations untuk menggabungkan hasil dari thread

### Fungsi `#pragma omp parallel for`
Directive ini:
- Membagi iterasi loop ke beberapa thread
- Setiap thread mengerjakan sebagian dari iterasi
- Implicit barrier di akhir directive (semua thread tunggu sampai selesai)
- Dapat dikombinasikan dengan `reduction` untuk aggregasi hasil

### Fungsi Reduction
`reduction(+:sum)` pada proyek ini:
- Setiap thread memiliki **local copy** dari `sum`
- Thread mengumpulkan hasil ke local copy-nya
- Setelah semua thread selesai, hasil dari semua thread **dikombinasikan** menggunakan operator (+)
- Hasilnya disimpan ke `sum` utama (shared variable)

Operator yang didukung: +, -, *, /, &, |, ^, &&, ||, min, max

### Perbedaan Sequential dan Parallel

| Aspek | Sequential | Parallel |
|---|---|---|
| Jumlah thread | 1 | N (bisa 2, 4, 8, dst) |
| Overhead | Minimal | Ada (thread creation, synchronization) |
| Ideal untuk | Data kecil, algoritma sederhana | Data besar, operasi berulang |
| Synchronization | Tidak perlu | Perlu (barrier, critical sections) |
| Memory access | Sederhana | Kompleks (cache coherency) |
| Scalability | Terbatas | Dapat meningkat dengan jumlah core |

### Faktor Penyebab Speedup Tidak Linier

#### 1. Overhead Thread Creation
- Pembuatan thread memerlukan alokasi stack dan inisialisasi context (~1-10 microseconds per thread)
- Untuk operasi cepat, overhead ini signifikan
- Pada data kecil (100.000), overhead lebih besar dari beban kerja

#### 2. Synchronization Cost
- Implicit barrier di akhir `parallel for` memerlukan synchronization point
- Jika thread selesai di waktu berbeda, thread yang selesai lebih cepat harus menunggu
- Cost synchronization bisa mencapai microseconds hingga milliseconds

#### 3. Memory Bottleneck
- L3 cache memiliki bandwidth terbatas
- Jika semua thread mengakses memori sama, terjadi bottleneck
- Memory contention menyebabkan cache miss yang lebih banyak
- Bandwidth memori (memory bandwidth) menjadi limiting factor

#### 4. Load Imbalance
- Jika beban kerja tidak terbagi merata antar thread, ada thread yang idle
- Pada data 100.000 dengan 4 thread, beban per thread sangat kecil
- Beberapa thread selesai lebih cepat dan menunggu di barrier

#### 5. Cache Locality
- Data yang diakses oleh satu thread idealnya ada di cache lokal (L1/L2)
- Jika data tersebar di banyak line cache, cache miss meningkat
- Parallel version bisa menurunkan cache locality

### Kenapa Data Besar Lebih Untung
- **Ratio komputasi/overhead besar**: Waktu komputasi >> overhead thread creation
- **Load balancing lebih baik**: Beban kerja per thread cukup besar untuk amortisasi overhead
- **Cache efficiency**: Ukuran working set per thread lebih sesuai dengan L2/L3 cache

## Hasil Uji Lengkap

Hasil uji dari berbagai ukuran data tersimpan di folder `test/`:

- [hasil_uji_100000.txt](test/hasil_uji_100000.txt) - Hasil uji untuk 100.000 bilangan
- [hasil_uji_1000000.txt](test/hasil_uji_1000000.txt) - Hasil uji untuk 1.000.000 bilangan
- [hasil_uji_10000000.txt](test/hasil_uji_10000000.txt) - Hasil uji untuk 10.000.000 bilangan

## Kesimpulan

Implementasi parallel computing menggunakan OpenMP untuk penjumlahan bilangan menunjukkan hasil yang sesuai dengan teori:

1. **Untuk data kecil (100.000)**: Sequential lebih efisien karena overhead thread > manfaat paralelisasi
2. **Untuk data medium (1.000.000)**: Parallel mulai memberikan keuntungan (3.36x speedup)
3. **Untuk data besar (10.000.000)**: Parallel memberikan speedup optimal (4.11x dengan 4 thread)
4. **Efisiensi meningkat** seiring dengan pertumbuhan data, menunjukkan amortisasi overhead yang lebih baik
5. **Super-linear speedup** pada data terbesar kemungkinan karena cache behavior yang lebih baik

## Kendala yang Ditemui

1. **Overhead thread creation**: Waktu pembuatan thread mengurangi keuntungan pada data kecil
2. **Synchronization cost**: Implicit barrier di akhir directive memerlukan waktu synchronization
3. **Memory bottleneck**: Jika semua thread mengakses memori yang sama, bandwidth memori menjadi limiting factor
4. **Load imbalance**: Distribusi beban kerja tidak selalu merata antar thread
5. **Cache coherency**: Mempertahankan konsistensi cache antar core memerlukan overhead

## Rekomendasi Optimisasi

1. **Gunakan `schedule(dynamic)` atau `schedule(guided)`** untuk load balancing lebih baik
2. **Increase problem size** untuk mengurangi overhead relative
3. **Use multiple parallel regions** untuk menghindari synchronization berlebihan
4. **Consider NUMA effects** jika menjalankan pada multi-socket system
5. **Profile dengan tools seperti likwid atau perf** untuk mengidentifikasi bottleneck

## Link Video YouTube
[Link Video Presentasi](https://youtu.be/s7VcrmTGKcI?si=qZv5o0fldkO9CdN3)
