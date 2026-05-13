Bagian 3.6.4: Inter-Integrated Circuit (I2C)

**1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!**

Komunikasi I2C menggunakan arsitektur Master-Slave. Arduino bertindak sebagai Master dan LCD sebagai Slave. Komunikasi ini hanya menggunakan dua kabel: SDA (Serial Data pada pin A4) untuk transfer data dua arah, dan SCL (Serial Clock pada pin A5) untuk sinkronisasi waktu transmisi.
Arduino pertama-tama mengirimkan sinyal clock dan memanggil alamat unik LCD (misalnya 0x27). Setelah LCD mengonfirmasi alamat tersebut, Arduino mulai mengirimkan paket data karakter teks atau instruksi posisi kursor melalui jalur SDA. LCD menerima data tersebut dan menampilkannya di layar.


**2. Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar!**

Pin tengah potensiometer wajib terhubung ke pin Analog (A0) sebagai output pembacaan. Namun, pin kiri dan kanan (VCC dan GND) bebas ditukar.
Potensiometer bekerja sebagai pembagi tegangan (voltage divider). Apabila pin VCC 5V dan GND tertukar, yang terjadi hanyalah arah logikanya yang terbalik. Misalnya, jika awalnya diputar ke kanan penuh bernilai 1023 dan ke kiri penuh bernilai 0, maka jika kabel VCC dan GND ditukar, putar ke kanan penuh akan menjadi 0 dan putar ke kiri penuh akan menjadi 1023. Rangkaian tidak akan rusak atau mengalami short circuit.

**3. Modifikasi program dengan menggabungkan antara UART dan I2C**
_Source Code:_

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinPot = A0;

void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
}

void loop() {
    int nilai = analogRead(pinPot);

    // Proses perhitungan matematika
    int panjangBar = map(nilai, 0, 1023, 0, 16);
    int persen = map(nilai, 0, 1023, 0, 100);
    float volt = (nilai / 1023.0) \* 5.0;

    // 1. Output ke Serial Monitor (UART)
    Serial.print("ADC: ");
    Serial.print(nilai);
    Serial.print("\tVolt: ");
    Serial.print(volt);
    Serial.print(" V\tPersen: ");
    Serial.print(persen);
    Serial.println("%");

    // 2. Output ke LCD (I2C)
    lcd.setCursor(0, 0);
    lcd.print("ADC:");
    lcd.print(nilai);
    lcd.print(" ");
    lcd.print(persen);
    lcd.print("% "); // Spasi ekstra untuk membersihkan sisa karakter lama

    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) {
        if (i < panjangBar) {
        lcd.print((char)255); // Cetak blok hitam padat
        } else {
            lcd.print(" "); // Cetak spasi kosong
            }
    }

    delay(500); // Penahan refresh rate agar mudah dibaca
}
```

Penjelasan Baris Kode Modifikasi:

int panjangBar = map(...); : Memetakan nilai ADC (0-1023) ke jumlah kolom maksimal pada LCD (0-16) untuk menggambar grafik bar.

int persen = map(nilai, 0, 1023, 0, 100); : Mengubah rentang 0-1023 menjadi skala persentase 0-100%.

float volt = (nilai / 1023.0) \* 5.0; : Menghitung tegangan murni. Karena 1023 mewakili 5V, nilai ADC dibagi 1023 lalu dikali 5 (menggunakan tipe data float agar presisi desimalnya tidak hilang).

Blok Serial.print(...) : Arduino mengirimkan data teks secara serial (asynchronous) ke komputer menggunakan modul UART.

lcd.setCursor(0, 0); : Memerintahkan modul I2C untuk meletakkan kursor pada kolom ke-0 (paling kiri) di baris ke-0 (paling atas).

lcd.print("% "); : Tiga buah spasi ekstra di akhir perintah print berfungsi sangat vital untuk menimpa/menghapus karakter dari putaran sebelumnya.

Blok for (int i = 0; i < 16; i++) { ... } : Mencetak balok solid (char)255 sebanyak jumlah panjangBar. Jika iterasi kolom i sudah melampaui panjangBar, sisa layar LCD di baris tersebut akan ditimpa dengan spasi agar kembali bersih.

**4. Lengkapi tabel berikut berdasarkan pengamatan pada Serial Monitor**

ADC,Volt (V),Persen (%)
1,0.00 V,0 %
21,0.10 V,2 %
49,0.24 V,4 %
74,0.36 V,7 %
96,0.47 V,9 %
