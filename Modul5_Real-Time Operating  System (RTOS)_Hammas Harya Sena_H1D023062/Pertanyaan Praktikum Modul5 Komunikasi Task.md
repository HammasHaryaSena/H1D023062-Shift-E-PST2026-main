Bagian 5.6.4: Komunikasi Task

**1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!**

Meskipun berjalan pada mikrokontroler single-core seperti Arduino Uno yang secara fisik hanya mampu mengeksekusi satu instruksi dalam satu waktu, penggunaan mekanisme Queue pada FreeRTOS menciptakan sistem multitasking yang cerdas dan deterministik melalui sinkronisasi antara task read_data (Producer) dan display (Consumer). Dalam mekanisme ini, task display akan berada dalam status Blocked untuk menghemat sumber daya CPU hingga menerima data baru dari antrean, sementara task read_data akan mengisi antrean tersebut sebelum akhirnya memasuki masa tunggu melalui vTaskDelay(). Proses context switching yang diatur oleh scheduler ini memastikan bahwa perpindahan kendali terjadi secara instan dan tepat waktu, sehingga data yang ditampilkan selalu akurat dan terbaru tanpa adanya risiko pembacaan data lama atau sampah.

**2. Apakah program ini berpotensi mengalami race condition? Jelaskan!**

Berdasarkan kode pada Percobaan 2 (Komunikasi Task), program ini tidak berpotensi mengalami race condition.
- **Penggunaan Queue sebagai Buffer Aman** Dalam pemrograman multitasking tanpa RTOS, kita biasanya menggunakan variabel global untuk berbagi data antar-fungsi. Jika dua fungsi mengakses variabel global secara bersamaan, itulah yang memicu race condition. Namun, pada program ini, Anda menggunakan xQueueCreate, xQueueSend, dan xQueueReceive. Mekanisme antrean (Queue) di FreeRTOS dirancang khusus untuk menjadi thread-safe. Artinya, kernel FreeRTOS memiliki protokol internal (seperti mematikan interupsi sementara atau menggunakan critical sections) untuk memastikan bahwa hanya satu task yang dapat memanipulasi data dalam antrean pada satu waktu.
- **Mekanisme "Copy by Value"** Saat read_data memanggil xQueueSend, data dari struktur readings disalin (copy) ke dalam ruang memori yang dikelola oleh antrean. Ketika display mengambil data dengan xQueueReceive, ia menyalin data dari antrean ke variabel lokalnya sendiri. Karena masing-masing task bekerja dengan salinan datanya sendiri di dalam stack masing-masing, tidak ada perebutan memori fisik yang sama secara bersamaan.
- **Sinkronisasi Otomatis** Program ini menggunakan portMAX_DELAY pada fungsi xQueueReceive. Ini menciptakan mekanisme penguncian otomatis. Task display akan dipaksa berhenti (Blocked) jika antrean kosong. Ia hanya akan "terbangun" jika task read_data telah selesai mengirim data secara utuh. Hal ini mencegah task display membaca data yang baru "setengah jadi" atau data lama yang belum diperbarui.

**3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya?**

_Source Code:_

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

#define DHTPIN 2     // Pin data sensor DHT
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

struct readings {
  float temp;
  float h;
};

QueueHandle_t my_queue;

void setup() {
  Serial.begin(9600);
  dht.begin(); // Inisialisasi sensor DHT

  my_queue = xQueueCreate(1, sizeof(struct readings));

  if (my_queue != NULL) {
    // Task Producer: Membaca sensor fisik
    xTaskCreate(read_sensor_task, "Read DHT", 128, NULL, 1, NULL);
    // Task Consumer: Menampilkan ke serial
    xTaskCreate(display_task, "Display", 128, NULL, 1, NULL);
  }
}

void loop() {}

