#define _CRT_SECURE_NO_WARNINGS
#include <DAQlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

void program();
void writeDigit(int digit, int position);
int findQuotient(int dividendValue, int divisorValue);
int findRemainder(int dividendValue, int divisorValue);


int main(){
	if (setupDAQ(4) == TRUE) {
		while (continueSuperLoop() == TRUE) {
				program();
				if (digitalRead(0) == TRUE) {
					for (int j = 0; j < 8; j++) {
						writeDigit(0, j);
					}
					if (digitalRead(0) == FALSE) {
						program();
					}
				}
			}	
		}

	else {
		printf("ERROR: Cannot initialize DAQ\n");
	}
	
	system("PAUSE");
	return 0;
}

void program() {
	int dividend, divisor, quotient, remainder;
	int thousands, hundreds, tens, ones;
	int dividendPosition = 4;
	int divisorPosition = 0;
	int quotientPosition = 4;
	int remainderPosition = 0;
	int count = 0;
	
	printf("Enter the value of the dividend:\n");
	scanf("%i", &dividend);
	thousands = dividend / 1000;
	hundreds = (dividend - (thousands * 1000)) / 100;
	tens = (dividend - (thousands * 1000) - (hundreds * 100)) / 10;
	ones = (dividend - (thousands * 1000) - (hundreds * 100)) - (tens * 10);

	int dividendNumber[4] = { thousands, hundreds, tens, ones };

	for (int i = 3; i > -1; i--) {
		writeDigit(dividendNumber[i], dividendPosition);
		dividendPosition++;
	}

	printf("Enter the value of the divisor:\n");
	scanf("%i", &divisor);
	thousands = divisor / 1000;
	hundreds = (divisor - (thousands * 1000)) / 100;
	tens = (divisor - (thousands * 1000) - (hundreds * 100)) / 10;
	ones = (divisor - (thousands * 1000) - (hundreds * 100)) - (tens * 10);

	int divisorNumber[4] = { thousands, hundreds, tens, ones };

	for (int i = 3; i > -1; i--) {
		writeDigit(divisorNumber[i], divisorPosition);
		divisorPosition++;
	}
	
	quotient = findQuotient(dividend, divisor);
	remainder = findRemainder(dividend, divisor);

	printf("The Quotient and the Remainder are: %d and %d\n", quotient, remainder);
	
	thousands = quotient / 1000;
	hundreds = (quotient - (thousands * 1000)) / 100;
	tens = (quotient - (thousands * 1000) - (hundreds * 100)) / 10;
	ones = (quotient - (thousands * 1000) - (hundreds * 100)) - (tens * 10);

	int quotientNumber[4] = { thousands, hundreds, tens, ones };

	for (int i = 3; i > -1; i--) {
		writeDigit(quotientNumber[i], quotientPosition);
		quotientPosition++;
	}

	thousands = remainder / 1000;
	hundreds = (remainder - (thousands * 1000)) / 100;
	tens = (remainder - (thousands * 1000) - (hundreds * 100)) / 10;
	ones = (remainder - (thousands * 1000) - (hundreds * 100)) - (tens * 10);

	int remainderNumber[4] = { thousands, hundreds, tens, ones };

	for (int i = 3; i > -1; i--) {
		writeDigit(remainderNumber[i], remainderPosition);
		remainderPosition++;
	}
}

void writeDigit(int digit, int position)
{
	static int digits[] =
	{ 252, 96, 218, 242, 102, 182, 190, 224, 254, 246 };

	displayWrite(digits[digit], position);
}

//12 divided by 3, 3 is divisor, 12 is dividend
int findQuotient(int dividendValue, int divisorValue) {
	int quotient;

	quotient = dividendValue / divisorValue;

	return quotient;
}

int findRemainder(int dividendValue, int divisorValue) {
	int remainder;

	remainder = dividendValue % divisorValue;

	return remainder;
}