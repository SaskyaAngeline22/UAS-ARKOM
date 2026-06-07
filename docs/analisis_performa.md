# Analisis Performa

## Pengertian Parallel Computing
Parallel computing adalah teknik pemrosesan di mana beberapa tugas atau perhitungan dijalankan secara bersamaan pada beberapa prosesor atau thread untuk mempercepat waktu eksekusi.

## Konsep Thread
Thread adalah unit eksekusi terkecil dalam program yang dapat dijalankan secara bersamaan. Dalam OpenMP, thread digunakan untuk membagi pekerjaan dalam loop atau area paralel.

## Konsep Shared Memory
Shared memory adalah model memori di mana beberapa thread dapat mengakses ruang memori yang sama secara langsung. Setiap thread dapat membaca dan menulis data yang berada di memori bersama.

## OpenMP Memory Model
Model memori OpenMP mendefinisikan bagaimana variabel diperlakukan di area paralel. Variabel dapat bersifat shared atau private, dan OpenMP mengatur sinkronisasi untuk memastikan konsistensi data.

## Fungsi pragma omp parallel for
`#pragma omp parallel for` digunakan untuk mendistribusikan iterasi loop ke beberapa thread secara paralel. Setiap thread mengeksekusi bagian dari loop sehingga pekerjaan dapat diselesaikan lebih cepat.

## Fungsi reduction
Kata kunci `reduction(+:sum)` memberitahu OpenMP untuk melakukan pengurangan yang aman antara nilai partial sum dari setiap thread. Setiap thread menghitung subtotal, lalu OpenMP menggabungkannya menjadi nilai akhir.

## Perbedaan Sequential dan Parallel
- Sequential: eksekusi dilakukan oleh satu unit eksekusi. Cocok untuk data kecil dan logika sederhana.
- Parallel: eksekusi dibagi ke beberapa thread. Cocok untuk tugas besar dan komputasi intensif.

## Faktor yang Menyebabkan Speedup Tidak Linier
### Overhead thread creation
Membuat dan mengelola thread memerlukan waktu tambahan. Untuk ukuran data kecil, overhead ini dapat mengurangi manfaat parallel.

### Synchronization cost
Sinkronisasi antara thread, seperti penggabungan hasil reduction, memerlukan waktu tambahan.

### Memory bottleneck
Jika semua thread mengakses memori bersama secara intensif, batasan bandwidth memori dapat menjadi penghambat.

### Load imbalance
Jika beban kerja tidak terbagi merata antara thread, beberapa thread dapat menunggu thread lain selesai, sehingga efisiensi menurun.

## Rumus Analisis
- Speedup = Waktu Sequential / Waktu Parallel
- Efisiensi = (Speedup / Jumlah Thread) × 100%

## Kesimpulan Analisis
Benchmark menunjukkan bahwa parallel computing dapat meningkatkan performa pada ukuran data besar, tetapi keuntungan tergantung pada jumlah thread, overhead, dan karakteristik memori. Implementasi OpenMP bekerja lebih baik saat beban kerja cukup besar untuk mengompensasi overhead thread.
