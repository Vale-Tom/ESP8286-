#include <SoftwareSerial.h>

SoftwareSerial seriale(9, 10);

String termine = "\r\n";  //sequenza che termina le richieste inviate
String comando;           //stringa utilizzata per assemblare il comando
String lung;              //stringa utilizzata per inviare la lungheza della richiesta

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  seriale.begin(9600);
  seriale.print("AT+CWMODE=1" + termine);  //imposto l'esp come stazione
  delay(2000);
  seriale.print("AT+CIPMUX=1" + termine);  //imposto l'esp per poter aprire più connessioni
  delay(2000);
  seriale.print("AT+CWJAP=\"vale\",\"prova1234\"\r\n");  //connetto al wifi
  checkok(0);
  delay(8000);
}

bool checkok(int flagTypeMsg) {  //funzione per verificare se il modulo risponde con "ok"

  /*
  while(seriale.available()==0){}//attendo che il modulo risponda
  if(seriale.read()=='O'){//se la prima lettera ricevuta è una O allora aspetto la k
    if(seriale.read()=='K'){//e la seconda lettera è K allora il modulo ha risposto OK
      seriale.flush();
      Serial.println("ok");
      return 1;
    }
  }
  */
  String buff = "";
  Serial.println("testok");
  while (seriale.available() == 0) {}
  while (seriale.available() > 0) {
    Serial.write(seriale.peek());
    buff += seriale.read();
  }
  switch (flagTypeMsg)

  {
    case 0:   //ok
      if (buff.lastIndexOf("OK") >= 0)
      {
      Serial.println("tOK");
      return true;
      }
      break;
    
    case 1:       //Linked
      if (buff.lastIndexOf("Linked") >= 0)
      {
      Serial.println("Connection to website ok");
      return true;
      }
      break;    


  }

  return false;
}

void loop() {
  // put your main code here, to run repeatedly:
  seriale.flush();
  seriale.print("AT+CIPSTART=0,\"TCP\",\"api.thingspeak.com\",80\r\n");  //apro la connessione con thingspeak
  /*00000000000000000000*/
  checkok(1);

  //checkok(0);//controllo se la connessione è andata a buon fine
  //costruzione comando
  comando = "GET /update?api_key=KXF7WXQ77LKCGZUQ&field1=";  //imposto la stringa per la costruzione del comando
  comando += analogRead(A0);                                 //inserisco il valore analogico da caricare
  comando += termine;                                        //inserisco la sequenza che indica la fine del comando
  //costruzione richiesta di invio
  lung = "AT+CIPSEND=0,";    //imposto la base del comando per la richiesta
  lung += comando.length();  //inserisco la lunghezza della richiesta
  lung += termine;           //inserisco la sequenza che indica la fine del comando
  //seriale.flush();           //prima di effettuare la richiesta pulisco il buffer di ricezione per essere sicuro di leggere correttamente "ok"
  seriale.println(lung);     //stampo la stringa contenente la richiesta
  checkok(0);
  delay(5000);
  seriale.flush();
  Serial.println(comando);
  seriale.print(comando);  //invio il comando
  checkok(0);                 //controllo ok
  delay(10000);
}
