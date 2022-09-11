#include "../include/kstdio.h"
/**
* first argument define the type of string to kprintf and kscanf, 
* %c for charater
* %s for string, 
* %d for integer
* %x hexadecimal
* %f for floating point number
*/
void showError(uint8_t e[]){

	_USART_WRITE(USART2, (uint8_t *)e);
}

void reverse(uint32_t st , uint32_t ed , uint8_t s[]){

	for(uint32_t i = st , j = 1 ; i < (ed+st)/2 ; i++ , j++){

		uint8_t ch = s[i];
		s[i] = s[ed-j];
		s[ed-j] = ch;
	}
}

void convertIntToString(uint32_t n , uint8_t s[]){

	uint32_t len = 0 , t = n;

	if(n == 0) s[len++] = '0';

	while(n){

		s[len++] = (n % 10) + '0';
		n /= 10;
	}

	if(t < 0) s[len++] = '-';

	s[len] = 0;
	reverse(0 , len , s);	
}

void convertIntToHexString(uint32_t n , uint8_t s[]){

	uint32_t len = 0;

	while(n){

		uint32_t rem = n % 16;

		if(rem <= 9) s[len++] = rem + '0';
		else s[len++] = (rem - 10) + 'A';

		n /= 16;
	}

	while(len < 8){s[len++] = '0';}

	s[len++] = 'x';
	s[len++] = '0';
	s[len] = 0;

	reverse(0 , len , s);
}

void convertFloatToString(float f , uint8_t s[]){

	if(f == 0){
		s[0] = '0';
		s[1] = 0;
		return;
	}

	uint32_t whole = 0 , isNeg = 0;
	if(f < 0) {f *= -1; isNeg = 1;} //making it positive
	whole = (uint32_t) f;
	uint32_t i = 0;

	if(!whole) s[i++] = '0';
	while(whole){

		s[i++] = (whole % 10) + '0';
		whole /= 10;
	}

	if(isNeg) s[i++] = '-'; //putting the negative sign
	reverse(0 , i , s);
	s[i++] = '.';

	//handling the float part
	uint32_t it = 4;
	while(it--){

		f *= 10.0;
		whole = (uint32_t) f;
		s[i++] = (whole % 10) + '0';
	}

	s[i] = 0;
}

void convertStringToInt(uint32_t *var , uint8_t s[]){

	uint32_t num = 0;

	for(uint32_t i = 0 ; s[i] ; i++){

		num *= 10;
		num += (uint32_t)(s[i] - '0');
	}

	*var = num;
}

void convertHexStringToInt(uint32_t *var , uint8_t s[]){

	uint32_t num = 0;

	for(uint32_t i = 2 ; s[i] ; i++){

		num *= 16;

		if(s[i] >= '0' && s[i] <= '9') num += (s[i] - '0');
		else if(s[i] >= 'A' && s[i] <= 'F') num += (10 + s[i] - 'A');
		else num += (10 + s[i] - 'a');
	}

	*var = num;
}

void convertStringToFloat(float *var , uint8_t s[]){

	float num = 0.000000 , sign = 1.0;
	uint32_t whole = 0 , i = 0 ;
	if(s[0] == '-') {sign = -1.0; i++;}

	while(s[i] != '.' && s[i]){

		whole *= 10;
		whole += (s[i] - '0');
		i++;
	}

	//if no (.) in the string
	if(!s[i]){
		num = (float) whole;
		*var = num * sign;
		return;
	}

	//ignoring the (.)
	i++;
	float j = 1.0;

	//appending the fractional part
	while(s[i]){

		j *= 10;
		num += (s[i] - '0') / j;
		i++;
	}

	num += (float)whole; //appending the whole part

	*var = num * sign;
}


void kprintf(uint8_t *format,uint8_t* outvar)
{
	uint32_t *tmp = (uint32_t*) outvar;
	uint32_t n = *tmp; 

	if(format[1] == 'c'){

		_USART_WRITE(USART2, (uint8_t *)outvar);
	}

	else if(format[1] == 's'){

		_USART_WRITE(USART2, (uint8_t *)outvar);
	}

	else if(format[1] == 'd'){

		uint8_t num[13];
		convertIntToString(n , num);
		
		_USART_WRITE(USART2, (uint8_t *)num);
	}

	else if(format[1] == 'x'){

		uint8_t hex[12];
		convertIntToHexString(n , hex);

		_USART_WRITE(USART2, (uint8_t *)hex);
	}

	else if(format[1] == 'f'){

		uint8_t flt[15];
		float *f = (float *) outvar;
		convertFloatToString(*f , flt);

		_USART_WRITE(USART2, (uint8_t *)flt);
	}

	else showError((uint8_t *)"Invalid format specifier\n");
}


void kscanf(uint8_t *format,uint8_t* invar)
{

	if(format[0] != '%') {showError((uint8_t *)"Invalid format specifier\n");return;}

	if(format[1] == 'c') {
        _USART_READ(USART2, invar, 2);

    } 

    else if(format[1] == 's') {
        _USART_READ(USART2, invar, 1000);

    } 

    else if(format[1] == 'd') {

        uint8_t input[13];

        _USART_READ(USART2, input, 1000);

        uint32_t* x = (uint32_t*) invar;
        convertStringToInt(x , input);

    } 

    else if(format[1] == 'x') {

        uint8_t input[13];

        _USART_READ(USART2, input, 1000);

        uint32_t* x = (uint32_t*) invar;
        convertHexStringToInt(x , input);

    } 

    else if(format[1] == 'f') {

        uint8_t input[13];

        _USART_READ(USART2, input, 1000);

        float* x = (float*) invar;
        convertStringToFloat(x , input);

    }
	
	else showError((uint8_t *)"Invalid format\n");
}





