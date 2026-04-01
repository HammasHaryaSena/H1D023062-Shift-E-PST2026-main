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
int timeDelay = 100;

void setup() {
    pinMode(ledPin, OUTPUT);
}

void loop() {
    digitalWrite(ledPin, HIGH);
    delay(timeDelay);
    digitalWrite(ledPin, LOW);
    delay(timeDelay);

    if (timeDelay >= 1000) {
        digitalWrite(ledPin, LOW);
        delay(3000);
        timeDelay = 100;
    } else {
        timeDelay += 100;
    }
}
```

Penjelasan Baris per Baris:

const int ledPin = 12; : Mendeklarasikan konstanta bertipe integer bernama ledPin dan menetapkannya ke pin 12. Nilainya tidak bisa diubah (read-only).

int timeDelay = 100; : Mendeklarasikan variabel integer timeDelay dengan nilai awal 100 ms. Dimulai dari angka kecil agar fase pertama langsung berkedip cepat.

void setup() { : Fungsi bawaan Arduino yang hanya dieksekusi satu kali saat mikrokontroler pertama kali dihidupkan atau direset.

pinMode(ledPin, OUTPUT); : Mengonfigurasi pin 12 (yang disimpan di ledPin) agar berfungsi sebagai jalur keluaran arus listrik (output).

} : Menutup blok fungsi setup().

void loop() { : Fungsi bawaan Arduino yang akan dieksekusi secara terus-menerus tanpa henti.

digitalWrite(ledPin, HIGH); : Mengirimkan sinyal digital bernilai HIGH (tegangan 5V) ke pin 12 untuk menyalakan LED.

delay(timeDelay); : Menghentikan sementara program selama waktu timeDelay (saat ini LED sedang menyala).

digitalWrite(ledPin, LOW); : Mengirimkan sinyal digital bernilai LOW (tegangan 0V) ke pin 12 untuk mematikan LED.

delay(timeDelay); : Menghentikan sementara program selama waktu timeDelay (saat ini LED sedang mati).

if (timeDelay >= 1000) { : Memeriksa kondisi apakah nilai penundaan sudah mencapai 1000 ms (batas kelambatan).

digitalWrite(ledPin, LOW); : Jika kondisi if terpenuhi, pastikan LED dimatikan.

delay(3000); : Menahan kondisi mati tersebut selama 3000 ms (3 detik) untuk menciptakan efek mati/jeda.

timeDelay = 100; : Mereset variabel timeDelay kembali ke 100 ms agar siklus berulang dari awal.

} else { : Jika kondisi if tidak terpenuhi (nilai timeDelay masih di bawah 1000 ms).

timeDelay += 100; : Menambahkan 100 ms ke nilai timeDelay saat ini, sehingga pada putaran loop berikutnya kedipan akan menjadi lebih lambat secara bertahap (fase sedang).

} : Menutup blok percabangan if-else.

} : Menutup blok fungsi loop().
