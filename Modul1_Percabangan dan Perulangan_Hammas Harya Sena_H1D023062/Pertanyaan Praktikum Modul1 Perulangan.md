Bagian 1.6.4: Perulangan

**1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!**

<img width="661" height="380" alt="Image" src="https://github.com/user-attachments/assets/09e3fdfe-26d6-4f0d-a18e-6974399fc151" />

**2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!**
   Efek tersebut dihasilkan dari struktur perulangan increment (penambahan). Menggunakan perintah for (int ledPin = 2; ledPin < 8; ledPin++), program memulai perulangan dari pin terkecil (pin 2). Di dalam blok perulangan tersebut, instruksi untuk menyalakan dan mematikan LED dijalankan. Adanya perintah ledPin++ memaksa sistem beralih mengeksekusi pin sebelahnya (pin 3, lalu pin 4, dst) pada iterasi berikutnya, menghasilkan ilusi cahaya berpindah ke kanan.

**3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!**
   Sistem menggunakan struktur perulangan decrement (pengurangan) untuk membalik arah. Dengan perintah for (int ledPin = 7; ledPin >= 2; ledPin--), prosesnya sama seperti sebelumnya, namun kali ini program diperintahkan mengeksekusinya mundur. Dimulai dari batas pin tertinggi (pin 7) dan variabel ledPin terus dikurangi satu angka setiap putaran hingga mencapai pin terendah (pin 2).

**4. Modifikasi Program Perulangan (3 LED Kiri dan 3 LED Kanan Bergantian)**

_Source Code:_

```cpp
int timer = 500; // Menentukan durasi nyala LED (0.5 detik)

void setup() {
  // Melakukan inisialisasi pin 2 sampai 7 sebagai OUTPUT menggunakan perulangan
  for (int ledPin = 2; ledPin <= 7; ledPin++) {
    pinMode(ledPin, OUTPUT); // Mengatur setiap pin menjadi mode output
  }
}

void loop() {
  // --- MENYALAKAN 3 LED KIRI (Pin 2, 3, 4) ---
  for (int ledPin = 2; ledPin <= 4; ledPin++) {
    digitalWrite(ledPin, HIGH); // Memberi tegangan (nyala) pada LED kiri
  }
  delay(timer);                 // Menahan 3 LED kiri tetap menyala
  
  for (int ledPin = 2; ledPin <= 4; ledPin++) {
    digitalWrite(ledPin, LOW);  // Memutus tegangan (mati) pada LED kiri
  }

  // --- MENYALAKAN 3 LED KANAN (Pin 5, 6, 7) ---
  for (int ledPin = 5; ledPin <= 7; ledPin++) {
    digitalWrite(ledPin, HIGH); // Memberi tegangan (nyala) pada LED kanan
  }
  delay(timer);                 // Menahan 3 LED kanan tetap menyala
  
  for (int ledPin = 5; ledPin <= 7; ledPin++) {
    digitalWrite(ledPin, LOW);  // Memutus tegangan (mati) pada LED kanan
  }
}
```
- "int timer = 500;" Membuat variabel bernama timer dengan tipe data integer (angka bulat). Angka 500 berarti 500 milidetik (0,5 detik). Variabel ini akan menentukan seberapa lama LED menyala sebelum berganti posisi.
- "void setup()" Fungsi yang hanya dijalankan satu kali saat Arduino pertama kali dinyalakan.
- "for (int ledPin = 2; ledPin <= 7; ledPin++)" Sebuah perulangan yang dimulai dari angka 2 hingga 7. Ini cara cepat untuk mengatur banyak pin sekaligus.
- "pinMode(ledPin, OUTPUT)" Mengatur setiap nomor pin (2, 3, 4, 5, 6, 7) agar berfungsi sebagai Output (mengeluarkan listrik untuk menyalakan LED).
- "for (int ledPin = 2; ledPin <= 4; ledPin++)" Mengakses pin 2, 3, dan 4 secara berurutan.
- "digitalWrite(ledPin, HIGH)" Mengirim sinyal listrik (HIGH) ke pin tersebut. Karena tidak ada delay di dalam kurung kurawal ini, ketiga LED akan terlihat menyala bersamaan.
- "delay(timer)" Menghentikan program selama 500ms. Selama waktu ini, grup kiri tetap menyala.
- "digitalWrite(ledPin, LOW)" Memutus aliran listrik ke pin 2, 3, dan 4 sehingga ketiga LED kiri mati.
