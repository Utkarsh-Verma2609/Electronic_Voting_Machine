#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 10, 9, 8, 7, 6);

#define sw1 A0  // Button 1
#define sw2 A1  // Button 2
#define sw3 A2  // Button 3
#define sw4 A3  // Button 4
#define sw5 A4  // Button 5 for result
#define sw6 A5  // Button 6 for control
// #define startButton 12 // Button to start the EVM

int vote1 = 0;
int vote2 = 0;
int vote3 = 0;
int vote4 = 0;
int id;
int adminpin=80;
int currentState = 0;
bool votingActive = false;
int serialAuthPin = 1234;  // Predefined authentication PIN
int totalVoters = 500;  // Total number of voters
bool hasVoted[500] = {false};  // Track if each voter has voted
int currentVoterID = -1;

void setup() {
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  pinMode(sw4, INPUT);
  pinMode(sw5, INPUT);
  pinMode(sw6, INPUT);
  pinMode(13, OUTPUT);  // Blue LED
  pinMode(12, OUTPUT);  // Green LED

  digitalWrite(12,LOW);
  digitalWrite(13,LOW);

  // pinMode(startButton, INPUT_PULLUP); // Start button with internal pull-up resistor

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Electronic Voting");
  lcd.setCursor(0, 1);
  lcd.print("Machine (EVM)");

  delay(3000);

  Serial.begin(9600);

  digitalWrite(sw1, HIGH);
  digitalWrite(sw2, HIGH);
  digitalWrite(sw3, HIGH);
  digitalWrite(sw4, HIGH);
  digitalWrite(sw5, HIGH);
  digitalWrite(sw6, HIGH);

  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("BJP");
  // lcd.setCursor(4, 0);
  // lcd.print("INC");
  // lcd.setCursor(8, 0);
  // lcd.print("AAP");
  // lcd.setCursor(12, 0);
  // lcd.print("OTH");
}

int count = 0;

void loop() {
  count++;

  if (!votingActive) {
    // if (digitalRead(startButton) == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("EVM started.");
      lcd.setCursor(0, 1);
      lcd.print("Plz Enter ID");
      delay(1000);

      if (Serial.available() > 0) {
        String inputString = Serial.readStringUntil('\n');
         id = inputString.toInt();

        if (id >= 0 && id < totalVoters) {
          currentVoterID = id;

          if (!hasVoted[id]) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Authentication");
            lcd.setCursor(0, 1);
            lcd.print("Successful");
            delay(2000);
            lcd.clear();
            votingActive = true;
          } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Authentication");
            lcd.setCursor(0, 1);
            lcd.print("Failed (Already Voted)");
            delay(2000);
            lcd.clear();
          }
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Authentication");
          lcd.setCursor(0, 1);
          lcd.print("Failed (Invalid ID)");
          delay(2000);
          lcd.clear();
        }
      }
    // }
  } else {
    if (digitalRead(sw6) == 0) {
      if (!votingActive) {
        votingActive = true;
        currentState = 1;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Vote or Result");
        lcd.setCursor(0, 1);
        lcd.print("Press a button");
      }
    }

    if (votingActive) {
      lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Vote or Result");
        lcd.setCursor(0, 1);
        lcd.print("Press a button");
        delay(300);

    if(id!=80 and digitalRead(sw6) == 0 ){  
      if (digitalRead(sw1) == 0) {
        digitalWrite(12,HIGH);
        delay(500);
        digitalWrite(12,LOW);
        castVote(1);
        votingActive = false;
      } else if (digitalRead(sw2) == 0) {
        digitalWrite(12,HIGH);
        delay(500);
        digitalWrite(12,LOW);
        castVote(2);
        votingActive = false;
      } else if (digitalRead(sw3) == 0) {
        digitalWrite(12,HIGH);
        delay(500);
        digitalWrite(12,LOW);
        castVote(3);
        votingActive = false;
      } else if (digitalRead(sw4) == 0) {
        digitalWrite(12,HIGH);
        delay(500);
        digitalWrite(12,LOW);
        castVote(4);
        votingActive = false;
      }
    }
      if (digitalRead(sw5) == 0) {
        if(id==adminpin){
          digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
           showResults();
        votingActive = false;
        }else{
           lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Only Election");
      lcd.setCursor(0, 1);
      lcd.print("Officer allowed");
      delay(1000);
        }
        
      }
    
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Turn on the");
      lcd.setCursor(0, 1);
      lcd.print("EVM");
      delay(500);
    }
  }
}

void castVote(int candidate) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You voted for:");

  switch (candidate) {
    case 1:
      lcd.setCursor(0, 1);
      lcd.print("ABC");
      vote1++;
      break;
    case 2:
      lcd.setCursor(0, 1);
      lcd.print("DEF");
      vote2++;
      break;
    case 3:
      lcd.setCursor(0, 1);
      lcd.print("IJK");
      vote3++;
      break;
    case 4:
      lcd.setCursor(0, 1);
      lcd.print("XYZ");
      vote4++;
      break;
    
  }

  if(candidate!=5) hasVoted[currentVoterID] = true; // Mark the current voter as having voted
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thank you for");
  lcd.setCursor(0, 1);
  lcd.print("voting!");
  delay(2000);
  lcd.clear();
}

void showResults() {
  currentState = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Election Results:");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BJP:");
  lcd.print(vote1);

  lcd.setCursor(6, 0);
  lcd.print("INC:");
  lcd.print(vote2);

  lcd.setCursor(0, 1);
  lcd.print("AAP:");
  lcd.print(vote3);

  lcd.setCursor(6, 1);
  lcd.print("OTH:");
  lcd.print(vote4);

  delay(5000);
  lcd.clear();
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);

int vote=vote1+vote2+vote3+vote4;
if(vote)
{
if((vote1 > vote2 && vote1 > vote3 && vote1 > vote4))
{
lcd.clear();
lcd.print("ABC Wins");
delay(5000);
lcd.clear();
}
else if((vote2 > vote1 && vote2 > vote3 && vote2 > vote4))
{
lcd.clear();
lcd.print("DEF Wins");
delay(5000);
lcd.clear();
}
else if((vote3 > vote1 && vote3 > vote2 && vote3 > vote4))
{
lcd.clear();
lcd.print("IJK Wins");
delay(5000);
lcd.clear();
}
else if(vote4 > vote1 && vote4 > vote2 && vote4 > vote3)
{
lcd.setCursor(0,0);
lcd.clear();
lcd.print("XYZ Wins");
delay(5000);
lcd.clear();
}

else if(vote4 > vote1 && vote4 > vote2 && vote4 > vote3)
{
lcd.setCursor(0,0);
lcd.clear();
lcd.print("XYZ Wins");
delay(2000);
lcd.clear();
}

else
{
lcd.clear();
lcd.print(" Tie Up Or ");
lcd.setCursor(0,1);
lcd.print(" No Result ");
delay(5000);
lcd.clear();
}

}
else
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("  No Voting…         ");
delay(5000);
lcd.clear();
}
vote1=0;vote2=0;vote3=0;vote4=0,vote=0;
delay(3000);
lcd.clear();

}