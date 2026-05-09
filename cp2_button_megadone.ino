// 定义 9 个输入引脚 (增加了 48)
const int inputPins[] = {22, 24, 26, 28, 30, 32, 50, 52, 48};
// 对应 p5.js 的指令：增加了 "R" (Reset)
const char* cmds[] = {"1", "2", "3", "4", "5", "6", "C", "L", "R"};
const int ledPin = 13; 

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  // 初始化 9 个引脚为上拉输入
  for (int i = 0; i < 9; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }
}

void loop() {
  // 遍历 9 个引脚
  for (int i = 0; i < 9; i++) {
    if (digitalRead(inputPins[i]) == LOW) {
      digitalWrite(ledPin, HIGH); // 点亮板载 LED 提示触发
      Serial.println(cmds[i]);    // 发送对应字符到 p5.js
      
      // 阻塞直到引脚释放，防止重复触发
      while(digitalRead(inputPins[i]) == LOW) {
        delay(5); 
      }
      
      digitalWrite(ledPin, LOW);  
      delay(150);                 // 稍微增加防抖时间，确保串口输出稳定
      break; 
    }
  }
}