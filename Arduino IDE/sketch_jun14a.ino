#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Mengatur kredensial WiFi dan alamat server
const char* ssid = "PASSWORDNYA";
const char* password = "lolz1122";
const char* serverName = "http://192.168.35.253:5001/api/data";  

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);  

  // Menghubungkan ke jaringan WiFi
  WiFi.begin(ssid, password);
  Serial.print("Sedang Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");  
  }
  Serial.println("Terhubung ke WiFi");

  dht.begin();  
}

void loop() {
  delay(2000); 

  // Memeriksa status koneksi WiFi
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("ESP32 Terhubung ke WiFi");

    HTTPClient http;

    float temperature = dht.readTemperature();  
    float humidity = dht.readHumidity();  

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Gagal membaca data dari sensor DHT!");  
      return;
    }

    http.begin(serverName);  
    http.addHeader("Content-Type", "application/json");  

    // Membuat data JSON untuk dikirim
    String httpRequestData = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
    Serial.print("Mengirim Data ke server: ");
    Serial.println(httpRequestData);  

    int httpResponseCode = http.POST(httpRequestData);  

    // Memeriksa kode respon HTTP
    if (httpResponseCode > 0) {
      String response = http.getString();  
      Serial.print("Kode Respon HTTP: ");
      Serial.println(httpResponseCode);  
      Serial.print("Respon: ");
      Serial.println(response);  
    } else {
      Serial.print("Kesalahan saat mengirim POST: ");
      Serial.println(httpResponseCode);  
    }

    http.end(); 
  } else {
    Serial.println("Koneksi WiFi Terputus");  
  }

  delay(10000);  
}
