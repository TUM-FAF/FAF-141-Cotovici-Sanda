#include "object.h"
#include <cmath>
#include <iostream>


objects::objects(POINT center, const int &speed)
 {

    this -> center = center;
    this -> xSpeed = speed;
    this -> ySpeed = speed;
    clr = RGB(0,0,0);

}

bool objects::Accelerate(const int& dX, const int& dY)
{
    xSpeed = dX;
    ySpeed = dY;
    return TRUE;
}

bool objects::Color(const COLORREF &clr)
{
    this -> clr = clr;
    return TRUE;
}
bool objects::Shape(objects &ob)
{

    return TRUE;
}

bool Circle::Move(const HDC &hdc, const RECT& rect, HBRUSH &hBrush)
{
    hBrush = CreateSolidBrush(clr);
    SelectObject(hdc, hBrush);

    Collision(rect);

    center.x += xSpeed; center.y -= ySpeed;

    if(counter>0)
    {
        Rectangle(hdc, center.x-20, center.y-20, center.x+20, center.y+20 );
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        DeleteObject(hBrush);
        return TRUE;
    }

    Ellipse(hdc, center.x-20, center.y-20, center.x+20, center.y+20 );
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    DeleteObject(hBrush);
    return TRUE;

}

bool objects::Collision(const RECT &rect)
{
    if(center.x+20 > rect.right-1)
    {
        xSpeed =- abs(xSpeed);
        counter=1;
    }
    if(center.x-20 < rect.left+1)
    {
        xSpeed = abs(xSpeed);
        counter=1;
    }
    if(center.y+20 > rect.bottom-1)
    {
        ySpeed = abs(ySpeed);
    }
    if(center.y-20 < rect.top+1)
    {
        ySpeed = -abs(ySpeed);
    }
    return TRUE;
}

bool Interaction(objects &obj1, objects &obj2) {

    float dist;
    POINT totalSpeed;

    dist = sqrt( pow(obj1.center.x-obj2.center.x,2) + pow(obj1.center.y-obj2.center.y,2) );

    if ( dist < 42 && dist > 30) {
	obj1.Color(RGB((BYTE)(rand() % 255), (BYTE)(rand() % 255), (BYTE)(rand() % 255)));
	obj2.Color(RGB(240,128,128));
    totalSpeed.x = (abs(obj1.xSpeed) + abs(obj2.xSpeed))/2;
    totalSpeed.y = (abs(obj1.ySpeed) + abs(obj2.ySpeed))/2;
	obj1.Accelerate(-obj1.xSpeed+1,-obj1.ySpeed-1);
    obj2.Accelerate(-obj2.xSpeed-1,-obj2.ySpeed+1);
    }

    return TRUE;
}

