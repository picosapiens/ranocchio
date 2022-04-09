#define ADCBUFFERSIZE  900
#define ADCPIN    0

uint16_t ADCCounter=0;
uint8_t ADCBuffer[ADCBUFFERSIZE];
uint32_t dtbuffered_ns; // nominal time step
long int datafreq_Hz;

// Defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void setscalefactor( int fac )
{
  switch(fac)
 {
  case 2:
    cbi(ADCSRA,ADPS2);
    cbi(ADCSRA,ADPS1);
    sbi(ADCSRA,ADPS0);
    dtbuffered_ns = 1625;
    break;
  case 4:
    cbi(ADCSRA,ADPS2);
    sbi(ADCSRA,ADPS1);
    cbi(ADCSRA,ADPS0);
    dtbuffered_ns = 3250;
    break;
  case 8:
    cbi(ADCSRA,ADPS2);
    sbi(ADCSRA,ADPS1);
    sbi(ADCSRA,ADPS0);
    dtbuffered_ns = 6500;
    break;
  case 16:
    sbi(ADCSRA,ADPS2);
    cbi(ADCSRA,ADPS1);
    cbi(ADCSRA,ADPS0);
    dtbuffered_ns = 13000;
    break;
  default: // case 32
    sbi(ADCSRA,ADPS2);
    cbi(ADCSRA,ADPS1);
    sbi(ADCSRA,ADPS0);
    dtbuffered_ns = 26000;
    break;
 }
}

int sum3(int i) // to filter out noise
{
  return ADCBuffer[(ADCCounter+i-1)%ADCBUFFERSIZE]+ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE]+ADCBuffer[(ADCCounter+i+1)%ADCBUFFERSIZE];
}

void analyzeData()
{
  // Identify signal mean
  uint8_t swingline(0);
  uint8_t datamin = 255;
  uint8_t datamax = 0;
  uint32_t firstpcrossing;
  uint32_t lastpcrossing;
  uint32_t foundpcrossings = 0;
  for(int i = 0; i<ADCBUFFERSIZE; i++)
  {
    if( ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE] > datamax )
      datamax = ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE];
    if( ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE] < datamin )
      datamin = ADCBuffer[(ADCCounter+i)%ADCBUFFERSIZE];
  }
  swingline = (datamax+datamin)/2;

  // Find positive crossings of the mean signal
  for(int i=1; i<ADCBUFFERSIZE-1; i++)
  {
    if ((sum3(i) <= swingline*3) && (sum3(i + 1) > swingline*3)) // triple swingline because using sum3
    {
      if(0==foundpcrossings) {
        firstpcrossing = i + ((3*swingline - sum3(i))) / ( sum3(i+1) - sum3(i) );
        lastpcrossing = firstpcrossing;
      } else {
        lastpcrossing = i + ((3*swingline - sum3(i))) / ( sum3(i+1) - sum3(i) );
      }
      foundpcrossings++;
    }
  }

  // Calculate period and frequency
  long int dataperiod_us = (lastpcrossing-firstpcrossing)*dtbuffered_ns/1000/(foundpcrossings-1);
  datafreq_Hz = (long int)1000000/dataperiod_us;
}
  
void setup() {
  // Set voltage reference
  cbi(ADMUX,REFS1);
  sbi(ADMUX,REFS0);
  
  // Left adjust results
  sbi(ADMUX,ADLAR);

  // Set analog pin
  #ifndef __AVR_ATmega2560__
  ADMUX |= ( ADCPIN & 0x07 ); // Simple on Uno
  #else __AVR_ATmega2560__
  cbi(ADMUX,MUX0); // Is all this necessary?
  cbi(ADMUX,MUX1);
  cbi(ADMUX,MUX2);
  cbi(ADMUX,MUX3);
  cbi(ADMUX,MUX4);
  //cbi(ADCSRB,MUX5);
  ADMUX |= ( ADCPIN & 0x07 );
  #warning uncertain implementation on mega
  // Mega has more ADMUX options, and one of the bits is in ADCSRB
  if (ADCPIN >= 8 )
    ADCSRB |= _BV(MUX5);
  else
    ADCSRB &= ~_BV(MUX5);
  #endif

  // ADC off
  cbi(ADCSRA,ADEN);

  // Bit used to start ADC when the time comes
  cbi(ADCSRA,ADSC);

  // Use trigger to start ADC
  sbi(ADCSRA,ADATE);

  // I'm not using interrupts here - I just want to poll the result
  cbi(ADCSRA,ADIE);

  // Free running mode (trigger a new sample as soon as the previous result is ready)
  cbi(ADCSRB,ADTS2);
  cbi(ADCSRB,ADTS1);
  cbi(ADCSRB,ADTS0);

  Serial.begin(115200);
  Serial.println("Hello");
  
}

void loop() {
  
  setscalefactor( 4 );
  ADCCounter=0;
  int stopIndex = ADCCounter;
  memset( (void *)ADCBuffer, 0, sizeof(ADCBuffer) ); // clear buffer
  noInterrupts();
  // Enable ADC
  sbi(ADCSRA,ADEN);
  // Start conversion
  sbi(ADCSRA,ADSC);

  while(true)
  {
    while( !(ADCSRA&(1<<ADIF)) ); // Wait for result (In free running mode so can't use ADSC to check for completion
    ADCBuffer[ADCCounter] = ADCH; // Grab sample
    sbi(ADCSRA,ADIF); // Apparently writing 1 clears it
    ADCCounter = ADCCounter+1;
    if( ADCBUFFERSIZE == ADCCounter)
      break;
  }

  // Stop ADC
  cbi(ADCSRA,ADEN);
  interrupts();

  analyzeData();

  Serial.print("Apparent data frequency (Hz): "); Serial.println(datafreq_Hz);
}
