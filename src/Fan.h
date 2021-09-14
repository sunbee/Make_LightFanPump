#ifndef FAN_H
#define FAN_H

class FAN
{
    public:
        void switch(bool=false);
        void instruct();
    private:
        int PIN_SWITCH;
        int PIN_DATA;
}
#endif