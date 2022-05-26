/**
 * Accende un led RGB in accordo con una stringa decimale
 * letta dalla porta seriale.
 * Formato della stringa decimale: RRR,GGG,BBB 
 * 
 * @author     Sandro Tributi <tributi.sandro@curiepergine.it>
 * @copyright  CC BY
 */
 
// Pin led RGB
#define pinRed 9
#define pinGreen 10
#define pinBlue 11

// Variabili
String decStr; // stringa letta dalla porta seriale
byte r, g, b;  // valori decimali RGB (0-255)
int posComma;
byte commas[2];

void setup() {
  // inizializzazione porta seriale
  Serial.begin(9600);
  // inizializzazione pin dove è collegato il led RGB
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);    
}

void loop() {
  // se ci sono byte da leggere sulla seriale...
  if (Serial.available() > 0) {
    // lettura della stringa
    decStr = Serial.readStringUntil('\n');
    decStr.trim();        // elimina spazi
    posComma = 0;
    for (int i = 0; i < decStr.length(); i++) {
      if (decStr.charAt(i) == ',') {
        commas[posComma] = i;
        posComma++;
      }
    }
    r = decStr.substring(0, commas[0]).toInt();
    g = decStr.substring(commas[0] + 1, commas[1]).toInt();
    b = decStr.substring(commas[1] + 1, decStr.length()).toInt();
    // accende il led RGB
    setColor(pinRed, pinGreen, pinBlue, r, g, b);
    // stampa valori sul monitor seriale
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.println(b);
  }
}

void setColor(byte pinR, byte pinG, byte pinB, byte red, byte green, byte blue) {
  analogWrite(pinR, red);
  analogWrite(pinG, green);
  analogWrite(pinB, blue);
}
