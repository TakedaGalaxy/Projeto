#include <WiFi.h>

#define SSID "----"
#define PASSWD "------"

const uint16_t port = 50000;
const char * host = "192.168.15.6";

WiFiClient *cliente;

void inicializacaoSocket(void){

  WiFi.begin(SSID,PASSWD);
    
}
