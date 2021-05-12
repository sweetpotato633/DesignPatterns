#include <stdint.h>

//大家应该已经习惯了先抑后扬的风格，先来一个错误的示范
//糖果机.c
typedef enum{
    SOLD_OUT = 0,//没糖果了
    NO_QUARTER = 1,
    HAS_QUARTER = 2,
    SOLD = 3,
}eState;

static uint8_t state = NO_QUARTER;
static uint16_t CandyCount = 0;//糖果机里面一开始有多少糖果
static void init(uint16_t count)
{
    CandyCount = count;
    if(CandyCount > 0)
    {
        state = NO_QUARTER;
    }
}

//四种动作： 投币，退币，转曲柄，发放糖果（这个是内部状态，自己调用自己）
static void InsertQuarter()
{
    if(state == HAS_QUARTER)
    {
        printf("你已经投币了，不用再投了。");
    }
    else if(state == NO_QUARTER)
    {
        state = HAS_QUARTER;
        printf("投币成功，可以转曲柄出糖果了");
    }
    else if(state == SOLD_OUT)
    {
        printf("哎呀，糖果卖完了，你可以把投币收回去");
    }
    else if(state == SOLD)
    {
        printf("请等待上次操作完成");//这个地方其实有点问题，这次投币就白瞎了？原文如此，不进行逻辑补全了，毕竟我们的目的不是这个
    }
}
static void ejectQuarter()
{
    /*四种状态下，发生退币操作进行的动作*/
}
static void TurnCrank()
{
    /*四种状态下，转曲柄操作进行的动作*/
    if(state == HAS_QUARTER)
    {
        printf("转动了曲柄");
        state = SOLD;
        dispense();
    }
}
static void dispense()
{
    if(state == SOLD)
    {
        printf("糖果已发放");
        CandyCount-=1;
        if(CandyCount > 0)
        {
            state = NO_QUARTER;
        }
        else
        {
            state = SOLD_OUT;
        }
    }
    /*四种状态下，调用发放糖果操作进行的动作，这个是内部调用的*/
}

void StateMachine(uint8_t cmd)
{
    switch (cmd)
    {
    case 0:
        InsertQuarter();
        break;
    case 1:
        ejectQuarter();
        break;
    case 2:
        TurnCrank();
        break;
    default:
        break;
    }
}

//貌似很完美，问题来了，后面要增加一个新需求，在转动曲柄的时候，有一个人品判断，有10%的概率出现暴击，两个糖果
//新增一个状态，暴击状态，完蛋了，所有的代码都需要修改。当然，直接在disense函数中加入概率判断也可以，这个我们不抬杠哈。这里讨论的是需要增加一个状态怎么办

//按照之前讲的设计原则来分析：区分变和不变的，抽象和具体；多用组合，少用继承
//不变的是四种输入:投币，退币，转曲柄，发放糖果（这个是内部状态，自己调用自己）
//改变的是：不同输入下的状态
//不变的抽象化，抽离出接口


struct _StateInput
{
    void (*InsertQuarter)();
    void (*ejectQuarter)();
    void (*TurnCrank)();
    void (*dispense)();
    void (*init)(struct _StateMachine* state);
};

struct _StateMachine
{
    void (*InsertQuarter)();
    void (*ejectQuarter)();
    void (*TurnCrank)();
    void (*setState)(struct _StateInput* input);
    struct _StateInput* (*getInstanceOfState)(uint16_t stateCode);
};
typedef struct _StateInput TTStateInput;
typedef struct _StateMachine TTStateMachine;

//对变化的状态进行接口实现
//HasQuarter.c
static TTStateMachine* gloMachine;
static void InsertQuarter2()//用接口函数取代了if else
{
    printf("你已经投币了，不用再投了。");
}
static void ejectQuarter2()//用接口函数取代了if else
{
    printf("退币成功。");
    gloMachine->setState(gloMachine->getInstanceOfState(NO_QUARTER));
}
static void TurnCrank2()
{
    printf("转动了曲柄。");
    gloMachine->setState(gloMachine->getInstanceOfState(SOLD));    
}
static void dispense2()
{
    printf("无效动作，不会发生");
}
static void init(TTStateMachine *machine)
{
    gloMachine = machine;
}

const TTStateInput HasQuarter = {
    .InsertQuarter = InsertQuarter2,
    .ejectQuarter = ejectQuarter2,
    .TurnCrank = TurnCrank2,
    .dispense = dispense2,
    .init = init,
};
//其他状态.c


//StateMachine.c
static TTStateInput* currentState;
static void InsertQuarter3()//顶层应用体现的是抽象，而不是具体
{
    currentState->InsertQuarter();
}
static void ejectQuarter3()
{
    currentState->ejectQuarter();
}
static void TurnCrank3()
{
    currentState->TurnCrank();
}

static void setState(TTStateInput* state)
{
    currentState = state;
}

static TTStateInput* getInstanceOfState(uint16_t stateCode)
{
//工厂方法
}

const TTStateMachine StateMachine2 = {
    .InsertQuarter = InsertQuarter3,
    .ejectQuarter = ejectQuarter3,
    .TurnCrank = TurnCrank,
    .setState = setState,
    .getInstanceOfState = getInstanceOfState,
};

//顶层任务，调用StateMachine2，与底层状态无关
void DoStateMachine(uint8_t cmd)
{

}

//新增暴击状态怎么办？总共分3步
//增加 暴击.c文件，实现TTStateInput接口
//修改工厂方法
//修改HasQuarter的TurnCrank方法，根据概率，决定下一个状态是否产生暴击

//好吧，我承认，其实还是有耦合的，不过从层次和代码修改量上要好很多了
