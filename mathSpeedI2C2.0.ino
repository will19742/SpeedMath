/* Speed Game made by Desarrollo de software
31/08/2022 */
#include <Keypad.h>
#include <LiquidCrystal_I2C.h> //LCD library
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte sad[8] = {
  B00000,
  B01010,
  B01010,
  B00000,
  B00000,
  B01110,
  B10001,
};

unsigned long time=0;
unsigned long inicio=0;
int m, mu=0,md=0;             
int s, su=0,sd=0;
int c,cu,cd=0;
byte intento=0;

char level;
boolean modePlay=false;
int cifra_azar;
int numero1=0;
int numero2=0;
int numero3=0;
int temp=0;
int resultado;
String operando="";
String sResultado;
String sLevel;
int largo=0;
boolean activar=false;
boolean temporizar = false;


char cifra_jugador[4]; //Almacena el número del jugador

String numero_jugador = String(); //Almacena las 4 cifras del jugador
String sNumero_jugador;


int cuenta=0;
int i,j,x;
int puntos,famas=0;
int intentos=0;
int maximo_intentos=10;

const byte ROWS=4;
const byte COLS=4;
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};
byte rowPins[ROWS] = {13,6,5,4}; //Filas(pines del 9 al 6)
byte colPins[COLS] = {3,2,1,0}; //Columnas (pines del 5 al 2)
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



void game_over()
{
  temporizar=false;
  modePlay=false;
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Juego terminado");
   delay (1000);
  lcd.clear();
 
  lcd.setCursor(1,0);
  lcd.print("Gracias x jugar");
  lcd.setCursor(0,1);
  lcd.print("Tiempo: ");
  lcd.print(md);
  lcd.print(mu);
  lcd.print(":");
  lcd.print(sd);
  lcd.print(su); 
  lcd.print(":");
  lcd.print(cd);
  lcd.print(cu); 

}

void generate_random()
{
    lcd.clear();
    cuenta=0;
    sResultado="";
    sNumero_jugador="";
   
    randomSeed(analogRead(analogRead(0)));
    
    switch(level)
    {
      case '1':
  
       numero1=random(1,11);  //Generar un número aleatorio entre 1 and 10
       numero2=random(1,11);  //Generar un número aleatorio entre 1 and 10     
       break;

      case '2':
      
       numero1=random(50,100);  //Generar un número aleatorio entre 50 and 99
       numero2=random(1,11);  //Generar un número aleatorio entre 1 and 10
       break;

        
      case '3':
        
       numero1=random(50,100);  //Generar un número aleatorio entre 1 y 99
       numero2=random(50,100);  //Generar un número aleatorio entre 1 y 10     
       break;

      
    }    
    
    numero3=random(1,5);  //Generar un número aleatorio entre 1 and 4
    

    switch(numero3)
    {
      case 1:
        operando="+";
        resultado=numero1+numero2;
        break;
      case 2:
        operando="-";
          if(numero1<numero2)
          {
            temp=numero1;
            numero1=numero2;
            numero2=temp;
          }
        resultado=numero1-numero2;    
    
        break;
       case 3:
        operando="*";
        resultado=numero1*numero2;       
        break;
       case 4:
         operando="/";
         resultado=numero1%numero2;
         if(resultado!=0)  //SI mod no es cero
         {
           operando="*";
           resultado=numero1*numero2;       
         }
         else  //El mod es cero
         {
           resultado=numero1/numero2;
         }
    }
          
    sResultado=  String(resultado);
    
    lcd.setCursor(0,0);
    lcd.print(numero1);
    lcd.setCursor(2,0);
    lcd.print(operando);
    lcd.setCursor(3,0);
    lcd.print(numero2); 
    lcd.setCursor(12,1);
    lcd.print(cuenta);   

    lcd.setCursor(0,1);  
    lcd.print("    ");
    lcd.setCursor(0,1);  

     
}

