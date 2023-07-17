#include <Arduino.h>
#if defined(ESP32) || defined(PICO_RP2040)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <string.h>
#include <Firebase_ESP_Client.h>

#include <addons/TokenHelper.h>

#include <addons/RTDBHelper.h>

String a ;

//const a;
#define WIFI_SSID "ENTER YOUR WIFI SSID"
#define WIFI_PASSWORD "ENTER YOUR WIFI PASSWORD"

#define API_KEY "ENTER YOUR FIREBASE API KEY"

#define DATABASE_URL "ENTER YOUR RTDB URL" 

#define USER_EMAIL "ENTER YOUR FIREBASE AUTHENTICATION SECTION EMAIL"
#define USER_PASSWORD "ENTER YOUR FIREBASE AUTHENTICATION SECTION PASSWORD"

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;
int z = 2;
int b = 4;
int c = 5;
int d = 12;
int e = 13;
int f = 14;
int g = 15;
int h = 16;

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif
 
 int NUMBER9[]={1,1,1,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,1,1,1,1,1,1,1};
 int NUMBER8[]={0,1,1,0,1,1,1,0, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 0,1,1,0,1,1,1,0};
 int NUMBER7[]={1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0, 1,0,0,0,1,0,0,0, 1,0,0,1,1,1,1,1, 1,1,1,0,1,0,0,0};
 int NUMBER6[]={1,1,1,1,1,1,1,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,1,1,1};
 int NUMBER5[]={1,1,1,1,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,1,1,1};
 int NUMBER4[]={1,1,1,1,0,0,0,0, 0,0,0,1,0,0,0,0, 0,0,0,1,0,0,0,0, 0,0,0,1,0,0,0,0, 1,1,1,1,1,1,1,1};
 int NUMBER3[]={1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,1,1,1,1,1,1,1};
 int NUMBER2[]={1,0,0,0,0,0,1,1, 1,0,0,0,0,1,0,1, 1,0,0,0,1,0,0,1, 1,0,0,1,0,0,0,1, 0,1,1,0,0,0,0,1};
 int NUMBER1[]={0,0,1,0,0,0,0,0, 0,1,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
 int NUMBER0[]={1,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,1,1,1,1,1,1,1};

 int _[] = {0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};
 int A[] = {1,1,1,1,1,1,1,1, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 1,1,1,1,1,1,1,1};
 int B[] = {1,1,1,1,1,1,1,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 0,1,1,0,1,1,1,0};
 int C[] = {0,0,1,1,1,1,0,0, 0,1,0,0,0,0,1,0, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1};
 int D[] = {1,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 0,1,0,0,0,0,1,0, 0,0,1,1,1,1,0,0};
 int E[] = {1,1,1,1,1,1,1,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1, 1,0,0,1,0,0,0,1};
 int F[] = {1,1,1,1,1,1,1,1, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0};
 int G[] = {0,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,1,1,0};
 int H[] = {1,1,1,1,1,1,1,1, 0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0, 0,0,0,0,1,0,0,0, 1,1,1,1,1,1,1,1};
 int I[] = {1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1};
 int J[] = {0,0,0,0,0,1,1,0, 0,0,0,0,1,0,0,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 1,1,1,1,1,1,1,0};
 int K[] = {1,1,1,1,1,1,1,1, 0,0,0,1,1,0,0,0, 0,0,1,0,0,1,0,0, 0,1,0,0,0,0,1,0, 1,0,0,0,0,0,0,1};
 int L[] = {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1};
 int M[] = {1,1,1,1,1,1,1,1, 0,1,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,1,0,0,0,0,0,0, 1,1,1,1,1,1,1,1};
 int N[] = {1,1,1,1,1,1,1,1, 0,0,1,0,0,0,0,0, 0,0,0,1,1,0,0,0, 0,0,0,0,0,1,0,0, 1,1,1,1,1,1,1,1};
 int O[] = {0,1,1,1,1,1,1,0, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,1, 0,1,1,1,1,1,1,0};
 int P[] = {1,1,1,1,1,1,1,1, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 1,0,0,1,0,0,0,0, 0,1,1,0,0,0,0,0};
 int Q[] = {0,1,1,1,1,1,1,0, 1,0,0,0,0,0,0,1, 1,0,0,0,0,1,0,1, 0,1,1,1,1,1,1,0, 0,0,0,0,0,0,0,1};
 int R[] = {1,1,1,1,1,1,1,1, 1,0,0,1,1,0,0,0, 1,0,0,1,0,1,0,0, 1,0,0,1,0,0,1,0, 0,1,1,0,0,0,0,1};
 int S[] = {0,1,1,1,0,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,0,0,1, 1,0,0,0,1,1,1,0};
 int T[] = {1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0};
 int U[] = {1,1,1,1,1,1,1,0, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,1, 1,1,1,1,1,1,1,0};
 int V[] = {1,1,1,1,1,1,0,0, 0,0,0,0,0,0,1,0, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,1,0, 1,1,1,1,1,1,0,0};
 int W[] = {1,1,1,1,1,1,1,1, 0,0,0,0,0,0,1,0, 0,0,0,0,0,1,0,0, 0,0,0,0,0,0,1,0, 1,1,1,1,1,1,1,1};
 int X[] = {1,1,0,0,0,0,1,1, 0,0,1,0,0,1,0,0, 0,0,0,1,1,0,0,0, 0,0,1,0,0,1,0,0, 1,1,0,0,0,0,1,1};
 int Y[] = {1,1,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,1,1,1,1,1, 0,0,1,0,0,0,0,0, 1,1,0,0,0,0,0,0};
 int Z[] = {1,0,0,0,0,1,1,1, 1,0,0,0,1,0,0,1, 1,0,0,1,0,0,0,1, 1,0,1,0,0,0,0,1, 1,1,0,0,0,0,0,1};
 int* alpha[]= {A,B,C,D,E,F,G,H,I,J,K,L,M,N};//,T,U,V,W,X,Y,Z};
 int letterSpace;
 int dotTime;
 int i;
 void setup()
 { Serial.begin(115200);
// setting the ports of the leds to OUTPUT(SExperiments)

pinMode(z,OUTPUT);
pinMode(b,OUTPUT);
pinMode(c,OUTPUT);
pinMode(d,OUTPUT);
pinMode(e,OUTPUT);
pinMode(f,OUTPUT);
pinMode(g,OUTPUT);
pinMode(h,OUTPUT);

// defining the space between the letters (ms)
 letterSpace = 6;
 // defining the time dots appear (ms)
 dotTime = 1;
 #if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  multi.addAP(WIFI_SSID, WIFI_PASSWORD);
  multi.run();
#else
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    if (millis() - ms > 10000)
      break;
#endif
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  config.api_key = API_KEY;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.database_url = DATABASE_URL;

  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h


#if defined(ESP8266)
  fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);
#endif

  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  config.wifi.clearAP();
  config.wifi.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif

  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;
}
 void printLetter(int letter[])
 {
 int y;
// printing the first y row of the letter
 for (y=0; y<16; y++)
 {
 digitalWrite(y+2, letter[y]);
 }
 delay(dotTime);
// printing the second y row of the letter
 for (y=0; y<16; y++)
 {
 digitalWrite(y+2, letter[y+16]);
 }
 delay(dotTime);
// printing the third y row of the letter
//(SExperiments)
 for (y=0; y<16; y++)
 {
 digitalWrite(y+2, letter[y+32]);
 }
 delay(dotTime);
 for(y=0; y<16; y++) 
 {
 digitalWrite(y+2, letter[y+48]);
 }
 delay(dotTime);
for(y=0; y<16; y++)
 {
 digitalWrite(y+2, letter[y+64]);
 }
 delay(dotTime);
 // printing the sspace between the letters
//(SExperiments)
 for (y=0; y<16; y++)
 {
 digitalWrite(y+2, 0);
 }
 delay(letterSpace);
 }
 
 void loop()//write here =) 
 {
  if (Firebase.ready())
  {
    sendDataPrevMillis = millis();

    a =  Firebase.RTDB.getString(&fbdo, F("/test/string")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str();

    Serial.printf("a: %s\n\n", a);
    for(i=0; i<16; i++){
      char c = a[i];
      if (std::string(1, c) == std::string("A")){
        printLetter(A);
        }
      if (std::string(1, c) == std::string("B")){
        printLetter(B);
        }
      if (std::string(1, c) == std::string("C")){
        printLetter(C);
        }
      if (std::string(1, c) == std::string("D")){
        printLetter(D);
        }
      if (std::string(1, c) == std::string("E")){
        printLetter(E);
        }
      if (std::string(1, c) == std::string("F")){
        printLetter(F);
        }
      if (std::string(1, c) == std::string("G")){
        printLetter(G);
        }
      if (std::string(1, c) == std::string("H")){
        printLetter(H);
        }
      if (std::string(1, c) == std::string("I")){
        printLetter(I);
        }
      if (std::string(1, c) == std::string("J")){
        printLetter(J);
        }
      if (std::string(1, c) == std::string("K")){
        printLetter(K);
        }
      if (std::string(1, c) == std::string("L")){
        printLetter(L);
        }
      if (std::string(1, c) == std::string("M")){
        printLetter(M);
        }
      if (std::string(1, c) == std::string("N")){
        printLetter(N);
        }
      if (std::string(1, c) == std::string("O")){
        printLetter(O);
        }
      if (std::string(1, c) == std::string("P")){
        printLetter(P);
        }
      if (std::string(1, c) == std::string("Q")){
        printLetter(Q);
        }
      if (std::string(1, c) == std::string("R")){
        printLetter(R);
        }
      if (std::string(1, c) == std::string("S")){
        printLetter(S);
        }
      if (std::string(1, c) == std::string("T")){
        printLetter(T);
        }
      if (std::string(1, c) == std::string("U")){
        printLetter(U);
        }
      if (std::string(1, c) == std::string("V")){
        printLetter(V);
        }
      if (std::string(1, c) == std::string("W")){
        printLetter(W);
        }
      if (std::string(1, c) == std::string("X")){
        printLetter(X);
        }
      if (std::string(1, c) == std::string("Y")){
        printLetter(Y);
        }
      if (std::string(1, c) == std::string("Z")){
        printLetter(Z);
        }
      else {
        printLetter(_);
        }                     
      }
    FirebaseJson json;
    count++;
  }
}
