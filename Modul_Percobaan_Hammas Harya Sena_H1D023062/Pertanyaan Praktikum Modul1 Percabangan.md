# Jawaban Pertanyaan Praktikum Modul I

## Bagian 1.5.4: Percabangan

**1. Pada kondisi apa program masuk ke blok if?**
Program akan masuk ke blok `if` ketika kondisi yang dievaluasi bernilai benar (_true_). Pada percobaan modul, ini terjadi ketika variabel `timeDelay <= 100`, artinya ketika jeda kedipan LED sudah sangat singkat (berkedip cepat), program akan mengeksekusi blok `if` untuk memberikan jeda mati sementara dan mereset nilai penundaan kembali ke awal (1000 ms).

**2. Pada kondisi apa program masuk ke blok else?**
Program masuk ke blok `else` apabila kondisi pada blok `if` bernilai salah (_false_). Selama variabel `timeDelay` nilainya masih di atas 100 ms, blok `else` akan terus dieksekusi pada setiap putaran untuk mengurangi nilai `timeDelay` secara bertahap (menggunakan `timeDelay -= 100;`), yang membuat kedipan makin lama makin cepat.

**3. Apa fungsi dari perintah delay(timeDelay)?**
Fungsi `delay(timeDelay)` adalah menghentikan sementara proses eksekusi kode pada mikrokontroler selama waktu yang ditentukan oleh isi variabel `timeDelay` (dalam satuan milidetik). Ini berfungsi untuk menahan kondisi pin (tetap menyala/`HIGH` atau tetap mati/`LOW`) cukup lama agar perubahannya bisa ditangkap secara visual oleh mata manusia.

**4. Modifikasi Program Percabangan (Cepat → Sedang → Mati)**

_Source Code:_

```cpp
const int ledPin = 12;      
int timeDelay;              

void setup() { 
  pinMode(ledPin, OUTPUT);  
  
  for (timeDelay = 1000; timeDelay >= 200; timeDelay -= 200) {
    digitalWrite(ledPin, HIGH); 
    delay(timeDelay);           
    digitalWrite(ledPin, LOW);  
    delay(timeDelay);           
  }

  timeDelay = 600;
  digitalWrite(ledPin, HIGH);   
  delay(timeDelay);            
  digitalWrite(ledPin, LOW);   
  delay(timeDelay);   
  digitalWrite(ledPin, LOW);
} 

void loop() { 
}
```

- void setup(): Saya memindahkan logika ke dalam setup karena setup hanya berjalan satu kali. Ini adalah cara termudah agar program tidak reset (mengulang) ke awal.

- for (timeDelay = 1000; ...): Baris ini menangani alur Lambat → Cepat. Nilai awal 1000ms akan dikurangi 200ms terus-menerus sampai menyentuh angka 200ms.

- timeDelay = 600: Setelah putaran cepat selesai, kita secara manual mengatur jeda ke angka menengah (600ms) untuk menciptakan fase Sedang.

- digitalWrite(ledPin, LOW) (Terakhir): Memastikan LED dalam keadaan mati setelah semua urutan kedip selesai.

- void loop() { }: Dengan membiarkan bagian ini kosong, Arduino tidak akan melakukan apa-apa lagi setelah urutan di setup selesai. LED akan tetap mati selamanya kecuali tombol reset pada papan Arduino ditekan atau kabel power dicabut-pasang kembali.
