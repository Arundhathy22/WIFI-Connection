#include <M5Core2.h>
#include <WiFi.h>
const int MAX_NETWORKS = 5;
const char* SSIDs[] = {"OnePlus Nord CE4", "FMS_TRV01"}; 
const char* Passwords[] = {"d3x8yd42", "JiffyPan23#$"}; 
const int numofNetworks = 2;

int b = 0;  
String ssidList[MAX_NETWORKS];
int numNetworks = 0;  

void scanNetworks() {
  M5.Lcd.setCursor(0, 0);
  int n = WiFi.scanNetworks(); 
  numNetworks = min(n, MAX_NETWORKS);
  M5.Lcd.fillScreen(BLACK);
  for (int i = 0; i < numNetworks ; i++) {
    ssidList[i] = WiFi.SSID(i); 
  }
}

void displayNetworks(){
    M5.Lcd.setCursor(0,0);
    M5.Lcd.fillScreen(BLACK);
    for(int i = 0; i < numNetworks ; i++){
      if (i == b) {
        M5.Lcd.setTextColor(RED, BLACK);
      } else {
        M5.Lcd.setTextColor(WHITE, BLACK);
      }
    M5.Lcd.printf("%d: %s\n", i + 1, ssidList[i].c_str());
  }
}

void connectToNetwork(const String& ssid, const String& password) {
  WiFi.begin(ssid.c_str(), password.c_str()); 
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 10) {
     delay(1000);
     attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) { 
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(GREEN, BLACK);
    M5.Lcd.printf("Connected to %s\n", ssid.c_str());
    M5.Lcd.printf("IP: %s\n", WiFi.localIP().toString().c_str());
  }  
}

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  M5.Lcd.print("WIFI SCAN");
  scanNetworks(); 
  displayNetworks();
}

void loop() {
  M5.update();
  if (M5.BtnA.wasReleased() ){
    b++;
    if(b > numNetworks-1){
      b = 0;  
    }    
    displayNetworks(); 
  }

  if (M5.BtnB.wasReleased()) {
      for (int i = 0; i < numofNetworks; i++) {
        if (ssidList[b] == SSIDs[i]){
          connectToNetwork(ssidList[b], Passwords[i]);
          return;
      }
      }
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.setTextColor(RED, BLACK);
      M5.Lcd.printf("No password for %s\n", ssidList[b].c_str());
  }
  if (M5.BtnC.wasReleased()) {
    displayNetworks();  
  }
}