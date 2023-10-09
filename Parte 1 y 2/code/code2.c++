/**
 * @brief C++
 * Autor: Jerónimo Delmar
 * Parcial 1
 * Comisión: 1D
 * 2023
 */
#define MOTOR 3
#define UP 2      // BOTON UP = PIN 2
#define DOWN 12    // BOTON DOWN = PIN 3
#define SLIDER 4
#define UNITS A5  // CATODO UNIDADES = PIN A5
#define TENS A4   // CATODO DECENAS = PIN A4
int units;        // GLOBAL INT VAR 'units'
int tens;         // GLOBAL INT VAR 'tens'
bool primes;      // GLOBAL BOOL VAR 'primes'
const int pinNumbers[] = {10, 11, 7, 6, 5, 9, 8}; // ARRAY DE PINES - {A, B, C, D, E, F, G};

void setup()
{
  units = 0;
  tens = 0;
  pinMode(UP, INPUT_PULLUP);    // BOTON UP
  pinMode(DOWN, INPUT_PULLUP);  // BOTON DOWN
  pinMode(4, INPUT_PULLUP);     // SLIDER PRIMOS
  pinMode(5, OUTPUT);  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(UNITS, OUTPUT);
  pinMode(TENS, OUTPUT);
  Serial.begin(9600);
}

void loop()
{  	
  	if(digitalRead(SLIDER) == LOW)
    {
      primes = true;
      //Serial.println("primos");
    }
  	else
    {
      primes = false;
      //Serial.println("no primos");
    }  
  
  	Input();
  	
  	if(primes == true)
    {
      if(NumberIsPrime() == true)
      {
        DisplayNumbers(1);
        delay(200);
        DisplayNumbers(2);
        delay(200);
      }
      else
      {
        TurnOff();
        delay(500);
      }
    }
    else
    {
        DisplayNumbers(1);
        delay(200);
        DisplayNumbers(2);
        delay(200);
    }
  	//Serial.print(tens);
  	//Serial.println(units);
}

/**
 * @brief Debe correr al inicio.
 * Chequea el boton si se esta recibiendo una señal de input de alguno de los 2 botones y cual, y ejecuta la logica asociada al mismo. 
 */
void Input()
{
  // UP
  if(digitalRead(UP) == LOW)
  {
    if(units < 9)
    {
      units ++;      
    }
    else
    {
      units = 0;
      if (tens < 9)
      {
        tens++;
      }
      else
      {
        tens = 0;
      }
    }    
  }
  // DOWN
  if(digitalRead(DOWN) == LOW)
  {
    if (tens == 0 && units == 0)
    {
      tens = 9;
      units = 9;
    }
    else if (units > 0)
    {
      units--;
    }
    else if (units == 0)
    {
      units = 9;
      if (tens > 0)
      {
        tens--;
      }
    }
  }
  analogWrite(MOTOR, ((tens*10) + units) * 2 );
  return;
}

/**
 * @brief Activa y desactiva los displays de manera alternativa, produciendo el multiplexing.
 * 
 * @param display Int. Valor numerico. 1 para activar las unidades, 2 para activar las decenas. Desactiva el opuesto.
 */
void DisplayNumbers(int display)
{
  switch(display)
  {    
    case 1:
    	digitalWrite(UNITS, HIGH);
    	digitalWrite(TENS, LOW);
    	break;
   	case 2:
    	digitalWrite(UNITS, LOW);
    	digitalWrite(TENS, HIGH);
    	break;
  }
  SetLeds(display);
}

/**
 * @brief Setea los leds para mostrar el numero correspondiente.
 * 
 * @param counter Int. Valor numerico de referencia que indica si los leds que se van a setear deben mostrar las unidades, o las decenas.
 */
void SetLeds(int counter)
{  
	int displayToShow; // Si el valor de 'counter' es 1...
  	if(counter == 1)
    {
      displayToShow = units; // ... se toma el valor de las unidades.
    }
  	else
    {
      displayToShow = tens; // Caso contrario, las decenas.
    }
  
    // Arrays con los estados HIGH/LOW correspondientes a los segmentos {A, B, C, D, E, F, G};
  	int v0[] = {1, 1, 1, 1, 1, 1, 0}; // 0
  	int v1[] = {0, 1, 1, 0, 0, 0, 0}; // 1
  	int v2[] = {1, 1, 0, 1, 1, 0, 1}; // 2
  	int v3[] = {1, 1, 1, 1, 0, 0, 1}; // 3
  	int v4[] = {0, 1, 1, 0, 0, 1, 1}; // 4
    int v5[] = {1, 0, 1, 1, 0, 1, 1}; // 5
    int v6[] = {1, 0, 1, 1, 1, 1, 1}; // 6
    int v7[] = {1, 1, 1, 0, 0, 0, 0}; // 7
    int v8[] = {1, 1, 1, 1, 1, 1, 1}; // 8
    int v9[] = {1, 1, 1, 1, 0, 1, 1}; // 9
  
	switch(displayToShow) // En base al valor unitario a mostrar se le pasa a LedSetter el array correspondiente.
  	{
        case 0:            
            LedSetter(v0);
            break;
        case 1:            
            LedSetter(v1);
            break;
        case 2:            
            LedSetter(v2);
            break;
      	case 3:
      		LedSetter(v3);
      		break;
      	case 4:
      		LedSetter(v4);
      		break;
      	case 5:
      		LedSetter(v5);
      		break;
      	case 6:
      		LedSetter(v6);
      		break;
      	case 7:
      		LedSetter(v7);
      		break;
      	case 8:
      		LedSetter(v8);
      		break;
      	case 9:
      		LedSetter(v9);
      		break;
  	}
}

/**
 * @brief Función que setea el estado HIGH/LOW de los 7 pines correspondientes a los segmentos a mostrar.
 * 
 * @param state Int[]. Recibe 7 valores 0/1.
 */
void LedSetter(int state[])
{
  for(int len = 0; len < 7; len++)
  {
    digitalWrite(pinNumbers[len], state[len]); // Se itera por cada uno de los pines definidos al comienzo. Se setea el valor binario recibido en el array.
  }
}

/**
 * @brief Chequea si el numero actual en el contador global es primo o no. Retorna true si es primo, false si no lo es.
 * 
 * @return true 
 * @return false 
 */
bool NumberIsPrime()
{
  	int number = (tens*10) + units;
  
    if(number <= 1)
    {
        return false;
    }    
    if(number <= 3)
    {
        return true;
    }    
    if (number % 2 == 0 || number % 3 == 0)
    {
        return false;
    }        
    for (int i = 5; i * i <= number; i += 6)
    {
    	if (number % i == 0 || number % (i + 2) == 0)
        {
            return false;
        }
    }
}

/**
 * @brief Apaga ambos displays.
 * 
 */
void TurnOff()
{
  digitalWrite(UNITS, HIGH);
  digitalWrite(TENS, HIGH);
}