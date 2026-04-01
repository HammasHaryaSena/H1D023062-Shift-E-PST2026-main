Bagian 1.6.4: Perulangan

1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan!

(Catatan: Masukkan gambar/screenshot skematik 5 LED kamu di sini)

2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!
   Efek tersebut dihasilkan dari struktur perulangan increment (penambahan). Menggunakan perintah for (int ledPin = 2; ledPin < 8; ledPin++), program memulai perulangan dari pin terkecil (pin 2). Di dalam blok perulangan tersebut, instruksi untuk menyalakan dan mematikan LED dijalankan. Adanya perintah ledPin++ memaksa sistem beralih mengeksekusi pin sebelahnya (pin 3, lalu pin 4, dst) pada iterasi berikutnya, menghasilkan ilusi cahaya berpindah ke kanan.

3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!
   Sistem menggunakan struktur perulangan decrement (pengurangan) untuk membalik arah. Dengan perintah for (int ledPin = 7; ledPin >= 2; ledPin--), prosesnya sama seperti sebelumnya, namun kali ini program diperintahkan mengeksekusinya mundur. Dimulai dari batas pin tertinggi (pin 7) dan variabel ledPin terus dikurangi satu angka setiap putaran hingga mencapai pin terendah (pin 2).

4. Modifikasi Program Perulangan (3 LED Kiri dan 3 LED Kanan Bergantian)

Source Code:
int timer = 500;

void setup() {
for (int pin = 2; pin <= 7; pin++) {
pinMode(pin, OUTPUT);
}
}

void loop() {
// Fase 1: Kiri Nyala, Kanan Mati
for (int pin = 2; pin <= 4; pin++) {
digitalWrite(pin, HIGH);
}
for (int pin = 5; pin <= 7; pin++) {
digitalWrite(pin, LOW);
}
delay(timer);

    // Fase 2: Kiri Mati, Kanan Nyala
    for (int pin = 2; pin <= 4; pin++) {
        digitalWrite(pin, LOW);
    }
    for (int pin = 5; pin <= 7; pin++) {
        digitalWrite(pin, HIGH);
    }
    delay(timer);

}
Penjelasan Baris per Baris:

int timer = 500; : Mendeklarasikan variabel timer untuk menyimpan nilai jeda waktu perpindahan nyala LED sebesar 500 ms.

void setup() { : Fungsi inisialisasi awal mikrokontroler.

for (int pin = 2; pin <= 7; pin++) { : Melakukan perulangan dari angka 2 hingga 7. Variabel pin digunakan untuk mewakili nomor pin pada Arduino.

pinMode(pin, OUTPUT); : Mengatur setiap pin yang sedang diiterasi (pin 2, 3, 4, 5, 6, dan 7) sebagai jalur OUTPUT.

} : Menutup blok for pada setup.

} : Menutup blok fungsi setup().

void loop() { : Fungsi utama yang berjalan berulang tanpa batas.

for (int pin = 2; pin <= 4; pin++) { : Memulai perulangan khusus untuk kelompok 3 LED bagian kiri (terhubung ke pin 2, 3, dan 4).

digitalWrite(pin, HIGH); : Menyalakan LED yang berada pada kelompok kiri tersebut.

} : Menutup perulangan penyalaan LED kiri.

for (int pin = 5; pin <= 7; pin++) { : Memulai perulangan khusus untuk kelompok 3 LED bagian kanan (terhubung ke pin 5, 6, dan 7).

digitalWrite(pin, LOW); : Memastikan LED yang berada pada kelompok kanan dalam kondisi mati.

} : Menutup perulangan pematian LED kanan.

delay(timer); : Menahan eksekusi selama 500 ms agar konfigurasi "Kiri Nyala - Kanan Mati" dapat terlihat jelas.

for (int pin = 2; pin <= 4; pin++) { : Kembali melakukan iterasi pada pin 2 hingga 4 (kelompok kiri).

digitalWrite(pin, LOW); : Mematikan LED kelompok kiri.

} : Menutup perulangan pematian LED kiri.

for (int pin = 5; pin <= 7; pin++) { : Kembali melakukan iterasi pada pin 5 hingga 7 (kelompok kanan).

digitalWrite(pin, HIGH); : Menyalakan LED kelompok kanan.

} : Menutup perulangan penyalaan LED kanan.

delay(timer); : Menahan eksekusi selama 500 ms untuk mempertahankan fase "Kiri Mati - Kanan Nyala" sebelum fungsi loop() kembali mengeksekusi baris paling atas.

} : Menutup blok fungsi loop().
