const int red = 7;
const int green = 8;
const int yellow = 10;
const int btnred = 2;
const int btngreen = 3;
const int btnyellow = 5;
const int blinktime = 500;
const int outputs[] = {red, green, yellow};
const int inputs[] = {btnred, btngreen, btnyellow};
short sizeorder = 0;
short comparepos;
short compareinput;
short order[100] = {};

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(outputs[i], OUTPUT);
    pinMode(inputs[i], INPUT);
  }
  randomSeed(analogRead(A3));
  blinkall(3);
}

void loop() {
  make();
  show();
  if(!verify()){
    sizeorder = 0;
    blinkall(3);
  } else {
    blinkall(1);
  }
}

void make() {
  order[sizeorder] = random(3);
  sizeorder++;
}

void show() {
  for (int i = 0; i < sizeorder; i++) {
    digitalWrite(outputs[order[i]], HIGH);
    delay(blinktime);
    digitalWrite(outputs[order[i]], LOW);
    delay(blinktime);
  }
  delay(500);
}

bool verify(){
  bool touched = false;
  int btntouched;
  for (int i = 0; i < sizeorder; i++) {
    while(!touched){
      for (int b = 0; b < 3; b++) {
        if(digitalRead(inputs[b])){
          digitalWrite(outputs[b], HIGH);
          delay(blinktime);
          digitalWrite(outputs[b], LOW);
          delay(blinktime);
          touched = true;
          btntouched = b;
        }
      }
      delay(10);
    }
    if(order[i]!=btntouched) return false;
    touched = false;
  }
  delay(500);
  return true;
}

void blinkall(int times) {
  for (int t = 0; t < times; t++) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(outputs[i], HIGH);
    }
    delay(100);
    for (int i = 0; i < 3; i++) {
      digitalWrite(outputs[i], LOW);
    }
    delay(100);
  }
  delay(blinktime);
}
