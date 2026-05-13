Bagian 4.6.4: Digital to Analog Converter (PWM)

**1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!**

Fungsi analogWrite() menggunakan teknik Pulse Width Modulation (PWM) yang secara periodik menghidupkan dan mematikan sinyal digital dalam kecepatan tinggi . Dengan mengubah durasi keadaan HIGH dan LOW (duty cycle), fungsi ini memanipulasi tegangan rata-rata yang diterima oleh komponen . Pada LED, perubahan tegangan rata-rata ini ditangkap oleh indera penglihatan manusia sebagai redup atau terangnya cahaya.

**2. Apa hubungan antara nilai ADC (0-1023) dan nilai PWM (0-255)?**

Nilai ADC (0-1023) merupakan hasil pembacaan input dengan resolusi 10-bit, sedangkan nilai PWM (0-255) adalah resolusi sinyal output 8-bit yang dihasilkan oleh Arduino Uno. Hubungannya adalah skalabilitas; agar data input dapat mengendalikan kecerahan lampu secara akurat dan linier, nilai ADC tersebut harus dikonversi (misalnya dengan dibagi 4 atau diproses menggunakan fungsi map()) sehingga sesuai dengan rentang maksimal output PWM .

**3. Modifikasi Program Kecerahan LED (Rentang PWM 50 - 200)**
_Source Code:_

```cpp
#include <Arduino.h>

const int potPin = A0;  
const int ledPin = 9;

int nilaiADC = 0;  
int pwm = 0;

void setup() {
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}

void loop() {
nilaiADC = analogRead(potPin);

// Modifikasi batas PWM menjadi 50 hingga 200 di sini
pwm = map(nilaiADC, 0, 1023, 50, 200);

analogWrite(ledPin, pwm);

Serial.print("ADC: ");
Serial.print(nilaiADC);
Serial.print(" | PWM: ");
Serial.println(pwm);

delay(50);
}
```

Penjelasan Baris per Baris Program:
#include <Arduino.h> : Memanggil kerangka library dasar milik Arduino.
const int potPin = A0; : Menetapkan pin analog A0 sebagai input dari potensiometer .
const int ledPin = 9; : Menetapkan pin digital 9 sebagai output PWM untuk LED .
int nilaiADC = 0; : Mendeklarasikan variabel nilaiADC dengan nilai awal 0 untuk menampung data sensor.
int pwm = 0; : Mendeklarasikan variabel pwm dengan nilai awal 0 untuk menyimpan data konversi kecerahan .
void setup() { : Fungsi penyiapan konfigurasi dasar saat alat pertama kali berjalan.
pinMode(ledPin, OUTPUT); : Mengonfigurasi fungsi ledPin (pin 9) agar bekerja sebagai jalur OUTPUT sinyal listrik ke LED.
Serial.begin(9600); : Menginisialisasi modul komunikasi serial komputer pada kecepatan baud rate 9600.
void loop() { : Fungsi program utama yang akan terus dieksekusi berulang-ulang tanpa henti.
nilaiADC = analogRead(potPin); : Memerintahkan mikrokontroler membaca sinyal analog di pin A0 dan menyimpannya sebagai angka (0-1023).
pwm = map(nilaiADC, 0, 1023, 50, 200); : (Baris Modifikasi) Mengubah skala nilai nilaiADC (0-1023) menjadi batas nilai PWM kecerahan "sedang" secara proporsional.Batas redup terendah diatur di angka 50 dan paling terang dibatasi pada angka 200 .
analogWrite(ledPin, pwm); : Memerintahkan pengiriman sinyal PWM (pulsa duty cycle) ke pin 9 sebesar nilai variabel pwm yang sudah dimodifikasi.
Serial.print("ADC: "); hingga Serial.println(pwm); : Rangkaian instruksi untuk mencetak nilai input (ADC) dan output kecerahan (PWM) ke layar monitor komputer .
delay(50); : Menghentikan program sejenak selama 50 milidetik pada akhir iterasi, bertujuan menjaga stabilitas pembacaan sensor dan kecepatan tampilan data agar tidak terlalu cepat di layar .