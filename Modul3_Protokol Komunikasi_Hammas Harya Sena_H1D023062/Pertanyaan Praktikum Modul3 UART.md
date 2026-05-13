Bagian 3.5.4: Komunikasi Serial (UART)

**1. Jelaskan proses dari input keyboard hingga LED menyala/mati!**

- **Input:** Pengguna mengetikkan karakter ('1' atau '0') di _keyboard_ dan menekan _Enter_ pada antarmuka Serial Monitor di komputer.
- **Transmisi:** Komputer mengubah karakter tersebut menjadi kode ASCII dan mengirimkannya dalam bentuk sinyal digital melalui kabel USB (protokol UART) ke pin RX (Receive) pada Arduino.
- **Pemrosesan:** Arduino menerima data tersebut dan menyimpannya di _serial buffer_. Perintah `Serial.read()` mengambil karakter tersebut dari _buffer_.
- **Eksekusi:** Struktur logika `if-else` mengevaluasi karakter. Jika data adalah '1', Arduino mengirimkan tegangan 5V (HIGH) ke pin 12 sehingga LED menyala. Jika '0', tegangan diturunkan ke 0V (LOW) sehingga LED mati.

**2. Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?**
Fungsi `Serial.available()` digunakan untuk mengecek apakah ada byte data yang sudah masuk dan siap dibaca di dalam _buffer_ penerima. Jika baris ini dihilangkan, Arduino akan terus-menerus mengeksekusi `Serial.read()` pada setiap siklus `loop()` meskipun komputer tidak mengirimkan data apa pun. Hal ini akan mengembalikan nilai `-1` (atau 255/karakter kosong), yang menyebabkan program memproses "sampah" secara terus-menerus dan membuang siklus kerja CPU secara percuma.

**3. Modifikasi program agar LED berkedip (blink) ketika menerima input '2'**
_Source Code:_

```cpp
const int PIN_LED = 12;
char currentMode = '0';
unsigned long previousMillis = 0;
const long interval = 500;
bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  Serial.println("Ketik '1'(ON), '0'(OFF), atau '2'(BLINK)");
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  // Mengecek apakah ada instruksi masuk dari Serial Monitor
  if (Serial.available() > 0) {
    char data = Serial.read();

    if (data == '1' || data == '0' || data == '2') {
      currentMode = data; // Perbarui mode sesuai input

      if (currentMode == '1') {
        digitalWrite(PIN_LED, HIGH);
        Serial.println("LED ON");
      }
      else if (currentMode == '0') {
        digitalWrite(PIN_LED, LOW);
        Serial.println("LED OFF");
      }
      else if (currentMode == '2') {
        Serial.println("LED BLINKING (Mode 2 Aktif)");
      }
    }
    else if (data != '\n' && data != '\r') {
      Serial.println("Perintah tidak dikenal");
    }
  }

  // Logika BLINK tanpa memblokir pembacaan serial
  if (currentMode == '2') {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(PIN_LED, ledState);
    }
  }
}
```

Penjelasan Baris Kode Modifikasi:

char currentMode = '0'; : Menyimpan status mode aktif saat ini (diawali dengan mode OFF).

unsigned long previousMillis = 0; : Variabel untuk menyimpan catatan waktu terakhir kali LED berubah status (menggunakan tipe unsigned long untuk mencegah overflow memori waktu).

const long interval = 500; : Menetapkan jeda kedipan LED sebesar 500 milidetik.

bool ledState = LOW; : Mengingat kondisi LED saat ini (mati atau menyala).

void loop() { ... } : Jika ada data serial (Serial.available() > 0), program akan membacanya dan memperbarui nilai currentMode.

if (currentMode == '2') { : Mengeksekusi blok ini jika pengguna sudah mengirimkan angka '2'.

unsigned long currentMillis = millis(); : Mengambil waktu (dalam milidetik) sejak Arduino pertama kali dihidupkan.

if (currentMillis - previousMillis >= interval) : Mengevaluasi apakah selisih waktu saat ini dengan waktu terakhir LED berubah sudah mencapai 500ms. Jika iya, maka status ledState akan dibalik (!ledState) dan dikirimkan ke pin LED.

**4. Tentukan apakah menggunakan delay() atau millis()! Jelaskan pengaruhnya terhadap sistem**

Untuk memodifikasi LED agar berkedip (Mode '2') sembari tetap bisa menerima input mode lain ('0' atau '1') tanpa delay, kita wajib menggunakan millis().
Pengaruhnya sangat besar: fungsi delay() bersifat blocking (menghentikan seluruh aktivitas mikrokontroler selama waktu jeda), sehingga Arduino akan "tuli" dan tidak bisa membaca input Serial baru saat LED sedang dalam fase jeda. Sebaliknya, millis() bersifat non-blocking, memungkinkan mikrokontroler mengeksekusi instruksi pembacaan Serial secara paralel sambil terus melacak waktu kedipan LED di latar belakang.
