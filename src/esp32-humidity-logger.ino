#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <DHT.h>
#include "ArduinoJson-v5.10.1.hpp"

#define DHTTYPE DHT11

using namespace ArduinoJson;

const char* ssid = SSID_NAME;
const char* password = SSID_PASS;

const char* token = LOGZIO_TOKEN;
const char* server_host = "listener.logz.io";
const int server_port = 5052;
const char* root_ca= \
     "-----BEGIN CERTIFICATE-----\n" \
     "MIIENjCCAx6gAwIBAgIBATANBgkqhkiG9w0BAQUFADBvMQswCQYDVQQGEwJTRTEU\n" \
     "MBIGA1UEChMLQWRkVHJ1c3QgQUIxJjAkBgNVBAsTHUFkZFRydXN0IEV4dGVybmFs\n" \
     "IFRUUCBOZXR3b3JrMSIwIAYDVQQDExlBZGRUcnVzdCBFeHRlcm5hbCBDQSBSb290\n" \
     "MB4XDTAwMDUzMDEwNDgzOFoXDTIwMDUzMDEwNDgzOFowbzELMAkGA1UEBhMCU0Ux\n" \
     "FDASBgNVBAoTC0FkZFRydXN0IEFCMSYwJAYDVQQLEx1BZGRUcnVzdCBFeHRlcm5h\n" \
     "bCBUVFAgTmV0d29yazEiMCAGA1UEAxMZQWRkVHJ1c3QgRXh0ZXJuYWwgQ0EgUm9v\n" \
     "dDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALf3GjPm8gAELTngTlvt\n" \
     "H7xsD821+iO2zt6bETOXpClMfZOfvUq8k+0DGuOPz+VtUFrWlymUWoCwSXrbLpX9\n" \
     "uMq/NzgtHj6RQa1wVsfwTz/oMp50ysiQVOnGXw94nZpAPA6sYapeFI+eh6FqUNzX\n" \
     "mk6vBbOmcZSccbNQYArHE504B4YCqOmoaSYYkKtMsE8jqzpPhNjfzp/haW+710LX\n" \
     "a0Tkx63ubUFfclpxCDezeWWkWaCUN/cALw3CknLa0Dhy2xSoRcRdKn23tNbE7qzN\n" \
     "E0S3ySvdQwAl+mG5aWpYIxG3pzOPVnVZ9c0p10a3CitlttNCbxWyuHv77+ldU9U0\n" \
     "WicCAwEAAaOB3DCB2TAdBgNVHQ4EFgQUrb2YejS0Jvf6xCZU7wO94CTLVBowCwYD\n" \
     "VR0PBAQDAgEGMA8GA1UdEwEB/wQFMAMBAf8wgZkGA1UdIwSBkTCBjoAUrb2YejS0\n" \
     "Jvf6xCZU7wO94CTLVBqhc6RxMG8xCzAJBgNVBAYTAlNFMRQwEgYDVQQKEwtBZGRU\n" \
     "cnVzdCBBQjEmMCQGA1UECxMdQWRkVHJ1c3QgRXh0ZXJuYWwgVFRQIE5ldHdvcmsx\n" \
     "IjAgBgNVBAMTGUFkZFRydXN0IEV4dGVybmFsIENBIFJvb3SCAQEwDQYJKoZIhvcN\n" \
     "AQEFBQADggEBALCb4IUlwtYj4g+WBpKdQZic2YR5gdkeWxQHIzZlj7DYd7usQWxH\n" \
     "YINRsPkyPef89iYTx4AWpb9a/IfPeHmJIZriTAcKhjW88t5RxNKWt9x+Tu5w/Rw5\n" \
     "6wwCURQtjr0W4MHfRnXnJK3s9EK0hZNwEGe6nQY1ShjTK3rMUUKhemPR5ruhxSvC\n" \
     "Nr4TDea9Y355e6cJDUCrat2PisP29owaQgVR1EX1n6diIWgVIEM8med8vSTYqZEX\n" \
     "c4g/VhsxOBi0cQ+azcgOno4uG+GMmIPLHzHxREzGBHNJdmAPx/i9F4BrLunMTA5a\n" \
     "mnkPIAou1Z5jJh5VkpTYghdae9C8x49OhgQ=\n" \
     "-----END CERTIFICATE-----\n";

const int DHTPin = 32;
DHT dht(DHTPin, DHTTYPE);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(10);

  dht.begin();

  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  delay(10000);

  Serial.println(WiFi.localIP()); // Printing the ESP IP address

  timeClient.begin();
}

void loop() {
  timeClient.update();

  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Computes temperature values
    float hic = dht.computeHeatIndex(t, h, false);

    // Convert to JSON and ship to logz.io
    {
      ArduinoJson::StaticJsonBuffer<300> jsonBuffer;

      JsonObject& root = jsonBuffer.createObject();
      root["token"] = token;
      root["type"] = "sensor";
      root["@timestamp"] = timeClient.getFormattedDate();
      root["temperature_c"] = t;
      root["heat_index_c"] = hic;
      root["humidity"] = h;

      char buffer[100];
      sprintf(buffer, "%f %f %f", t, hic, h);
      root["message"] = buffer;

      root.printTo(Serial);

      String jsonString;
      root.printTo(jsonString);

      client.setCACert(root_ca);

      if (client.connect(server_host, server_port)) {
        Serial.println("Connected to server!");
        client.println(jsonString);
        client.stop();
      } else {
        Serial.println("Connection failed!");
      }
    }
  }

  delay(5000); // Every 5 seconds
}


