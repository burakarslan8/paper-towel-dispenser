#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/time.h>

#define TRIG 13
#define ECHO 15

void setupSensor();
long double calculateDistance();

int main(){
	setupSensor();
	
	while(1){
		long double distance = calculateDistance();
		printf("%Lf\n", distance);
	}
	return 0;
}

void setupSensor(){
	wiringPiSetupPhys();
	pinMode(TRIG,OUTPUT);
	pinMode(ECHO,INPUT);
}

long double calculateDistance(){
	digitalWrite(TRIG,LOW);
	printf("Olculuyor\n");
	delay(2000);
	digitalWrite(TRIG,HIGH);
	delay(1);
	digitalWrite(TRIG,LOW);
	
	struct timeval pulse_start;
	while(digitalRead(ECHO)==LOW){
		gettimeofday(&pulse_start,NULL);

	}
	printf("%lu\n",pulse_start);
	struct timeval pulse_end;
	while(digitalRead(ECHO)==HIGH){
		gettimeofday(&pulse_end,NULL);
		
	}
	printf("%lu\n",pulse_end);
	
	long double pulse_duration = (pulse_end.tv_sec-pulse_start.tv_sec) + pulse_end.tv_usec - pulse_start.tv_usec;
	
	long double distance = pulse_duration * 17150;
	distance /= 1000000;
	distance -= 0.5f;
	return distance;
}

