#define MOTOR_OFFSET_LEFT 100  //본인꺼에 맞게 바꿀 값
#define MOTOR_OFFSET_RIGHT 100 //본인꺼에 맞게 바꿀 값

#define TARGET_LINE 0
#define kP 7  //본인꺼에 맞게 바꿀 값

#define SERIAL //시리얼 통신 안 쓰려면 주석처리하기

const int LED_pin[5] = {6, 5, 4, 3, 2};
const int sensor_pin[5] = {A0, A1, A2, A3, A4};

const int ENA = 9;   //모터 ENABLE A 핀
const int ENB = 10;  //모터 ENABLE B 핀
const int IN1 = 7;   //왼쪽 모터 방향 핀
const int IN2 = 8;
const int IN3 = 11;  //오른쪽 모터 방향 핀
const int IN4 = 12;

int sensor_value[5] = {0}; //센서 값 저장 변수
int sensor_standard[5] = {200, 200, 200, 200, 200}; //센서 기준값 설정 변수(캘리브레이션 사용 X경우)
int line_hex; //라인 위치 정보 저장 변수

void read_sensor(); //센서값 읽어서 "sensor_value"에 저장 후에 -> bit 형식으로 "line_hex"로 저
void monitoring_sensor(); //센서값 정보 -> UART출력 & LED출력 함수
void motor(int left_speed, int right_speed); //왼쪽/오른쪽 모터 속도 설정 함수
int curent_line(); //센서값 정보 -> 현재 라인 위치 판별 함수
void pControl(); //P제어 함수

void setup() {
#ifdef SERIAL
  Serial.begin(9600);
#endif
//아트메가의 모든 핀의 기본값은 입력이기 때문에 불필요 하지만 오류를 대비해 pinMode(SENSOR[i], INPUT) 입력
  for (int i = 0; i < 5; i++) {
    pinMode(sensor_pin[i], INPUT); //모든 센서는 INPUT으로 설정
    pinMode(LED_pin[i], OUTPUT); //모든 LED는 OUTPUT으로 설정
    digitalWrite(LED_pin[i], HIGH); //모든 LED의 초기값은 HIGH로 설정 -> sink 전류로 동작하기 때문
  }
  pinMode(ENA, OUTPUT); //모터 드라이버로 가는 핀들은 모두 OUTPUT
  pinMode(ENB, OUTPUT);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  read_sensor();//센서값을 읽고
  monitoring_sensor();//센서값을 UART & LED5개로 출력하고
  pControl();//그 센서값(라인 위치)에 따라 모터 속도 제어
}
/*********************************************************/
void read_sensor() {
  for (int i = 0; i < 5; i++) //센서값 읽어서 "sensor_value"에 저장
    sensor_value[i] = analogRead(sensor_pin[i]);

  line_hex = 0; //기준값보다 크면 검정색인 부분
  if( sensor_value[0] > sensor_standard[0] ) 
    line_hex += B10000; //왼쪽에서 0번 센서가 기준값보다 크면 이진수 0b 1 0000를 "line_hex"에 더해줌
  if( sensor_value[1] > sensor_standard[1] ) 
    line_hex += B01000; //왼쪽에서 1번 센서가 기준값보다 크면 이진수 0b 0 1000를 "line_hex"에 더해줌
  if( sensor_value[2] > sensor_standard[2] ) 
    line_hex += B00100; //왼쪽에서 2번 센서가 기준값보다 크면 이진수 0b 0 0100를 "line_hex"에 더해줌
  if( sensor_value[3] > sensor_standard[3] ) 
    line_hex += B00010; //왼쪽에서 3번 센서가 기준값보다 크면 이진수 0b 0 0010를 "line_hex"에 더해줌
  if( sensor_value[4] > sensor_standard[4] ) 
    line_hex += B00001; //왼쪽에서 4번 센서가 기준값보다 크면 이진수 0b 0 0001를 "line_hex"에 더해줌
}// ==> 결과적으로 라인 위치가 5비트로 표현됨

void monitoring_sensor() {
#ifdef SERIAL
  Serial.print(sensor_value[0]); Serial.print("\t"); //센서값 UART 출력
  Serial.print(sensor_value[1]); Serial.print("\t");
  Serial.print(sensor_value[2]); Serial.print("\t");
  Serial.print(sensor_value[3]); Serial.print("\t");
  Serial.print(sensor_value[4]); Serial.print("\t");
  
  if(line_hex <= B1111)Serial.print("0"); //"line_hex"를 출력할 때 높은 자리수가 0일 때 0을 채워주는 부분
  if(line_hex <= B111)Serial.print("0");
  if(line_hex <= B11)Serial.print("0");
  if(line_hex <= B1)Serial.print("0");
  Serial.print(line_hex, BIN);
#endif
  PORTD |= 0x7C; //LED전부 HIGH를 줘서 끄기
  PORTD &=~ line_hex<<2; //인식된 센서 그대로 LED 켜기
} // "<<2"는 PD2부터 LED니까 PD2자리부터 시작하도록 "line_hex"를 2칸 밀어줌

/*********************************************************/
void motor(int left_speed, int right_speed) { //왼쪽/오른쪽 모터 속도 설정 함수
  digitalWrite(IN1, HIGH); //모터 전진
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, left_speed); //모터 속도 변경
  analogWrite(ENB, right_speed);
}

int curent_line() { //센서 정보(line_hex) -> 현재 라인 위치 판별 함수
  switch(line_hex)
  { //"line_hex"의 1은 검정색을, 0은 흰색 배경을 나타냄 00100이면 라인이 라인트레이서 중앙에 있다는 것
    case B10000: return -4;
    case B11000: return -3;
    
    case B01000: return -2;
    case B01100: return -1; //음수는 라인트레이서 기준으로 라인이 왼쪽에 있다는 것, 숫자 크기는 중앙에서 얼마나 떨어졌는지 나타냄
    
    case B00100: return 0; //0을 중알으로 설정
    
    case B00110: return 1; //양수는 라인트레이서 기준으로 라인이 오른쪽에 있다는 것, 숫자 크기는 중앙에서 얼마나 떨어졌는지 나타냄
    case B00010: return 2;
    
    case B00011: return 3;
    case B00001: return 4;

    case B11110: return 100; //교차점 직진
    case B11111: return 100;
    case B01111: return 100;
  }
}

void pControl() { //P제어 함수
  int current_line = curent_line(); //바로 위에 있는 함수인 "curent_line()"에서 return한 값을 
  if (current_line == 100) current_line = 0;
  int error = current_line - TARGET_LINE; //얼마나 중앙에서 벗어났는지 "error" 값 계산
  int control_sensor = kP * error;
#ifdef SERIAL
  Serial.print("\t속도차이: "); //두 모터의 속도 차이 출력
  Serial.print(control_sensor);
  Serial.println(" * 2");
#endif
  motor((MOTOR_OFFSET_LEFT - control_sensor),  //왼쪽 모터 속도 조절
        (MOTOR_OFFSET_RIGHT + control_sensor));//오른쪽 모터 속도 조절
}
