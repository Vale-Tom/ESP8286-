#include <SoftwareSerial.h>

SoftwareSerial seriale(9,10);

int tensione;
String termine="\r\n";//sequenza che termina le richieste inviate
String comando;//stringa utilizzata per assemblare il comando
String lung;//stringa utilizzata per inviare la lungheza della richiesta

void setup() {
  // put your setup code here, to run once:
seriale.begin(9600);
seriale.print("AT+CWMODE=1"+termine);//imposto l'esp come stazione 
delay(2000);
seriale.print("AT+CIPMUX=1"+termine);//imposto l'esp per poter aprire più connessioni
delay(2000);
seriale.print("AT+CWJAP=\"vale\",\"prova1234\"\r\n");//connetto al wifi
delay(8000);
}


void loop() {
  // put your main code here, to run repeatedly:
seriale.print("AT+CIPSTART=0,\"TCP\",\"api.thingspeak.com\",80\r\n");//apro la connessione con thingspeak
delay(2000);//aspetto che il modulo risponda
//costruzione comando
comando="GET /update?api_key=KXF7WXQ77LKCGZUQ&field1=";//imposto la stringa per la costruzione del comando
comando+=analogRead(A0);//inserisco il valore analogico da caricare
comando+=termine;//inserisco la sequenza che indica la fine del comando
//costruzione richiesta di invio
lung="AT+CIPSEND=0,";//imposto la base del comando per la richiesta
lung+=comando.length();//inserisco la lunghezza della richiesta
lung+=termine;//inserisco la sequenza che indica la fine del comando
seriale.println(lung);//stampo la stringa contenente la richiesta
delay(2000);//attendo che il modulo risponda
seriale.println(comando);//invio il comando
delay(10000);//attendo la fine della richiesta
}
