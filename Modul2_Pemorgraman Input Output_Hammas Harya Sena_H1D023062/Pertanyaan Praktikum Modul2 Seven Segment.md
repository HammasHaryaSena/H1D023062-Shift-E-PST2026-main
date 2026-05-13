Bagian 2.5.4: Seven Segment

**1. Gambarkan rangkaian schematic yang digunakan pada percobaan!**

<img width="661" height="380" alt="Image" src="https://github.com/user-attachments/assets/09e3fdfe-26d6-4f0d-a18e-6974399fc151" />

**2. Apa yang terjadi jika nilai `num` lebih dari 15?**
Apabila nilai variabel `num` melebihi 15, program akan mengalami _out of bounds array access_. Artinya, mikrokontroler dipaksa untuk membaca indeks memori di luar batas _array_ `digitPattern` yang hanya dideklarasikan hingga indeks ke-15. Akibatnya, data yang dikirim ke _Seven Segment_ berisi nilai acak/tidak terdefinisi, yang menyebabkan lampu segmen menyala dengan pola yang tidak beraturan (_glitch_) atau mati sama sekali.

**3.  Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasannya!**

Program ini menggunakan _Seven Segment_ bertipe **Common Anode**.
**Alasan:** Pada fungsi `displayDigit`, terdapat instruksi `digitalWrite(segmentPins[i], !digitPattern[num][i]);`. _Array_ pola diatur dengan angka `1` sebagai penanda nyala (karakteristik _Common Cathode_). Namun, sebelum sinyal dikirimkan, program menggunakan operator negasi (`!`) yang mengubah nilai `1` menjadi logika `0` (LOW). Karena LED segmen menyala ketika diberikan logika tegangan LOW (terhubung ke Ground), ini membuktikan bahwa titik bersama (_common_) pada komponen keras tersebut sudah terhubung secara konstan ke VCC (Anode).


**4. Modifikasi program agar tampilan berjalan dari F ke 0 dan berikan penjelasan disetiap baris kodenya**

_Source Code:_

```cpp
void loop() {
  for(int i = 15; i >= 0; i--) {
    displayDigit(i);
    delay(1000);
  }
}
```

Penjelasan baris kode :

void loop() { : Fungsi utama Arduino yang akan dieksekusi secara terus-menerus tanpa henti.

for(int i = 15; i >= 0; i--) { : Deklarasi perulangan. Variabel i diinisialisasi di angka 15 (representasi F). Perulangan akan terus berjalan selama kondisi i lebih besar atau sama dengan 0 (i >= 0). Setiap selesai satu siklus putaran, nilai i akan dikurangi satu (i--).

displayDigit(i); : Memanggil fungsi cetak untuk menyalakan Seven Segment sesuai dengan pola array pada indeks ke-i.

delay(1000); : Menghentikan sementara proses eksekusi mikrokontroler selama 1000 milidetik (1 detik) agar mata pengguna dapat melihat transisi angka dengan jelas.

} : Penutup blok perulangan for.

} : Penutup blok fungsi loop.