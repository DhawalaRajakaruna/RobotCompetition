#include <BoxArranging.h>
#include <LineSensor.h>
#include <motorControl.h>

int boxCount = 0;
int junctionCount = 0;
void boxOrdering(int colorNum)
{
    //***************** initially need to change the thresholds*********************
    //Blue = 1
    //Red = 0

    movetoJunction(); //Initially go towards the first junction
    junctionCount = junctionCount + 1;
    switch (colorNum)
    {
    case 0://Red decending

        //First box-----------------------------------------------
        gotoFirstBox();
        redDecending();

        //Second box-----------------------------------------------
        gotoSecondBox();
        redDecending();

        //third box-------------------------------------------------
        gotoThirdBox();
        redDecending();
        break;

//////////////////////////////////////////////////////////////////////////////

    case 1://Blue assending

        //First box-----------------------------------------------
        gotoFirstBox();
        blueAsending();

        //Second box-----------------------------------------------
        gotoSecondBox();
        blueAsending();

        //third box-------------------------------------------------
        gotoThirdBox();
        blueAsending();
        break;

    default:
        Serial.println("Error In color detection");
        break;
    }
}

void redDecending(){
    int boxheight = measureHeight();
    //*********** Need to pick Up the Box*****************************
    switch (boxheight)
        {
        case 15:
            carryBoxTo(1);
            break;
        case 10:
            carryBoxTo(2);
            break;
        case 5:
            carryBoxTo(3);
            break;
        default:
            break;
        }
}

void blueAsending(){
    int boxheight = measureHeight();
    //*********** Need to pick Up the Box*****************************
    switch (boxheight)
        {
        case 5:
            carryBoxTo(1);
            break;
        case 10:
            carryBoxTo(2);
            break;
        case 15:
            carryBoxTo(3);
            break;
        default:
            break;
        }
}

void gotoFirstBox(){
    if (junctionCount == 1){
        turnLeft(85,60);
        moveForward(baseSpeed);
        delay(1000);// have to decide the delay according to the distance
        stopMotors();
    }
}
void gotoSecondBox(){
    if (junctionCount == 1){
        turnRight(85,60);
        movetoJunction();
        junctionCount++;
        turnLeft(85,65);
        moveForward(baseSpeed);
        delay(1000); // have to decide the delay according to the distance
        stopMotors();
    }
    if (junctionCount == 2){
        moveForward(baseSpeed);
        delay(1000);// have to decide the delay according to the distance
        stopMotors();
    }
    if (junctionCount == 3){
        turnLeft(85,60);
        movetoJunction();
        junctionCount--;
        turnRight(85,60);
        moveForward(baseSpeed);
        delay(1000);// have to decide the delay according to the distance
        stopMotors();
    }
}
void gotoThirdBox(){
    if (junctionCount == 1){
        turnRight(85,60);
        movetoJunction();
        junctionCount++;
        movetoJunction();
        junctionCount++;
        turnLeft(85,65);
        moveForward(baseSpeed);
        delay(1000); // have to decide the delay according to the distance
        stopMotors();
    }
    if (junctionCount == 2){
        turnRight(85,60);
        movetoJunction();
        junctionCount++;
        turnLeft(85,65);
        moveForward(baseSpeed);
        delay(1000);// have to decide the delay according to the distance
        stopMotors();
    }
    if (junctionCount == 3){
        moveForward(baseSpeed);
        delay(1000);// have to decide the delay according to the distance
        stopMotors();
    }
}
void carryBoxTo(int junctiontoTurn){
    turnBack(baseSpeed);
    movetoJunction();
    if (junctionCount < junctiontoTurn)
    {
        turnLeft(85, 60);
        movetoJunction();
        junctionCount++;
        nextMoveUp(junctiontoTurn);//
    }
    else if (junctionCount > junctiontoTurn)
    {
        turnRight(85,60);
        movetoJunction();
        junctionCount--;
        nextMoveDown(junctiontoTurn);//
    }
    else if (junctionCount == junctiontoTurn)
    {
        moveForward(baseSpeed);//till the place where to place the box
        //********** Move forward and place the boxes *************
        turnBack(baseSpeed);
        movetoJunction();
        brake();
        }
}
void nextMoveUp(int junctiontoTurn){
    if(junctionCount < junctiontoTurn){
        movetoJunction();
        junctionCount++;
    }
    turnRight(85, 60);
    //********** Move forward and place the boxes *************
    turnBack(baseSpeed);
    movetoJunction();
    brake();

}
void nextMoveDown(int junctiontoTurn){
    if(junctionCount > junctiontoTurn){
        movetoJunction();
        junctionCount--;
    }
    turnLeft(85,60);
    //********** Move forward and place the boxes *************
    turnBack(baseSpeed);
    movetoJunction();
    brake();
    

}
void movetoJunction(){
    //This function is to move the robo forward until it meets a junction
    while(true/* ! All IR sensor values should be white */){
        moveForward(baseSpeed);
    }
    brake();
}
int measureHeight(){
    //----------
    int height = 10;
    return height;
}

