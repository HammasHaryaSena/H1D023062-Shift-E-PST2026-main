Bagian 4.5.4: Analog to Digital Converter (ADC)

**1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini?**

Fungsi `analogRead()` digunakan untuk membaca besaran tegangan analog murni yang dikirimkan oleh potensiometer ke pin A0, kemudian mengonversinya (kuantisasi) menjadi nilai digital diskret yang dapat dipahami oleh mikrokontroler Arduino. Rentang nilai digital yang dihasilkan adalah dari 0 (mewakili 0 Volt) hingga 1023 (mewakili 5 Volt) karena Arduino Uno menggunakan ADC beresolusi 10-bit.

**2. Mengapa diperlukan fungsi map() dalam program tersebut?**

Fungsi `map()` sangat diperlukan untuk men-skala ulang (konversi proporsional) rentang data input agar sesuai dengan batas rentang aktuator output. Pada kasus ini, pembacaan ADC dari potensiometer memiliki rentang 0-1023, sedangkan motor servo SG90 secara fisik hanya bisa berputar dari sudut 0 hingga 180 derajat. Fungsi `map()` secara otomatis menerjemahkan nilai ADC ke sudut yang proporsional sehingga motor tidak menerima perintah pergerakan yang melampaui batas mekanisnya.


**3. Modifikasi Program Servo (Rentang 30° - 150°)**
_Source Code:_

```cpp
#include <Servo.h>

Servo myservo;

const int potensioPin = A0;
const int servoPin = 9;

int pos = 0;
int val = 0;

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potensioPin);

  // Modifikasi rentang pemetaan sudut di sini
  pos = map(val, 0, 1023, 30, 150);

  myservo.write(pos);

  Serial.print("ADC Potensio: ");
  Serial.print(val);
  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  delay(100);
}
```

Penjelasan Baris per Baris Program:
#include <Servo.h> : Memasukkan library bawaan Arduino untuk mengontrol motor servo.
Servo myservo; : Membuat sebuah objek dari library Servo dengan nama myservo.
const int potensioPin = A0; : Menetapkan pin A0 sebagai jalur masuk data analog dari potensiometer. const int servoPin = 9; : Menetapkan pin digital 9 (yang mendukung PWM) sebagai jalur sinyal kendali untuk motor servo.
int pos = 0; : Mendeklarasikan variabel pos untuk menyimpan sudut servo (nilai awal 0).
int val = 0; : Mendeklarasikan variabel val untuk menyimpan hasil pembacaan ADC potensiometer (nilai awal 0).
void setup() { : Fungsi pengaturan awal yang dijalankan sekali oleh mikrokontroler.
myservo.attach(servoPin); : Menghubungkan objek myservo ke pin 9 agar sinyal PWM dapat dikirim ke aktuator.
Serial.begin(9600); : Mengaktifkan komunikasi serial ke komputer dengan kecepatan 9600 bps untuk proses monitoring.
void loop() { : Fungsi utama yang akan terus diulang (siklus program).
val = analogRead(potensioPin); : Membaca nilai dari pin A0 (0 hingga 1023) dan menyimpannya di variabel val .
pos = map(val, 0, 1023, 30, 150); : (Baris Modifikasi) Menerjemahkan nilai val (0-1023) menjadi nilai sudut secara linier dengan batas minimum 30 derajat dan maksimum 150 derajat .
myservo.write(pos); : Memerintahkan servo berputar menuju sudut yang telah dihitung dan disimpan dalam pos.
Serial.print("ADC Potensio: "); hingga Serial.
println(pos); : Mengirim teks dan nilai pemrosesan data (ADC dan Sudut) untuk ditampilkan di layar Serial Monitor secara real-time .
delay(100); : Memberikan waktu jeda 100 milidetik pada sistem untuk memberikan kesempatan bagi komponen mekanis servo mencapai posisi targetnya secara stabil .