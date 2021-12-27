#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte znak_c[8] = {0b00010,0b00100,0b01110,0b10000,0b10000,0b10001,0b01110,0b00000};
byte znak_a[8] = {0b00000,0b00000,0b01110,0b00001,0b01111,0b10001,0b01111,0b00010};
byte znak_l[8] = {0b01100,0b00100,0b00110,0b01100,0b00100,0b00100,0b01110,0b00000};
byte znak_z[8] = {0b00100,0b00000,0b11111,0b00010,0b00100,0b01000,0b11111,0b00000};
byte znak_x[8] = {0b00010,0b00100,0b11111,0b00010,0b00100,0b01000,0b11111,0b00000};
byte znak_o[8] = {0b00010,0b00100,0b01110,0b10001,0b10001,0b10001,0b01110,0b00000};
byte znak_n[8] = {0b00010,0b00100,0b10110,0b11001,0b10001,0b10001,0b10001,0b00000};
byte znak_e[8] = {0b00000,0b00000,0b01110,0b10001,0b11111,0b10000,0b01110,0b00010};
byte znak_s[8] = {0b00010,0b00100,0b01110,0b10000,0b01110,0b00001,0b11110,0b00000};

byte znak_C[8] = {0b00010,0b01110,0b10101,0b10000,0b10000,0b10001,0b01110,0b00000};
byte znak_A[8] = {0b01110,0b10001,0b10001,0b11111,0b10001,0b10001,0b10001,0b00010};
byte znak_L[8] = {0b10000,0b10000,0b10010,0b10100,0b11000,0b10000,0b11111,0b00000};
byte znak_Z[8] = {0b00100,0b11111,0b00001,0b00010,0b00100,0b01000,0b11111,0b00000};
byte znak_X[8] = {0b00100,0b11111,0b01001,0b00010,0b00100,0b01000,0b11111,0b00000};
byte znak_O[8] = {0b00010,0b01110,0b10101,0b10001,0b10001,0b10001,0b01110,0b00000};
byte znak_N[8] = {0b00100,0b10101,0b11001,0b10101,0b10011,0b10001,0b10001,0b00000};
byte znak_E[8] = {0b11111,0b10000,0b10000,0b11110,0b10000,0b10000,0b11111,0b00010};
byte znak_S[8] = {0b00010,0b01111,0b10100,0b10000,0b01110,0b00001,0b11110,0b00000};

static const int slownik_size = 18;
static const int pamiec_znakow = 8;
//byte *znak[slownik_size];

struct Slownik{
      char const  *key;
      byte        *value;
      char         ascii;
      bool         used;
      int         memlcd;
    };

Slownik slownik[] = {
    // małe polskie znaki znaki
    {"\xFFFFFFC4\xFFFFFF87", znak_c, 'c', false, 0}, // ć
    {"\xFFFFFFC4\xFFFFFF85", znak_a, 'a', false, 0}, // ą
    {"\xFFFFFFC5\xFFFFFF82", znak_l, 'l', false, 0}, // ł
    {"\xFFFFFFC5\xFFFFFFBC", znak_z, 'z', false, 0}, // ż
    {"\xFFFFFFC5\xFFFFFFBA", znak_x, 'z', false, 0}, // ź
    {"\xFFFFFFC3\xFFFFFFB3", znak_o, 'o', false, 0}, // ó
    {"\xFFFFFFC5\xFFFFFF84", znak_n, 'n', false, 0}, // ń
    {"\xFFFFFFC4\xFFFFFF99", znak_e, 'e', false, 0}, // ę
    {"\xFFFFFFC5\xFFFFFF9B", znak_s, 's', false, 0}, // ś

    // duże polskie znaki znaki
    {"\xFFFFFFC4\xFFFFFF86", znak_C, 'C', false, 0}, // Ć
    {"\xFFFFFFC4\xFFFFFF84", znak_A, 'A', false, 0}, // Ą
    {"\xFFFFFFC5\xFFFFFF81", znak_L, 'L', false, 0}, // Ł
    {"\xFFFFFFC5\xFFFFFFBB", znak_Z, 'Z', false, 0}, // Ż
    {"\xFFFFFFC5\xFFFFFFB9", znak_X, 'Z', false, 0}, // Ź
    {"\xFFFFFFC3\xFFFFFF93", znak_O, 'O', false, 0}, // Ó
    {"\xFFFFFFC5\xFFFFFF83", znak_N, 'N', false, 0}, // Ń
    {"\xFFFFFFC4\xFFFFFF98", znak_E, 'E', false, 0}, // Ę
    {"\xFFFFFFC5\xFFFFFF9A", znak_S, 'S', false, 0}  // Ś
    };

String create(String incomingString){
  String outTekst = incomingString;
  int ilcd = 1; 
  for(int n = 0; n < slownik_size; n++){
    slownik[n].used = false;
  } 
  for(int i = 0; i < incomingString.length(); i++){
    for(byte ipz = 0;  ipz < slownik_size; ipz++){
      if(String(slownik[ipz].key) == incomingString.substring(i,i+2)){
        if (slownik[ipz].used == true){
          //Serial.println("Znalazłem duplikat: " + String(slownik[ipz].key));
          outTekst.replace(String(slownik[ipz].key), String(slownik[ipz].memlcd));
          }
        else if(ilcd <= pamiec_znakow){
        //Serial.println("ilcd "+String(ilcd));
        outTekst.replace(String(slownik[ipz].key), String(char(ilcd)));
        slownik[ipz].used = true;
        slownik[ipz].memlcd = ilcd;
        lcd.createChar(ilcd, slownik[ipz].value);
        ilcd++;}
        else  {
            outTekst.replace(String(slownik[ipz].key), String(slownik[ipz].ascii));}
            i++;
      }
    }
  }
  //Serial.println(outTekst);
  return outTekst; 
}
