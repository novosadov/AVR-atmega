#include <avr/io.h>
#include <stdint.h>                     

#include <avr/interrupt.h>



#define FOSC 16000000                       
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1


volatile char ReceivedChar;

int t;


int main( void )
{
	DDRB=0xFF;               //инициализирует порт В как выход (output)
	//DDRD|=1<<PORTD1;        // таким макаром подаётся логическая 1 на первую ножку порта D
	/*Set baud rate */
	UBRR0H = (MYUBRR >> 8); //установка скорости передачи
	UBRR0L = MYUBRR;
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      //контакты RX TX 
	UCSR0B |= (1 << RXCIE0);                    
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    

	sei();                                      

	while(1)
	{
		;                                     
	}
}

ISR (USART_RX_vect)             // Изначально это была функция эхо- принимала данные с блютуз и обратно отправляла
{
	//t=UDR0;
	//PORTB = t;
	ReceivedChar = UDR0;                       //Данные пришедшие с блютуз
	PORTB = ReceivedChar;                       // отправляем данные на порт В микроконтроллера
	
	/* в общем затык гдето в этой функции, прописывал if(), не помогло*/
}
