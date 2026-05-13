#include <Arduino_FreeRTOS.h>
#include <queue.h>

// Definisi struktur untuk menampung data
struct readings {
  int temp;
  int h;
};

// Handle untuk queue
QueueHandle_t my_queue;

// Prototype fungsi task
void read_data(void *pvParameters);
void display(void *pvParameters);

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; } // Tunggu port serial siap

  // Membuat queue dengan kapasitas 1 item
  my_queue = xQueueCreate(1, sizeof(struct readings));

  if (my_queue != NULL) {
    // Membuat task untuk membaca data
    xTaskCreate(read_data, "Read Sensors", 128, NULL, 1, NULL);
    
    // Membuat task untuk menampilkan data
    xTaskCreate(display, "Display", 128, NULL, 1, NULL);
  }
}

void loop() {
  // Kosong, FreeRTOS menangani penjadwalan task
}

/* * Task untuk mensimulasikan pembacaan data sensor 
 * dan mengirimkannya ke queue.
 */
void read_data(void *pvParameters) {
  struct readings x;
  for (;;) {
    x.temp = 54;
    x.h = 30;

    // Mengirim data ke queue
    xQueueSend(my_queue, &x, portMAX_DELAY);

    // Delay selama 1000ms (1 detik)
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

/* * Task untuk menerima data dari queue 
 * dan menampilkannya ke Serial Monitor.
 */
void display(void *pvParameters) {
  struct readings x;
  for (;;) {
    // Menunggu data tersedia di queue
    if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {
      Serial.print("Temp = ");
      Serial.print(x.temp);
      Serial.print(" | Humidity = ");
      Serial.println(x.h);
    }
  }
}