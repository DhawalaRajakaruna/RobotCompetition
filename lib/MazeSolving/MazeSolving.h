#ifndef MAZESOLVING_H
#define MAZESOLVING_H

extern int error;
extern float Kd;
extern float Kp;
extern float Ki;
extern float error_sum ;
extern float error_dif;
extern float lastError;

void mazeSolve(int);
void movetoJunction();
void boxAtZero();
void noBoxAtZero(int n);
bool CheckWall();
void bringTheBoxToSqure(int);
void stopAtSqure();
void PIDfollow();
void movetoJunctionBackward();
void PIDfollowBackward();

#endif