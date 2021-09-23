#include <IRremote.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#define MAX_DEVICES 10
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define PIN_RECEIVER 2
#define SPEED_TIME 70
#define PAUSE_TIME  500
#define CLK_PIN   13 
#define DATA_PIN  11 
#define CS_PIN    10 
MD_Parola mx = MD_Parola(MD_MAX72XX::PAROLA_HW, CS_PIN, MAX_DEVICES);
IRrecv receiver(PIN_RECEIVER);

boolean ligado = false; // on-off
// contadores

int num1 = 0;
int num2 = 0; 
int num3 = 0;
int num4 = 0;
int num5 = 0;
int num6 = 0;
int num7 = 0;
int num8 = 0;
int num9 = 0;
//letras por tecla
String letra1[] = {"A","B","C"};
String letra2[] = {"D","E","F"};
String letra3[] = {"G","H","I"};
String letra4[] = {"J","K","L"};
String letra5[] = {"M","N","O"};
String letra6[] = {"P","Q","R"};
String letra7[] = {"S","T","U"};
String letra8[] = {"V","W","X"};
String letra9[] = {"Y","Z"," "};

boolean tela = true;
String texto;
String letra = "";
boolean menu = false;
int indice = 0;
int start = 0;
char buf[100];
String muda_frase;
int atualizou;
// PARA APENAS TESTAR OS EFEITOS COM PALAVRAS PRONTAS DESCOMENTE AS 2 LINHAS A BAIXO
String palavras[] = {"","TEXT DISPLAY","ABC","IFAL"};
int num_palavras = 3;
// String palavras[] = {};
// int num_palavras = 0;

textEffect_t entrada[] = {PA_NO_EFFECT,PA_SCROLL_LEFT,PA_SCROLL_RIGHT,PA_SCROLL_DOWN, PA_SCROLL_UP };
textEffect_t saida[] = {PA_NO_EFFECT,PA_SCROLL_LEFT,PA_SCROLL_RIGHT,PA_SCROLL_DOWN, PA_SCROLL_UP };
int efeito_entrada = 0;
int efeito_saida = 0;

void setup()
{

  //mx.setZone(0,  MAX_DEVICES - 6, MAX_DEVICES - 1);
  
  receiver.enableIRIn();
  Serial.begin(11200);
  Serial.println("1(ABC) 2(DEF) 3(GHI) 4(JKL) 5(MNO) 6(PQR) 7(STU) 8(VWX) 9(YZ-) " );
  Serial.println("Aperte C para confirmar a letra");
  Serial.println("Aperte TEST para apagar a palavra que você esta digitando ");
  Serial.println("Aperte 0 para alternar entre a frase e letra");
  Serial.println("Aperte ▶ para salvar a frase");
  Serial.println("Aperte MENU para ir para as frases salvas e + e - enquanto está no menu para alternar entre as frases");
  Serial.println("Aperte ⇦ ou ⇨ para alternar entre os efeitos");
  mx.begin();
  }
void loop()
{    
    if(atualizou != indice){
      muda_frase = palavras[indice] ;
      muda_frase.toCharArray(buf,100); 
      atualizou = indice;
      }

  if (mx.displayAnimate() && menu == true && ligado == true){
     mx.displayText(buf, PA_CENTER, SPEED_TIME, PAUSE_TIME, entrada[efeito_entrada],saida[efeito_saida]);}
  if (receiver.decode()) 
  { receptor();
    receiver.resume();  }
  if(tela == true && menu == false && ligado == true)  {
    mx.print(letra);  }
  if(tela == false && menu == false && ligado == true)  {
    mx.print(texto); }
  //if(menu == true && ligado == true){
   //mx.print(palavras[indice]);}
  }

    


int letra_ocupada(int &num,String letras[])
{
  if(ligado == true){
    if(letra == "" || num != 0 ){
      if (num <3){
        num +=1;}
      else{num = 1;}
      
      letra = letras[num-1];
      return num;}
  }}




void receptor()
{  
  switch (receiver.decodedIRData.command) {
    case 162: //power
      if(ligado == false){ 
        mx.setTextAlignment(PA_CENTER);
        mx.print("ON");
        delay(500);
        mx.displayClear();
        ligado = true;}
      else{ 
        mx.displayClear();
        mx.print("OFF");
        delay(500);
        mx.displayClear();
        ligado = false;
        texto = "";
        letra = "";
        num1 = num2 = num3 = num4 = num5 = num6 = num7 = num8 = num9 = 0;}
        break;
    case 48: // 1
      letra_ocupada(num1,letra1); 
      break;
    case 24: // 2
      letra_ocupada(num2,letra2);
      //num_ocupado(1);
      break;
    case 122: // 3
      letra_ocupada(num3,letra3);
      break;
    case 16: // 4
      letra_ocupada(num4,letra4);
      break;
    case 56: // 5
      letra_ocupada(num5,letra5);
      break;
    case 90: // 6
      letra_ocupada(num6,letra6);
      break;
    case 66: // 7
      letra_ocupada(num7,letra7);
      break;
    case 74: // 8
      letra_ocupada(num8,letra8);
      break;
    case 82: // 9
      letra_ocupada(num9,letra9);
      break;

    case 176: // C
      if(letra != "")
      {
        texto += letra;
        letra = "";
        num1 = num2 = num3 = num4 = num5 = num6 = num7 = num8 = num9 = 0;}
        break;
    case 168: // ▶
      num_palavras += 1;
      palavras[num_palavras] = texto;
      texto = "";
      break;

    case 104: // 0
    menu = false;
    if(tela == true){
      tela = false; }
    else{
      tela = true;}
    break;

    case 34: // test
    texto = "";
    letra = "";
    break;

    case 226: //menu
    indice = 1;
    if(menu == false){
      menu = true;}
    else if(menu == true){
      menu = false;}
    break;

    case 2: // +
    if(menu == true){
      if(indice < num_palavras){
      indice ++;}
      else{indice = 1;}}
      break;
    case 152: // -
    if(menu == true){
    if(indice > 1){
      indice -= 1;}
      else{indice = num_palavras;}}
    break;
    case 224: // <-
    if(menu == true){
    if(efeito_entrada == 4){
      efeito_entrada = 0;}
      else{efeito_entrada ++;}}
    break;
    case 144: // ->
    if(menu == true){
    if(efeito_saida == 4){
      efeito_saida = 0;}
      else{efeito_saida ++;}}
    break;

  }
}
    
    
     
