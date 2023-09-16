# 2023_LineTracer

2023 RATS 신입생 라인트레이서 프로젝트

<div align=center>
    
![ezgif-5-28c73c5a9f](https://github.com/RATS-make-robot/2023_LineTracer/assets/68770209/e446edbc-0c1a-463e-938e-ef72ba596d17)
</div>

## 라인트레이서 대회
- 라인트레이서 완성 후 라인트레이서 대회에서 트랙 1바퀴 완주하면 준회원에서 정회원으로 승급됩니다.
    - 대회에서 여러 번 도전 가능
    - 최소 1회 완주 성공해야 정회원 승급 가능
- __정회원이 되어야 RATS에서 계속 활동할 수 있습니다.__

## 완성 모습

![20230301_155821](https://user-images.githubusercontent.com/68770209/226085467-d1575ad6-2522-4858-9c3e-a1780fda12e6.jpg)

## Schematic(회로도)
![2023_LineTracer_1](https://user-images.githubusercontent.com/68770209/226084867-f8758c74-1c60-4bd4-bbbc-3f401301a493.png)

## 2022년 대비 변경사항
- 차체

_모터 지지대 강화_
![230226](https://user-images.githubusercontent.com/68770209/226085409-d56b6ed5-345c-4c60-814d-5e5c09f153eb.png)

_배터리 위치 이동_
![20230302_105735](https://user-images.githubusercontent.com/68770209/226084952-f8f98ebe-845b-4b4d-a9c4-8cc974c7626a.jpg)

- 회로도

_잘못된 센서 방향 및 저항값 수정_
![2023_LineTracer_sensors](https://user-images.githubusercontent.com/68770209/226085589-e0334ce4-1ff3-4683-abfc-ae203f36912f.png)

## 부품리스트

[부품리스트 (가격과 판매처 링크가 포함된 버전)](https://mokhwasomssi.notion.site/bc81dec099644cce938beb7883b7c5f4)
- 소자
    |부품|종류|용도|
    |---|---|---|
    |아두이노 나노 호환보드|MCU|라트 개발보드|  
    |스위치|스위치|라트 전원 스위치|
    |7805|레귤레이터|전원부 레귤레이터|
    |캐패시터 0.33uF|커패시터|전원부 커패시터|
    |캐패시터 0.1uF|커패시터|전원부 커패시터|
    |저항 330Ω|저항|LED 저항|
    |저항 10kΩ|저항|수광 소자용 저항|
    |저항 220Ω|저항|발광 소자용 저항|
    |LED|LED|전원부 출력 확인, 센서 값 확인|
    |ST5811|발광 소자|주행선 감지|
    |SI5312-H|수광 소자|주행선 감지|

- 모터, 배터리
  |부품|종류|용도|
  |---|---|---|
  |아두이노 RC카 모터|모터|모터|
  |아두이노 RC카 바퀴|바퀴|바퀴|
  |배터리 18650 1200mAh|배터리|리튬 이온 배터리, 충전 가능|
  |배터리 홀더|배터리|18650x2 홀더|

- 소켓, 커넥터, 점퍼
  |부품|종류|용도|
  |---|---|---|
  |핀헤더|소켓|12핀 : 센서 전원, 신호  </br> 8핀 : 모터 전원, 신호|
  |핀헤더소켓|소켓|30핀 : 아두이노</br>3핀 : 레귤레이터|
  |몰렉스 커넥터 - M|커넥터|전원 커넥터|
  |몰렉스 커넥터 - F|커넥터|전원 커넥터|
  |소켓 점퍼 케이블 - F/F|점퍼|센서 전원 및 신호</br>모터드라이버 신호|
  |소켓 점퍼 케이블 - M/F|점퍼|모터드라이버 전원</br>모터 전선|

- 조립
  |부품|종류|용도|
  |----|---|---|
  |부품 수납 케이스|공구함|개인 부품 보관|
  |만능기판 100X100|만능기판|메인보드 납땜|
  |만능기판 100X50|만능기판|센서보드 납땜|
  |서포트 40mm|서포트|메인보드 서포트|
  |서포트 10mm|서포트|모터드라이버 서포트|
  |볼트 M3x10|볼트|메인보드 서포트 고정</br>모터드라이버 서포트 고정</br>볼캐스터 고정</br>센서보드 고정|
  |볼트 M3x16|볼트|몸체-몸체2 조립|
  |볼트 M3x30|볼트|모터 고정|
  |너트 M3|너트|너트|
  |볼캐스터 5/8|볼캐스터|앞바퀴|
