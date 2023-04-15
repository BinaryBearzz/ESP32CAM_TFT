#include <Arduino.h>
#include <Joystick.h>
onLeft _Event_L;
onRight _Event_R;
onUp _Event_U;
onDown _Event_D;
onSW _Event_SW;

onUpLeft _Event_UL;
onUpRight _Event_UR;
onDownLeft _Event_DL;
onDownRight _Event_DR;

Joystick::Joystick(int pinVRX, int pinVRY, int SW)
{
    if(pinVRX > 0)
        pinX = pinVRX;
    if(pinVRY > 0)
        pinY = pinVRY;
    pinSW = SW;
    _Event_L = NULL;
    _Event_R = NULL;
    _Event_U = NULL;
    _Event_D = NULL;
    _Event_SW = NULL;
    _Event_DL = NULL;
    _Event_DR = NULL;
    _Event_UL = NULL;
    _Event_UR = NULL;
} 

void Joystick::begin()
{   

    if(pinX > 0)
    {
        pinMode(pinX, INPUT);
        Serial.println("# Set pinX: "+String(pinX));
    }

    if(pinY > 0)
    {
        pinMode(pinY, INPUT);
        Serial.println("# Set pinY: "+String(pinY));
    }

    if(pinSW > 0)
    {
        pinMode(pinSW, INPUT_PULLUP);
        Serial.println("# Set pinSW: "+String(pinSW));
    }

}

int Joystick::est_horizontal()
{
    int a = 2;
    switch (position.x)
    {
        case -6 ... -4:
            a = 1; //Left
            break;
        case -2 ... 2:
            a = 2; //idle
            break;  
        case 4 ... 6:
            a = 3; //Right
            break;   
        default:
            a = 2;
            break;
    }
    return a;
}

int Joystick::est_vertical()
{
    int a = 2;
    switch (position.y)
    {
        case -6 ... -4:
            a = 1; //down
            break;
        case -2 ... 2:
            a = 2; //idle
            break;  
        case 4 ... 6:
            a = 3; //up
            break;   
        default:
            a = 2; 
            break;
    }
    return a;
}

void Joystick::mapping_Direction(int h, int v)
{
    int est_h = h;
    int est_v = v; 
    if(est_h == 1 && est_v == 2)
    {
        direction.dir = "Left";
        if(_Event_L != NULL && direction.last_dir != "Left")
        {
            _Event_L();
            direction.last_dir = direction.dir;
        }
    }
    else if (est_h == 2 && est_v == 2)
    {
        direction.dir = "center";
        if(direction.last_dir != "center")
        {
            direction.last_dir = direction.dir;
        }
    }
    else if (est_h == 3 && est_v == 2)
    {
        direction.dir = "Right";
        if(_Event_R != NULL && direction.last_dir != "Right")
        {
            _Event_R();
            direction.last_dir = direction.dir;
        }
    }
    else if(est_h == 2 && est_v == 3)
    {
        direction.dir = "Down";
        if(_Event_D != NULL && direction.last_dir != "Down")
        {
            _Event_D();
            direction.last_dir = direction.dir;
        }
    }
    else if(est_h == 2 && est_v == 1)
    {
        direction.dir = "Up";
        if(_Event_U != NULL && direction.last_dir != "Up")
        {
            _Event_U();
            direction.last_dir = direction.dir;
        }
    }
    else if(est_h == 1 && est_v == 3)
    {
        direction.dir = "DownLeft";
        if(_Event_DL != NULL && direction.last_dir != "DownLeft")
        {
            _Event_DL();
            direction.last_dir = direction.dir;
        }
    }
    else if(est_h == 3 && est_v == 3)
    {
        direction.dir = "DownRight";
        if(_Event_DR != NULL && direction.last_dir != "DownRight")
        {
            _Event_DR();
            direction.last_dir = direction.dir;
        }
    }
    else if(est_h == 1 && est_v == 1)
    {
        direction.dir = "UpLeft";
        if(_Event_UL != NULL && direction.last_dir != "UpLeft")
        {
            _Event_UL();
            direction.last_dir = direction.dir;
        }

    }
    else if(est_h == 3 && est_v == 1)
    {
        direction.dir = "UpRight";
        if(_Event_UR != NULL && direction.last_dir != "UpRight")
        {
            _Event_UR();
            direction.last_dir = direction.dir;
        }   
    }

}

