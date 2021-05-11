#include <stdint.h>
//主站接口函数
float getTemperature()
{
    return 0;
}
float getHumidity()
{
    return 0;
}
float getPressure()
{
    return 0;
}

//一个错误的示范
void display1(float temp,float humidity,float pressure);//用户1的显示函数
void display2(float temp,float humidity,float pressure);//用户2的显示函数
void display3(float temp,float humidity,float pressure);//用户3的显示函数
//主站在数据准备完毕后，会自动调用changed，用于刷新显示
void changed()
{
    float temp = getTemperature();
    float humidity = getHumidity();
    float pressure = getPressure();

    display1(temp,humidity,pressure);
    display2(temp,humidity,pressure);
    display3(temp,humidity,pressure);
}

//想一想，这种编程模式有什么问题？和前面讲的面向接口的编程原则有什么冲突？
//在应用层体现的应该是抽象，display1是具体的实现，不应该出现在应用层，后面如果增加display4，是不是需要回来修改changed代码，修改了changed，是不是要把display123都测一遍？

//隆重介绍观察者模式
//和报纸一样，出版者+订阅者的模式=观察者模式，只需要订阅报纸，出新报纸后，出版商会按照名单派发报纸，而不需要每个人天天去问有新报纸了没

//观察者模式：一对多的依赖，被观察者状态发生变化后，观察它的人，即观察者会收到通知，执行相应的动作
//一种松耦合
typedef struct 
{
    void (*update)(float temp,float humidity,float pressure);
    /* data */
}TTObserver;


typedef struct 
{
    void (*registerObserver)(TTObserver observer);
    void (*removeObserver)(TTObserver observer);
    void (*notifyObservers)();
    /* data */
}TTObservable;


//主站端文件.c
TTObserver observerList[10];//也可以考虑用链表
uint8_t offset = 0;
float temp = 0;
float humidity = 0;
float pressure = 0;
static void registerObserver(TTObserver observer)
{
    memcpy(&observerList[offset],observer,sizeof(TTObserver));
    offset++;
}
static void removeObserver(TTObserver observer)
{
    for(int i = 0; i < 10; i++)
    {
        if(isEqual(observerList[i],observer))
        {
            clearObject(&observerList[i]);
            offset--;
        }
    }
}
static void notifyObservers()
{
    for(int i = 0; i < 10; i++)
    {
        if(notEmpty(observerList[i]))
        {
            observerList[10].update(temp,humidity,pressure);
        }
    }
}

const TTObservable Weather={
    .registerObserver = registerObserver,
    .removeObserver = removeObserver,
    .notifyObservers = notifyObservers,
};

//定时调用，或者其他
void changed()
{
    temp = getTemperature();
    humidity = getHumidity();
    pressure = getPressure();

    Weather.notifyObservers();
}

//用户端文件.c
//多样化的实现,user1.c
static void update1(float temp,float humidity,float pressure)
{
    display1(temp,humidity,pressure);
}
TTObserver User1 = {
    .update = update1,
};
//多样化的实现,user2.c
static void update2(float temp,float humidity,float pressure)
{
    display2(temp,humidity,pressure);
}
TTObserver User2 = {
    .update = update2,
};
//多样化的实现,user3.c
static void update3(float temp,float humidity,float pressure)
{
    display3(temp,humidity,pressure);
}
TTObserver User3 = {
    .update = update3,
};

//main.c
void main()
{
    Weather.registerObserver(User1);
    Weather.registerObserver(User2);
    Weather.registerObserver(User3);

    while (1)
    {
        Delay(3600);//每小时
        changed();
        /* code */
    }
    
}

//拓展一下：我们的程序中，哪些地方可以用到或者已经用到了观察者？
//中断函数。。。其他