Bagian 2.6.4: Push Button

**1. Gambarkan rangkaian schematic yang digunakan pada percobaan!**

<img width="661" height="380" alt="Image" src="https://github.com/user-attachments/assets/09e3fdfe-26d6-4f0d-a18e-6974399fc151" />

**2. Mengapa pada push button digunakan mode INPUT_PULLUP pada Arduino Uno? Apa keuntungannya dibandingkan rangkaian biasa?**
Mode `INPUT_PULLUP` digunakan untuk memberdayakan/mengaktifkan resistor penarik (_pull-up resistor_) internal sebesar ~20 kΩ yang sudah terintegrasi di dalam _chip_ mikrokontroler Arduino.
**Keuntungannya:**

1. **Lebih praktis:** Tidak memerlukan penambahan komponen resistor eksternal di _breadboard_, sehingga meminimalisir jalur kabel dan menghemat ruang (_wiring_ lebih rapi).
2. **Sinyal Stabil:** Memastikan status pin digital selalu berada pada tegangan tinggi (`HIGH`) saat tombol dilepas, mencegah kondisi mengambang (_floating node_) akibat induksi elektromagnetik sekitar yang bisa menyebabkan sistem menghitung sendiri secara acak. Saat ditekan, pin akan langsung terbaca `LOW`.

**3. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?**
- **Penyebab Hardware:** Serat kabel _jumper_ penghubung putus di bagian dalam, pin port digital Arduino rusak, komponen _Seven Segment_ tidak tertancap sempurna di _breadboard_, atau elemen dioda LED pada bagian segmen tersebut sudah terbakar/rusak.
- **Penyebab Software:** Kesalahan ketik (_typo_) saat mendeklarasikan urutan pin pada variabel _array_ `segmentPins`, atau kekeliruan menempatkan nilai logika biner `1` dan `0` pada baris karakter tertentu di dalam matriks memori `digitPattern`.

**4. Modifikasi rangkaian dan program dengan dua push button (increment/decrement) dan penjelasannya**

_Source Code:_

```cpp
const int btnDown = 2; // Pin untuk tombol kurang
bool lastDownState = HIGH; // State deteksi tepi tombol kurang

void setup() {
  // Setup untuk segmen...
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP); // Aktivasi pull-up internal untuk tombol ke-2
}

void loop() {
  bool upState = digitalRead(btnUp);
  bool downState = digitalRead(btnDown);

  // Blok Increment (Tambah)
  if(lastUpState == HIGH && upState == LOW) {
    delay(300);
    currentDigit++;
    if(currentDigit > 15) currentDigit = 0;
    displayDigit(currentDigit);
  }
  lastUpState = upState;

  // Blok Decrement (Kurang)
  if(lastDownState == HIGH && downState == LOW) {
    delay(300);
    currentDigit--;
    if(currentDigit < 0) currentDigit = 15;
    displayDigit(currentDigit);
  }
  lastDownState = downState;
}
```

Penjelasan baris kode logika (Decrement):

bool downState = digitalRead(btnDown); : Membaca tegangan aktual dari pin tombol kurang dan menyimpannya ke variabel boolean.

if(lastDownState == HIGH && downState == LOW) { : Syarat terjadinya pemicu. Jika siklus sebelumnya tombol tidak ditekan (HIGH) dan saat ini sedang ditekan (LOW), maka kondisi bernilai benar (mendeteksi falling edge).

delay(300); : Waktu tunda 300 milidetik sebagai peredam bouncing (loncatan sinyal listrik mekanis).

currentDigit--; : Mengurangi isi variabel angka sebanyak 1 (decrement).

if(currentDigit < 0) currentDigit = 15; : Mekanisme pembatas underflow. Jika angka dikurangi terus hingga di bawah 0, maka nilainya diputar kembali menjadi 15 ('F').

displayDigit(currentDigit); : Mengeksekusi penyalaan pola segmen sesuai angka terbaru.

lastDownState = downState; : Memperbarui riwayat status tombol untuk pengecekan di siklus loop berikutnya.