void Joystick::onEvent_Left(onLeft funcEventLeft)
{
    _Event_L = funcEventLeft;
}
void Joystick::onEvent_Right(onRight funcEventRight)
{
    _Event_R = funcEventRight;
}
void Joystick::onEvent_Up(onUp funcEventUp)
{
    _Event_U = funcEventUp;
}
void Joystick::onEvent_Down(onDown funcEventDown)
{
    _Event_D = funcEventDown;
}

void Joystick::onEvent_SW(onSW funcEventSW)
{
    _Event_SW = funcEventSW;
}

void Joystick::onEvent_UpLeft(onUpLeft funcEventUpLeft)
{
    _Event_UL = funcEventUpLeft;
}
void Joystick::onEvent_UpRight(onUpRight funcEventUpRight)
{
    _Event_UR = funcEventUpRight;
}
void Joystick::onEvent_DownLeft(onDownLeft funcEventDownLeft)
{
    _Event_DL = funcEventDownLeft;
}
void Joystick::onEvent_DonwRight(onDownRight funcEventDownRight)
{
    _Event_DR = funcEventDownRight;
}

void Joystick::onEvent(onLeft funcEventLeft, onRight funcEventRight, onUp funcEventUp, onDown funcEventDown, onSW funcEventSW)
{
    if(funcEventLeft != NULL)
        _Event_L = funcEventLeft;
    if(funcEventRight != NULL)
        _Event_R = funcEventRight;
    if(funcEventUp!= NULL)
        _Event_U = funcEventUp;
    if(funcEventDown != NULL)
        _Event_D = funcEventDown;
    if(funcEventSW != NULL)
        _Event_SW = funcEventSW;
}
void Joystick::handle()
{
    if(pinX > 0)
       { int aPinX = analogRead(pinX); position.x = map((aPinX), 0, 4096, -6, 6);}
    if(pinY > 0)
        {int aPinY = analogRead(pinY); position.y = map((aPinY), 0, 4096, -6, 6);}
    // Serial.println("pinX: "+String(aPinX));
    // Serial.println("pinY: "+String(aPinY));
    // Serial.println("(x, y): "+String(position.x)+":"+String(position.y));
    int est_h = est_horizontal();
    int est_v = est_vertical(); 

    mapping_Direction(est_h, est_v);
    if(pinSW > 0)
    {
        currentStateSW = digitalRead(pinSW);
        if (lastStateSW == HIGH && currentStateSW == LOW)
        {
            if(_Event_SW != NULL)
            {
                _Event_SW(true);
            }
        }
        // Serial.println("The button is pressed");
        else if (lastStateSW == LOW && currentStateSW == HIGH)
        {
            if(_Event_SW != NULL)
            {
                _Event_SW(false);
            }
        }
        // Serial.println("The button is released");
        lastStateSW = currentStateSW;
    }
    // if(est_h == 1)
    // {
    //     if(_Event_L != NULL)
    //         _Event_L();
    // }
    // else if(est_h == 3)
    // {
    //     if(_Event_R != NULL)
    //         _Event_R();
    // }

    // if(est_v == 1)
    // {
    //     if(_Event_D != NULL)
    //         _Event_D();
    // }
    // else if(est_v == 3)
    // {
    //     if(_Event_U != NULL)
    //         _Event_U();
    // }
    // if(sw_ == 1)
    // {
    //     if(_Event_SW != NULL)
    //         _Event_SW();        
    // }

}


