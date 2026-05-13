Bagian 5.5.4: Multitasking

**1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!**

Pada sistem single-core seperti Arduino Uno, FreeRTOS menciptakan ilusi konkurensi dengan menjalankan setiap task secara bergantian melalui algoritma Round Robin, di mana scheduler membagi waktu CPU secara adil untuk tugas-tugas dengan prioritas yang sama. Efisiensi mekanisme ini sangat bergantung pada penggunaan vTaskDelay() yang secara cerdas mengubah status task menjadi Blocked saat sedang menunggu, sehingga sumber daya CPU dapat langsung dialihkan ke task lain yang sudah siap (Ready) tanpa membuang waktu percuma. Hasilnya, transisi cepat antar-status ini memungkinkan output program muncul secara bergantian dan responsif, membuktikan bahwa manajemen waktu yang ketat jauh lebih efektif daripada sekadar menggunakan fungsi delay() standar.

**2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!**

- **Definisikan fungsi task** dengan struktur void NamaFungsi(void *pvParameters).
- **Gunakan loop** while(1) di dalam fungsi tersebut agar tugas berjalan kontinu.
- **Panggil** xTaskCreate() di dalam setup() dengan parameter yang sesuai (fungsi, nama, stack, parameter, prioritas, handle).
- **Verifikasi melalui Serial Monitor** untuk memastikan task keempat berjalan beriringan dengan task lainnya tanpa mengganggu integritas sistem.

**3. Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya?**

_Source Code:_

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t xQueueSensor;

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT); // Pin LED

  // Membuat Queue untuk menampung 1 data integer [cite: 124, 154]
  xQueueSensor = xQueueCreate(1, sizeof(int));

  if (xQueueSensor != NULL) {
    // Task Producer: Membaca Potensiometer
    xTaskCreate(TaskSensor, "Sensor", 128, NULL, 1, NULL);
    // Task Consumer: Kontrol LED
    xTaskCreate(TaskLED, "LED", 128, NULL, 1, NULL);
  }
}

void loop() {}

void TaskSensor(void *pvParameters) {
  while(1) {
    int sensorValue = analogRead(A0); // Membaca potensiometer pada pin A0 [cite: 33]
    // Mengirim nilai ke antrean [cite: 125, 170]
    xQueueSend(xQueueSensor, &sensorValue, portMAX_DELAY);
    vTaskDelay(100 / portTICK_PERIOD_MS); // Sampling setiap 100ms
  }
}

void TaskLED(void *pvParameters) {
  int speedValue;
  while(1) {
    // Menerima nilai dari antrean [cite: 126, 170]
    if (xQueueReceive(xQueueSensor, &speedValue, portMAX_DELAY) == pdPASS) {
      digitalWrite(8, HIGH);
      // Menggunakan nilai sensor sebagai durasi delay [cite: 93]
      vTaskDelay(speedValue / portTICK_PERIOD_MS); 
      digitalWrite(8, LOW);
      vTaskDelay(speedValue / portTICK_PERIOD_MS);
    }
  }
}
```

Penjelasan Baris Kode Modifikasi:

#include <Arduino_FreeRTOS.h>: Memasukkan kernel FreeRTOS ke dalam program untuk mengaktifkan fitur multitasking.  
#include <queue.h>: Memasukkan pustaka manajemen antrean (queue) untuk komunikasi antar-tugas yang aman.  
QueueHandle_t xQueueSensor;: Mendeklarasikan variabel handle untuk mengidentifikasi antrean data sensor yang akan dibuat.
Serial.begin(9600);: Memulai komunikasi serial untuk pemantauan data melalui Serial Monitor.  
pinMode(8, OUTPUT);: Mengonfigurasi pin digital 8 sebagai output untuk mengendalikan LED.  
xQueueCreate(1, sizeof(int));: Membuat sebuah antrean yang mampu menampung 1 data bertipe integer (nilai potensiometer) secara terstruktur. 
if (xQueueSensor != NULL): Memastikan bahwa memori untuk antrean berhasil dialokasikan sebelum menjalankan tugas.
xTaskCreate(...): Mendaftarkan tugas TaskSensor dan TaskLED ke dalam scheduler agar dapat berjalan secara konkuren. Angka 128 adalah ukuran stack (memori), dan 1 adalah prioritas tugas
int sensorValue = analogRead(A0);: Membaca nilai tegangan analog dari potensiometer pada pin A0.  
xQueueSend(...): Mengirimkan hasil pembacaan sensor ke dalam antrean xQueueSensor agar bisa diambil oleh tugas lain tanpa risiko korupsi data.  
vTaskDelay(...): Menunda tugas selama 100ms dan memindahkannya ke status Blocked, sehingga CPU dapat digunakan oleh tugas lain. 
xQueueReceive(...): Mengambil data dari antrean. Jika antrean kosong, tugas ini akan berada dalam status Blocked hingga ada data masuk. 
digitalWrite(8, HIGH/LOW);: Menyalakan dan mematikan LED berdasarkan logika program.  
vTaskDelay(speedValue / ...): Menggunakan nilai dari potensiometer (speedValue) sebagai durasi kedipan LED secara dinamis.