#include <stdint.h>

//先来一个常规方法
//Group 1-7 cmd 1 on; 0 off
void RemoteControl(uint8_t Group,uint8_t cmd){
    switch (Group)
    {
    case 1:
        if(cmd == 1)
        {
            light_on();
        }
        else
        {
            light_off();
        }
        break;
    case 2:
        if(cmd == 1)
        {
            fan_high();
            DelayMin(10);
            fan_medium();
        }
        else
        {
            fan_off();
        }
        break;
    default:
        break;
    }
}

//Low爆了，对吧，通过前面的学习，可以很轻松的找出N多个违反设计原则的地方。但是这种代码，就是我们每天都在敲的代码
//引入命令模式，将命令执行的载体（电灯）和下发命令的对象分开（按键）
//举个栗子，也可以举好几个栗子
//餐厅里面，我们看到了一个新菜：“咖喱味孜然玉米炒葡萄”，感觉挺新鲜，想尝尝（提前打好120），就对服务员说，我要吃这个，服务员把要求写菜单上，然后把菜单给厨师，
//厨师看到后，把“咖喱味孜然玉米炒葡萄”做好，上桌。这个过程我们分析下
//首先，“咖喱味孜然玉米炒葡萄”我们不知道具体是什么东西，反正这玩意有个可以吃的属性
//服务员也不知道“咖喱味孜然玉米炒葡萄”怎么做，只负责记录要求，当然也可能贴心的问一下，需不需要提前打120
//只有厨师是最终的执行者
//类比一下：“咖喱味孜然玉米炒葡萄”写到菜单上，对应与电灯的light_on方法关联到第一组的on按键上
//服务员把菜单传递给厨师，对应于用户按下了第一组的on按键
//只有厨师才知道这道菜到底是什么玩意，厨师才是真正的执行者，类比于只有到最底层，命令才被翻译为开灯
//几个角色
//命令对象：具体执行动作的
//关联者：耦合部分，将命令和按钮相关联，这部分不知道命令的具体内容
//发起者：按按钮的人

//先写命令对象，按照惯例，先抽象
typedef struct{
    void (*execute)();
}TTComand;

//电灯.c文件
void buttonOnLight()
{
    light_on();
}
const TTComand CommandLightOn = {
    .execute = buttonOnLight,
};
void buttonOffLight()
{
    light_off();
}
const TTComand CommandLightOff = {
    .execute = buttonOffLight,
};

//风扇.c文件
void buttonOnFan()
{
    fan_high();
    DelayMin(10);
    fan_medium();
}
const TTComand CommandFanOn = {
    .execute = buttonOnFan,
};
void buttonOffFan()
{
    light_off();
}
const TTComand CommandFanOff = {
    .execute = buttonOffFan,
};


//关联者对象.c文件
TTComand *onCommands[7];
TTComand *offCommands[7];

typedef struct _Controler
{
    void (*setCmd)(uint8_t slot,TTComand *onCmd,TTComand *offCmd);
    void (*onPushed)(uint8_t slot);
    void (*offPushed)(uint8_t slot);
}TTControler;

static void setCmd(uint8_t slot,TTComand *onCmd,TTComand *offCmd)
{
    onCommands[slot] = onCmd;
    offCommands[slot] = offCmd;
}

static void onPushed(uint8_t slot)
{
    onCommands[slot]->execute();
}

static void offPushed(uint8_t slot)
{
    offCommands[slot]->execute();
}

const TTControler Controler = {
    .setCmd = setCmd,
    .onPushed = onPushed,
    .offPushed = offPushed,
};

//发起者.c 耦合部分
void ControlLoader()
{
    Controler.setCmd(0,&CommandLightOn,&CommandLightOff);
    Controler.setCmd(1,&CommandFanOn,&CommandFanOff);//这个地方是不是可以考虑用个工厂？此处只是表述编程思路，大家可以自己实现
}

void ControlExec(uint8_t slot,uint8_t cmd)//cmd 0 off;1 on
{
    if(cmd == 1)
    {
        Controler.onPushed(slot);
    }
    else
    {
        Controler.offPushed(slot);
    }
}
//当然也可以用接口再封装一下