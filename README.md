# QtModemSim900Test

Wiki: https://github.com/helmutkemper/Cplusplus/wiki/Modem-SIM900-...--Teste

Na época que eu dava aula de Arduino, meus alunos tinham a necessidade de usar um modem GPRS para pequenos projetos, de forma transparente e clara, por isto, eu fiz a classe **AtModem** em **C++** para eles. Porém, como todo código necessita ser testado, o **Qt** é uma excelente plataforma gratuita para teste em **C++** e este é o código de teste da classe.

Perceba que este código foi feito apenas para teste e não havia a necessidade de um código sustentável, por isto, o mesmo é meio desorganizado.

Caso você queira usar um modem **SIM900** e necessite ver o fluxo de dados, este teste é excelente.

![Aparência do programa](https://github.com/helmutkemper/QtModemSim900Test/blob/master/Captura_de_Tela.png "Aparência do programa")

### Como testar no Arduino

Você vai necessitar de:
-- Arduino Mega;
-- Shield Modem SIM900
-- Cabo USB
-- Sim Card com crédito

Copie o código abaixo no seu Arduino
```
#define kxModemGprsPowerPin 9

long baud;

void setup() {
  Serial.begin ( 115200 );
  Serial1.begin ( 115200 );
}

void loop() {}

void serialEvent ()
{
  int data = Serial.read ();
  
  if ( data == '_' )
  {
    pinMode ( kxModemGprsPowerPin, OUTPUT );
    digitalWrite ( kxModemGprsPowerPin, LOW );
  
    digitalWrite (kxModemGprsPowerPin, HIGH);
    delay ( 1000 );
    digitalWrite ( kxModemGprsPowerPin, LOW );
    return;
  }
  
  Serial1.write ( data );
}

void serialEvent1 ()
{
  int data = Serial1.read ();
  Serial.write ( data );
}
```
Ligue o seu modem na **porta serial 1** do Arduino, alimente o circuito, nem sempre a USB fornece corrente suficiente, e em seguida abra o programa.
Note que para o programa funcionar, a sua porta serial deve está configurada para **115200bps**.

Caso o seu modem esteja com problemas, veja este link:

https://github.com/helmutkemper/Cplusplus/wiki/Modem-SIM900-...--Restaurar
