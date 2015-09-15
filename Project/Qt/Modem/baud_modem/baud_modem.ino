long baud[] = { 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 0 };
int i = 0;


void setup() {
  Serial.begin ( 115200 );
}

void loop() {
  Serial2.begin ( baud[ i ] );
  Serial.println ( baud[ i ] );
  Serial2.write ( "AT+IPR=115200\r\n" );
  delay ( 5000 );
  Serial2.begin ( 115200 );
  while ( Serial2.available () > 0 )
  {
    Serial.write ( Serial2.read() );
  }
  Serial.println();
  i++;
  
  if ( baud[ i ] == 0 )
  {
    Serial.write ("fim!");
    while(true);
  }
}


