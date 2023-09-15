#define MOTOR_OFFSET_LEFT 100  //본인꺼에 맞게 바꿀 값
#define MOTOR_OFFSET_RIGHT 100 //본인꺼에 맞게 바꿀 값

#define TARGET_LINE 0
#define kP 7  //본인꺼에 맞게 바꿀 값

#define SERIAL //시리얼 안 쓰려면 주석처리하기

const int LED_pin[5] = {6, 5, 4, 3, 2};
const int sensor_pin[5] = {A0, A1, A2, A3, A4};

const int ENA = 9;
const int ENB = 10;
const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 11;
const int IN4 = 12;

int sensor_value[5] = {0};
int sensor_standard[5] = {200, 200, 200, 200, 200};
int line_hex;

void read_sensor();
void monitoring_sensor();
void motor(int left_speed, int right_speed);
int curent_line();
void pControl();

void setup() {
#ifdef SERIAL
  Serial.begin(9600);
#endif
    //아트메가의 모든 핀의 기본값은 입력이기 때문에 불필요 하지만 오류를 대비해 pinMode(SENSOR[i], INPUT) 입력
  for (int i = 0; i < 5; i++) {
    pinMode(sensor_pin[i], INPUT);
    pinMode(LED_pin[i], OUTPUT);
    digitalWrite(LED_pin[i], HIGH);
  }
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  read_sensor();
  monitoring_sensor();
  pControl();
}
/*********************************************************/
void read_sensor() {
  for (int i = 0; i < 5; i++)
    sensor_value[i] = analogRead(sensor_pin[i]);

  line_hex = 0;
  if( sensor_value[0] > sensor_standard[0] ) 
    line_hex += B10000;
  if( sensor_value[1] > sensor_standard[1] ) 
    line_hex += B01000;
  if( sensor_value[2] > sensor_standard[2] ) 
    line_hex += B00100;
  if( sensor_value[3] > sensor_standard[3] ) 
    line_hex += B00010;
  if( sensor_value[4] > sensor_standard[4] ) 
    line_hex += B00001;
}

void monitoring_sensor() {
#ifdef SERIAL
  Serial.print(sensor_value[0]); Serial.print("\t");
  Serial.print(sensor_value[1]); Serial.print("\t");
  Serial.print(sensor_value[2]); Serial.print("\t");
  Serial.print(sensor_value[3]); Serial.print("\t");
  Serial.print(sensor_value[4]); Serial.print("\t");
  
  if(line_hex <= B1111)Serial.print("0");
  if(line_hex <= B111)Serial.print("0");
  if(line_hex <= B11)Serial.print("0");
  if(line_hex <= B1)Serial.print("0");
  Serial.print(line_hex, BIN);
#endif
  PORTD |= 0x7C; //LED전부 끄기
  PORTD &=~ line_hex<<2;//인식된 센서 그대로 LED 켜기
}

/*********************************************************/
void motor(int left_speed, int right_speed) {
  digitalWrite(IN1, HIGH);//모터 전진
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, left_speed);//모터 속도 변경
  analogWrite(ENB, right_speed);
}

int curent_line()
{
  switch(line_hex)
  {
    case B10000: return -4;
    case B11000: return -3;
    
    case B01000: return -2;
    case B01100: return -1;
    
    case B00100: return 0;
    
    case B00110: return 1;
    case B00010: return 2;
    
    case B00011: return 3;
    case B00001: return 4;

    case B11110: return 100; //교차점 직진
    case B11111: return 100;
    case B01111: return 100;
  }
}

void pControl() {
  int current_line = curent_line();
  if (current_line == 100) current_line = 0;
  int error = current_line - TARGET_LINE;
  int control_sensor = kP * error;
#ifdef SERIAL
  Serial.print("\t속도차이: ");
  Serial.print(control_sensor);
  Serial.println(" * 2");
#endif
  motor((MOTOR_OFFSET_LEFT - control_sensor),
        (MOTOR_OFFSET_RIGHT + control_sensor));
}
