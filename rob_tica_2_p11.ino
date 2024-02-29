#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

char operacao[] = {'+', '-', '*', '/'};
float num1, num2, resposta, valorErrado, seed = 0;
char op;
bool muda_op = true;
String pergunta, respA, respB;

void setup() {
  lcd.begin(16, 2);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}

void loop() {
  randomSeed(seed);
  seed++;
  lcd.clear();
  
  op = operacao[random(4)];
  
  num1 = random(1,10);
  num2 = random(1,10);
  
  switch(op) {
    case '+': resposta = num1 + num2;
              break;
    case '-': resposta = num1 - num2;
              break;
    case '*': resposta = num1 * num2;
              break;
    case '/': resposta = num1 / num2;
              break;
  }
  
  if(resposta < 0) {valorErrado = -(random(1,10)); if(valorErrado == resposta){seed++; valorErrado = -(random(1,10));}} 
  else if(resposta <= 10) {valorErrado = random(1,10); if(valorErrado == resposta){seed++; valorErrado = (random(1,10));}}
  else if(resposta > 10 && resposta <= 100) {valorErrado = random(10,100); if(valorErrado == resposta){seed++; valorErrado = (random(10,100));}}
  else if(resposta > 100) {valorErrado = random(100,1000); if(valorErrado == resposta){seed++; valorErrado = (random(100,1000));}}
      
  pergunta = String(num1) +" "+ op +" "+ String(num2) +" =";
  lcd.setCursor(0, 0);
  lcd.print(pergunta);
  
  if(muda_op) {
    respA = "A) "+ String(resposta);
    lcd.setCursor(1,1);
    lcd.print(respA);

    respB = "B) "+ String(valorErrado+2);
    lcd.setCursor(9, 1);
    lcd.print(respB);
  }
  else {
    respA = "A) "+ String(valorErrado+2);
    lcd.setCursor(1,1);
    lcd.print(respA);

    respB = "B) "+ String(resposta);
    lcd.setCursor(9, 1);
    lcd.print(respB);
  }
  
  while (true) {
    if (digitalRead(7) == HIGH && muda_op == true) { // Botão A pressionado
      lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("VOCE ACERTOU!");
      delay(2000);
      muda_op = !muda_op;
      break;
    }
    if (digitalRead(6) == HIGH && muda_op == false) { // Botão B pressionado
      lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("VOCE ACERTOU!");
      delay(2000);
      muda_op = !muda_op;
      break;
    }
    if ((digitalRead(6) == HIGH && muda_op == true) || (digitalRead(7) == HIGH && muda_op == false)){ 
      lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("VOCE ERROU!");
      delay(2000);
      muda_op = !muda_op;
      break;
    }
  }
}