void timer()
{
    
   if(modePlay==true)
   {
    time = millis()-inicio;  
    
     m=(time/1000)/60;                 //Minutes
    mu=m%10;                            
    md=(m-mu)/10;                       
       
    s=(time/1000)%60;                 //Seconds
    su=s%10;                            
    sd=(s-su)/10;
    
    c=(time/100)%60;
    cu=c%10;
    cd=(c-cu)/10;
    
    lcd.setCursor(8,0);
    lcd.print(md);
    lcd.print(mu);
    lcd.print(":");
    lcd.print(sd);
    lcd.print(su); 
    lcd.print(":");
    lcd.print(cd);
    lcd.print(cu); 
    
    
   }
   
}

void setup() 
  {
Wire.begin();//Lo añadí para convertir lcd a lcd con interfaz I2C 
lcd.createChar(1,sad); 
lcd.begin(16,2); 
lcd.backlight (); //Lo añadí para convertir lcd a lcd con interfaz I2C 
lcd.clear ();  //Lo añadí para convertir lcd a lcd con interfaz I2C 
choose(); //Displays the select level mode

  
  }
  
//********************************************************
void verificar()
{
  if(sNumero_jugador==sResultado)
  {  
    
    lcd.setCursor(6,0);
    lcd.print("G");

    intento=intento+1;    
    
    generate_random();
 
  }
 
  else
 
  {
   
    
    lcd.setCursor(0,1);   
    
    cuenta=0;
    
    sNumero_jugador="";
    
    lcd.setCursor(6,1);
    lcd.write(byte(1));  //Esto escribe la carita :(
   
  }
  
 lcd.setCursor(3,1);
  lcd.print("Resuelto:");
  lcd.print(intento);
  lcd.print("/10");
  
  if(intento==maximo_intentos)
  {
    game_over();  // Ends the game
  }

}

void choose()
{
  
  modePlay=false;
  intento=0;
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("BIENVENIDO/A");
  lcd.setCursor(2,1);
  lcd.print("DS SOFTWARE");
  delay (3000);
  
  /*lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("FERIA CIMAT");
  delay (2000);*/

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Selec. nivel");
  lcd.setCursor(0,1);
  lcd.print("1-F   2-M    3-D");

}

void conteo()
{
  lcd.clear();
  
  lcd.setCursor(4,0);
  
  lcd.print(sLevel);
  
  delay(1000);
  
  lcd.clear();

  for(int x=3;x>=1;x--)
  {
  lcd.setCursor(8,0);
  
  lcd.print(x);
  
  delay(1000);
  
  
  }
  
lcd.clear();

lcd.setCursor(4,0);
  
lcd.print("Empieza!");

delay(600);


generate_random();
  
modePlay=true;
  
  if(activar==false)
    {
      inicio=millis();
      activar=true;
    }

}


void loop()
{
  timer();
  
// pon tu código principal aquí, para ejecutar repetidamente:
  
  char key = keypad.getKey();
  
  if(key)
  


  {   
//Si es la pantalla de selección de nivel

    if(modePlay==false)    
      {
        if(key=='1' || key=='2' || key=='3')
      {
          level=key;
          
          lcd.clear();
         
          lcd.setCursor(5,1);
  
          switch(level)
          {
            case '1':
            
              sLevel="NIVEL FACIL";              
              break;
            case '2':
              sLevel="NIVEL MEDIO";
              break;
            case '3':
              sLevel="NIVEL DIFICIL";
              break;
            
          } //fin switch
   
          conteo();       

        } // fin IF tecla selección de nivel
          
      } //fin IF modo play off
      
      else
      //Modo de jugador
      
      {
        
           temporizar=true;
        
           if(activar==false)
          {
            inicio=millis();
            activar=true;
            lcd.clear();
          }        
          
        
        if(key!='A' && key!='B' && key!='C' && key!='D')
       {
         
        cifra_jugador[cuenta] = key;
        
        numero_jugador = String(key);
        
        sNumero_jugador=sNumero_jugador+numero_jugador;
      
        lcd.setCursor(0+cuenta,1);
        
        lcd.print(cifra_jugador[cuenta]);
        
        cuenta++;                     
        
       largo=sResultado.length();
       
       if(cuenta==largo)
        {
          //        lcd.setCursor(10,1);
          verificar();
        }

         
       } //Fin if key!=   
      
        
      } // Fin sino mode player
      
      
        if(key=='A')
        {  
          modePlay=false;
          inicio=millis();
          activar=false; 
          choose(); 

        }
   
  }    //Fin if Key main
 


} //Fin loop
