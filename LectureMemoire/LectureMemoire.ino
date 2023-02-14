/*
  TV GUARDIAN 1 - 93LC96
  Premier test de communication avec le chip
*/
#define CS 2
#define CLK 3
#define DI 4
#define DO 5

void setup() {
  Serial.begin(57600);
  pinMode(CS, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DI, OUTPUT); //DI du CHIP sera une output sur l'arduino
  pinMode(DO, INPUT); //DO du CHIP sera une input sur l'arduino
  
  digitalWrite(CS, HIGH);   // sélectionne le chip 
  
  //ENVOIE DES COUPS D'HORLOGE POUR LES 11 BITS D'ADRESSES
  word readCmd = 0b11000000000000;   // 1 bit de démarrage et l'opcode de READ
                                         // 10 puis les 11 bits de l'adresse => 1+2+11=14
  word address = 0x00;
  for(address = 0; address < 2048;address++)
  {
    word finalCmd = readCmd | address;
    for(j = 13; j<0;j--)
    {
      digitalWrite(DI, finalCmd >> j & 1);
      digitalWrite(CLK, HIGH);
      digitalWrite(CLK, LOW);
    }
    byte data = 0;
    for(int i = 0;i<8;i++)
    {
      digitalWrite(CLK, HIGH);
      data = (data << 1)|digitalRead(DO);
      digitalWrite(CLK, LOW);
    }
    Serial.println((char)data);
  }
  digitalWrite(CS, LOW);
}

void loop() {
}
