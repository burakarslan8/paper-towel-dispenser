#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>

#define DELAY_TIME 2

#define M1A 16
#define M1B 18
#define M1E 22

void setup_motor(), motor_ileri(), motor_geri(), motor_stop();

#define TRIG 13
#define ECHO 15

#define LED 11
#define SETUP_LED() do { pinMode(LED, OUTPUT); } while(0);

void setupSensor();
long double calculateDistance();

void led(int s) {
    if (s > 0)
        digitalWrite(LED, HIGH);
    else
        digitalWrite(LED, LOW);
}

int main() {
    wiringPiSetupPhys();
    setup_motor(); setupSensor();
    SETUP_LED();
	
	while(1){
		long double distance = calculateDistance();
		printf("[SENSOR] distance: %Lfm\n", distance);
        if (distance < 10 && distance > 0) {
            led(1);
            motor_ileri();
            delay(2000);
            motor_stop();
        }
        led(0);
	}

    return 0;
}

void setup_motor() {
    pinMode(M1A, OUTPUT);
    pinMode(M1B, OUTPUT);
    pinMode(M1E, OUTPUT);
}

void motor_ileri() {
    printf("[MOTOR] FORWARD \n");

    /*
        a => h
        b => l
        e => h
    */

    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M1E, HIGH);
}

void motor_geri() {
    printf("[MOTOR] BACKWARD \n");

    /*
        a => l
        b => h
        e => h
    */

    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
    digitalWrite(M1E, HIGH);
}

void motor_stop() {
    printf("[MOTOR] STOP\n");

    // e => l

    digitalWrite(M1E, LOW);
}

void setupSensor(){
	pinMode(TRIG,OUTPUT);
	pinMode(ECHO,INPUT);
}

long double calculateDistance(){
	digitalWrite(TRIG,LOW);
	printf("[SENSOR] Calculating...\n");
	delay(DELAY_TIME * 1000);
	digitalWrite(TRIG,HIGH);
	delay(1);
	digitalWrite(TRIG,LOW);
	
	struct timeval pulse_start;
	while(digitalRead(ECHO)==LOW){
		gettimeofday(&pulse_start,NULL);

	}
	//printf("%lu\n",pulse_start);
	struct timeval pulse_end;
	while(digitalRead(ECHO)==HIGH){
		gettimeofday(&pulse_end,NULL);
		
	}
	//printf("%lu\n",pulse_end);
	
	long double pulse_duration = (pulse_end.tv_sec-pulse_start.tv_sec) + pulse_end.tv_usec - pulse_start.tv_usec;
	
	long double distance = pulse_duration * 17150;
	distance /= 1000000;
	distance -= 0.5f;
	return distance;
}