void read_sensor_task(void *pvParameters) {
  struct readings data;
  for (;;) {
    // Membaca data asli dari sensor
    data.temp = dht.readTemperature();
    data.h = dht.readHumidity();

    // Kirim ke antrean hanya jika data valid
    if (!isnan(data.temp) && !isnan(data.h)) {
      xQueueSend(my_queue, &data, portMAX_DELAY);
    }

    // Sensor DHT butuh jeda minimal 2 detik untuk pembacaan akurat
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void display_task(void *pvParameters) {
  struct readings received_data;
  for (;;) {
    if (xQueueReceive(my_queue, &received_data, portMAX_DELAY) == pdPASS) {
      Serial.print("Real Temp: ");
      Serial.print(received_data.temp);
      Serial.print("C | Humidity: ");
      Serial.print(received_data.h);
      Serial.println("%");
    }
  }
}
```

Penjelasan Baris Kode Modifikasi:

#include <Arduino_FreeRTOS.h>: Memasukkan inti kernel FreeRTOS agar Arduino bisa menjalankan banyak tugas (multitasking) secara bersamaan.
#include <queue.h>: Memasukkan fitur Queue (antrean) untuk mengirim data antar-task secara aman.
#include <DHT.h>: Pustaka standar untuk berinteraksi dengan sensor suhu dan kelembapan DHT.
#define DHTPIN 2: Menentukan bahwa kabel data sensor DHT terhubung ke pin digital 2.
#define DHTTYPE DHT11: Menentukan tipe sensor yang digunakan (DHT11).
DHT dht(DHTPIN, DHTTYPE);: Membuat objek bernama dht untuk memanggil fungsi-fungsi sensor.
struct readings { ... };: Membuat struktur data kustom bernama readings untuk membungkus dua data sekaligus (temp dan h) agar bisa dikirim dalam satu paket melalui Queue.
QueueHandle_t my_queue;: Deklarasi "pegangan" (handle) untuk antrean. Ini seperti alamat kotak surat yang akan kita gunakan nanti.
Serial.begin(9600);: Membuka jalur komunikasi serial ke komputer.
dht.begin();: Mengaktifkan sensor DHT.
my_queue = xQueueCreate(1, sizeof(struct readings));: Membuat antrean dengan kapasitas 1 slot yang ukurannya sebesar struktur readings.
if (my_queue != NULL): Memastikan antrean berhasil dibuat sebelum menjalankan task.
xTaskCreate(...): Perintah untuk membuat tugas mandiri:
read_sensor_task: Nama fungsi yang dijalankan.
"Read DHT" / "Display": Nama deskriptif task (untuk debugging).
128: Ukuran memori (stack) yang dialokasikan untuk task ini.
1: Prioritas task (keduanya setara di angka 1).
void loop() {}: Dalam FreeRTOS, fungsi loop() biasanya dibiarkan kosong karena kontrol program sudah diambil alih oleh scheduler FreeRTOS untuk menjalankan task-task yang telah dibuat.
for (;;): Loop tak terbatas (ciri khas task FreeRTOS).
data.temp = dht.readTemperature();: Mengambil data suhu.
if (!isnan(data.temp) ...): Validasi data. Jika sensor error (menghasilkan Not a Number), data tidak akan diproses.
xQueueSend(my_queue, &data, portMAX_DELAY);: Mengirim paket data ke dalam antrean. portMAX_DELAY artinya task ini akan menunggu selamanya jika antrean penuh sampai ada slot kosong.
vTaskDelay(pdMS_TO_TICKS(2000));: Memberi jeda 2 detik. Penting: Gunakan vTaskDelay, bukan delay(), agar CPU bisa mengerjakan task lain selama waktu tunggu ini.
struct readings received_data;: Wadah untuk menampung data yang diambil dari antrean.
if (xQueueReceive(my_queue, &received_data, portMAX_DELAY) == pdPASS): Mengambil data dari antrean. Jika antrean kosong, task ini akan "tidur" sampai ada data yang masuk (pdPASS).
Serial.print(...): Mencetak data suhu dan kelembapan ke Serial Monitor.