//代理模式：以一个代理主题来操作真实主题，真实主题执行具体的业务，而代理主题负责其他琐碎的业务
//两个例子
//例子1：计算机1能上网，计算机2不能上网，计算机2需要通过将IE的代理设置为计算机1，通过计算机1上网
//真实主题：计算机1上网
//代理：将计算机2通过一定的协议，并检查用户有效性等等，连接到计算机1，最终通过计算机1上网
//用户看到的是代理，但是只看到了上网这个真实主题的行为，其他细节被隐藏了

//例子2：小明喜欢小花，想送小花礼物，但是不好意思自己去，于是委托小强去送礼物（最后小强和小花在一起了，悲剧啊，同学们千万不要这么干，喜欢就大胆的说出来）
//真实主题：送礼物
//代理：小强，从小明手里拿到礼物，跑腿，送给小花（说这是我自己送你的礼物。。。,，往兄弟两肋上插刀啊）
//小花只看到了送礼物的过程，中间的环节并不清楚

//下面我们把这个悲剧故事，以代码的形式表现出来

//先定义接口
typedef struct _SendGift
{
    /* data */
    void (*sendDoll)();
    void (*sendFlower)();
}TTSendGift;

//小明.c
static void sendDoll()
{
    printf("送你一个玩偶");
}
static void sendFlower()
{
    printf("送你一束花");
}

const TTSendGift SendGift = {
    .sendDoll = sendDoll,
    .sendFlower = sendFlower,
};

//代理 小强
typedef struct _Proxy
{
    void (*sendDoll)();
    void (*sendFlower)();//实现相同的接口函数
    void (*run)();//跑腿
    void (*init)(TTSendGift *pSendGift);//
}TTProxy;

TTSendGift *pSendGift;
static void run()
{
    /*跑到小花面前*/
}

static void sendDoll2()
{
    run();
    pSendGift->sendDoll();//实际是小明的礼物
}

static void sendFlower2()
{
    run();
    pSendGift->sendFlower();//实际是小明的礼物
}

static void init(TTSendGift *pGift)
{
    pSendGift = pGift;
}

const TTProxy Proxy = {
    .sendDoll = sendDoll2,
    .sendFlower = sendFlower2,
    .run = run,
    .init = init,
};


//main.c
void main()
{
    Proxy.init(&SendGift);
    Proxy.sendDoll();
    Proxy.sendFlower();
}
