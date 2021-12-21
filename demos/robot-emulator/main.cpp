#include "mbed.h"
#include "stm32f413h_discovery_lcd.h"

typedef void (*func_t)(void);

// motor control pins
PwmOut in1(p21);
PwmOut in2(p22);
PwmOut in3(p23);
PwmOut in4(p24);
// end motor contron pins

// simulation variables, do not modify
int tail_x=BSP_LCD_GetXSize()/2;
int tail_y=BSP_LCD_GetYSize()/2;
int head_x=BSP_LCD_GetXSize()/2;
int head_y=BSP_LCD_GetYSize()/2;
float dir = 0;
Ticker lcd_ticker;
// end simulation variables

// ultrasonic sensor emulator class, do not modify
class Ultrasonic
{
    protected:
        AnalogIn* ain;
        Timeout* delayer;
        func_t echo_isr;
    public:
        static const int SPEED_OF_SOUND = 3350;
        Ultrasonic(PinName pin, func_t echo_cb)
        {
            this->ain = new AnalogIn(pin);
            this->delayer = new Timeout();
            this->echo_isr = echo_cb;
        }
        ~Ultrasonic()
        {
            delete ain;
            delete delayer;
        }
        void trigger()
        {
            if(this->echo_isr != NULL)
            {
                const float delay = (20.0+this->ain->read()*400.0)/SPEED_OF_SOUND;
                printf("Emulating %.0fus delay\n", delay*1e6);
                this->delayer->attach_us(this->echo_isr, delay*1e6);
            }
        }
};

// lcd drawing task that emulates the robot, do not modify
void lcd_draw_task()
{
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    if(in1 >= 0.1 && in3 >= 0.1)
    {
        BSP_LCD_FillCircle(tail_x, tail_y, 3);
        tail_x = head_x;
        tail_y = head_y;
        head_x += round(sin(dir)*in1*4);
        head_y += round(cos(dir)*in3*4);
    }
    else if(in2 >= 0.1 && in4 >= 0.1)
    {
        BSP_LCD_FillCircle(head_x, head_y, 3);
        head_x = tail_x;
        head_y = tail_y;
        tail_x -= round(sin(dir)*in2*4);
        tail_y -= round(cos(dir)*in4*4);
    }
    else if(in1 >= 0.1 && in4 >= 0.1)
    {
        dir += 0.1;
        BSP_LCD_FillCircle(head_x, head_y, 3);
        head_x = tail_x + round(sin(dir)*in1*10);
        head_y = tail_y + round(cos(dir)*in4*10);
    }
    else if(in2 >= 0.1 && in3 >= 0.1)
    {
        dir -= 0.1;
        BSP_LCD_FillCircle(head_x, head_y, 3);
        head_x = tail_x + round(sin(dir)*in2*10);
        head_y = tail_y + round(cos(dir)*in3*10);
    }
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_FillCircle(tail_x, tail_y, 3);
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    BSP_LCD_FillCircle(head_x, head_y, 3);
}


// splitted wait function which allows for lcd drawing simulation and ultrasonic sensor emulation to work
// do not use bare wait_ms and instead use this function wherever you may need wait.
// Hint: you should only need this function in your main loop to avoid browser crash. 
// You should not need any busy waits like this!!
void splitted_wait_ms(int delay_ms)
{
    static Timer internalTimer;
    internalTimer.start();
    internalTimer.reset();
    while(internalTimer.read_ms()<delay_ms)
    {
        wait_ms(1);
    }
}

int main() 
{
    BSP_LCD_Init();
    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    lcd_ticker.attach(lcd_draw_task, 0.25);
    
    while (1) 
    {
        in1 = 0.8;
        in2 = 0;
        in3 = 0.8;
        in4 = 0;
        splitted_wait_ms(5000);
        in1 = 0;
        in2 = 0.8;
        in3 = 0;
        in4 = 0.8;
        splitted_wait_ms(5000);
        in1 = 0.8;
        in2 = 0;
        in3 = 0;
        in4 = 0.8;
        splitted_wait_ms(5000);
    }
}
