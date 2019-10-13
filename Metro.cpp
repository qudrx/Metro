#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

int strt,st,stt,enrt,en,enn;
int CNT[21] = {0,23,18,35,23,32, 20,19,12,13,45, 16,7,21,20, 10,13,12,14,12, 3};
string ROUTEI[21] = {"0","1号线","2号线","4号线","5号线","6号线","7号线","8号线","8号线南段",
                     "9号线","10号线","13号线","14号线西","14号线东","15号线",
                     "16号线","八通线","昌平线","亦庄线","房山线","机场线"};
string SPOTI[21][46];

int G[369][369];
int MAXN = 368, EX = 54;
int EXCHANGE[55][3];
int ANS[151],RES[151];
int Pre[22] = {0,0,23,41,76,99,131,151,170,182,195,240,256,263,284,304,314,327,339,353,365,368};
bool vis[368];
int dis[368];


// 计算函数
void PRINT()
{
    int r,ss = en,k = 0;
    cout << "\n *** 查询结果 ***\n" << "路线共" << dis[en]+1 << "站：\n";

    while (ANS[en] != -1) {
        k++;
        RES[k] = en;
//        cout << en << "  ";
        en = ANS[en];
    }

    int RESS[151],RESROUTE[151];
    for (int i = k ; i >= 1 ; i --)  // Reserve and Add
        RESS[k-i+2] = RES[i];
    RESS[1] = st;
    RESS[k+1] = ss;
    k ++;
    for (int i = 1 ; i <= k ; i ++) {
        int p = 1;
        while (!(RESS[i] > Pre[p] && RESS[i] <= Pre[p+1]))
            p ++;
        RESROUTE[i] = p;
    }
    int o = RESROUTE[1];
    int z = 1;
    cout << "< " << ROUTEI[o] << " > :";
    bool F = false;
    while (z <= k) {
        while (RESROUTE[z] == o) {
            cout << "   " << SPOTI[RESROUTE[z]][RESS[z] - Pre[RESROUTE[z]]];
            z ++;
            if (z > k) {
                F = true;
                break;
            }
        }
        if (F)
            break;
        if (RESROUTE[z] != o) {
            o = RESROUTE[z];
            cout << "\n< " << ROUTEI[o] << " > :";
        }
        z ++;
    }



    // Clear
    strt = st = stt = enrt = en = enn = 0;
    for (int i = 0 ; i < MAXN ; i ++) {
        ANS[i] = -1;
        dis[i] = INF;
    }
    memset(vis,0,sizeof(vis));

    cout << '\n';
}

void CAL() //Dijkstra
{
    dis[st] = 0;
    for (int i = 1 ; i <= MAXN ; i ++ ) {
        int minv = INF;
        int u = -1;
        for (int j = 1 ; j <= MAXN ; j ++) {
            if (dis[j] < minv && vis[j] == 0) {
                minv = dis[j];
                u = j;
            }
        }
        if (u == -1)
            return;
        vis[u] = 1;
        for (int v = 1 ; v <= MAXN ; v ++) {
            if (vis[v]==0 && G[u][v]!=INF) {
                if (dis[v] > dis[u]+G[u][v]) {
                    dis[v] = dis[u]+G[u][v];
                    ANS[v] = u;//path[v]的值等于它的前一个结点的编号
                }
            }
        }
    }

    PRINT();
}

// 界面相关
void MAJOR();
void ROUTE(int s);
void SPOT(int s,int q);

void ROUTECHART()
{
    for (int i = 1 ; i <= 20 ; i ++)
        cout << i << " :  " << ROUTEI[i] << '\n';
}

void SPOTCHART(int rt)
{
    for (int i = 1 ; i <= CNT[rt] ; i ++)
        cout << i << " :  " << SPOTI[rt][i] << '\n';
}

void INIT()
{
    printf("欢迎进入北京地铁换乘系统，请先设定您的起点和终点\n");
    //初始化SPOT
    for (int i = 0 ; i < 21 ; i ++)
        for (int j = 0 ; j < 46 ; j ++)
            SPOTI[i][j] = "";
    SPOTI[1][1] = "苹果园站",SPOTI[1][2] = "古城站",SPOTI[1][3] = "八角游乐园站";
    SPOTI[1][4] = "八宝山站",SPOTI[1][5] = "玉泉路站",SPOTI[1][6] = "五棵松站";
    SPOTI[1][7] = "万寿路站";SPOTI[1][8] = "公主坟站";SPOTI[1][9] = "军事博物馆站";
    SPOTI[1][10] = "木樨地站";SPOTI[1][11] = "南礼士路站";SPOTI[1][12] = "复兴门站";
    SPOTI[1][13] = "西单站";SPOTI[1][14] = "天安门西站";SPOTI[1][15] = "天安门东站";
    SPOTI[1][16] = "王府井站";SPOTI[1][17] = "东单站";SPOTI[1][18] = "建国门站";
    SPOTI[1][19] = "永安里站";SPOTI[1][20] = "国贸站";SPOTI[1][21] = "大望路站";
    SPOTI[1][22] = "四惠站";SPOTI[1][23] = "四惠东站";

    SPOTI[2][1] = "西直门站",SPOTI[2][2] = "积水潭站",SPOTI[2][3] = "鼓楼大街站";
    SPOTI[2][4] = "安定门站",SPOTI[2][5] = "雍和宫站",SPOTI[2][6] = "东直门站";
    SPOTI[2][7] = "东四十条站";SPOTI[2][8] = "朝阳门站";SPOTI[2][9] = "建国门站";
    SPOTI[2][10] = "北京站";SPOTI[2][11] = "崇文门站";SPOTI[2][12] = "前门站";
    SPOTI[2][13] = "和平门站";SPOTI[2][14] = "宣武门站";SPOTI[2][15] = "长椿街站";
    SPOTI[2][16] = "复兴门站";SPOTI[2][17] = "阜成门站";SPOTI[2][18] = "车公庄站";

    SPOTI[3][1] = "天宫院",SPOTI[3][2] = "生物医药基地",SPOTI[3][3] = "义和庄";
    SPOTI[3][4] = "黄村火车站",SPOTI[3][5] = "黄村西大街",SPOTI[3][6] = "清源路";
    SPOTI[3][7] = "枣园";SPOTI[3][8] = "高米店南";SPOTI[3][9] = "高米店北";
    SPOTI[3][10] = "西红门";SPOTI[3][11] = "新宫";SPOTI[3][12] = "公益西桥";
    SPOTI[3][13] = "角门西";SPOTI[3][14] = "马家堡";SPOTI[3][15] = "北京南站";
    SPOTI[3][16] = "陶然亭";SPOTI[3][17] = "菜市口";SPOTI[3][18] = "宣武门";
    SPOTI[3][19] = "西单";SPOTI[3][20] = "灵境胡同";SPOTI[3][21] = "西四";
    SPOTI[3][22] = "平安里",SPOTI[3][23] = "新街口",SPOTI[3][24] = "西直门";
    SPOTI[3][25] = "动物园",SPOTI[3][26] = "国家图书馆",SPOTI[3][27] = "魏公村";
    SPOTI[3][28] = "人民大学";SPOTI[3][29] = "海淀黄庄";SPOTI[3][30] = "中关村";
    SPOTI[3][31] = "北京大学东门";SPOTI[3][32] = "圆明园";SPOTI[3][33] = "西苑";
    SPOTI[3][34] = "北宫门";SPOTI[3][35] = "安河桥北";

    SPOTI[4][1] = "宋家庄",SPOTI[4][2] = "刘家窑站",SPOTI[4][3] = "蒲黄榆站";
    SPOTI[4][4] = "天坛东门站",SPOTI[4][5] = "磁器口站",SPOTI[4][6] = "崇文门站";
    SPOTI[4][7] = "东单站";SPOTI[4][8] = "灯市口站";SPOTI[4][9] = "东四站";
    SPOTI[4][10] = "张自忠路站";SPOTI[4][11] = "北新桥站";SPOTI[4][12] = "雍和宫站";
    SPOTI[4][13] = "和平里北街站";SPOTI[4][14] = "和平西桥站";SPOTI[4][15] = "惠新西街南口站";
    SPOTI[4][16] = "惠新西街北口站";SPOTI[4][17] = "大屯路东站";SPOTI[4][18] = "北苑路北站";
    SPOTI[4][19] = "立水桥南站";SPOTI[4][20] = "立水桥站";SPOTI[4][21] = "天通苑南站";
    SPOTI[4][22] = "天通苑站";SPOTI[4][23] = "天通苑北站";

    SPOTI[5][1] = "潞城站",SPOTI[5][2] = "东夏园站",SPOTI[5][3] = "郝家府站";
    SPOTI[5][4] = "北运河东站",SPOTI[5][5] = "北运河西站",SPOTI[5][6] = "通州北关站";
    SPOTI[5][7] = "物资学院路站";SPOTI[5][8] = "草房站";SPOTI[5][9] = "常营站";
    SPOTI[5][10] = "黄渠站";SPOTI[5][11] = "褡裢坡站";SPOTI[5][12] = "青年路站";
    SPOTI[5][13] = "十里堡站";SPOTI[5][14] = "金台路站";SPOTI[5][15] = "呼家楼站";
    SPOTI[5][16] = "东大桥站";SPOTI[5][17] = "朝阳门站";SPOTI[5][18] = "东四站";
    SPOTI[5][19] = "南锣鼓巷站";SPOTI[5][20] = "北海北站";SPOTI[5][21] = "平安里站";
    SPOTI[5][22] = "车公庄站";SPOTI[5][23] = "车公庄西站";SPOTI[5][24] = "白石桥南站";
    SPOTI[5][25] = "花园桥站";SPOTI[5][26] = "慈寿寺站";SPOTI[5][27] = "海淀五路居站";
    SPOTI[5][28] = "田村站";SPOTI[5][29] = "廖公庄站";SPOTI[5][30] = "西黄村站";
    SPOTI[5][31] = "杨庄站";SPOTI[5][32] = "金安桥站";

    SPOTI[6][1] = "北京西站",SPOTI[6][2] = "湾子站",SPOTI[6][3] = "达官营站";
    SPOTI[6][4] = "广安门内站",SPOTI[6][5] = "菜市口站",SPOTI[6][6] = "虎坊桥站";
    SPOTI[6][7] = "珠市口站";SPOTI[6][8] = "桥湾站";SPOTI[6][9] = "磁器口站";
    SPOTI[6][10] = "广渠门内站";SPOTI[6][11] = "广渠门外站";SPOTI[6][12] = "九龙山站";
    SPOTI[6][13] = "大郊亭站";SPOTI[6][14] = "百子湾站";SPOTI[6][15] = "化工站";
    SPOTI[6][16] = "南楼梓庄站";SPOTI[6][17] = "欢乐谷景区站";SPOTI[6][18] = "垡头站";
    SPOTI[6][19] = "双合站";SPOTI[6][20] = "焦化厂站";

    SPOTI[7][1] = "朱辛庄站",SPOTI[7][2] = "育知路站",SPOTI[7][3] = "平西府站";
    SPOTI[7][4] = "回龙观东大街站",SPOTI[7][5] = "霍营站",SPOTI[7][6] = "育新站";
    SPOTI[7][7] = "西小口站";SPOTI[7][8] = "永泰庄站";SPOTI[7][9] = "林萃桥站";
    SPOTI[7][10] = "森林公园南门站";SPOTI[7][11] = "奥林匹克公园站";SPOTI[7][12] = "奥体中心站";
    SPOTI[7][13] = "北土城站";SPOTI[7][14] = "安华桥站";SPOTI[7][15] = "安德里北街站";
    SPOTI[7][16] = "鼓楼大街站";SPOTI[7][17] = "什刹海站";SPOTI[7][18] = "南锣鼓巷站";
    SPOTI[7][19] = "中国美术馆站";

    SPOTI[8][1] = "珠市口站",SPOTI[8][2] = "天桥站",SPOTI[8][3] = "永定门外站";
    SPOTI[8][4] = "木樨园站",SPOTI[8][5] = "海户屯站",SPOTI[8][6] = "大红门南站";
    SPOTI[8][7] = "和义站";SPOTI[8][8] = "东高地站";SPOTI[8][9] = "火箭万源站";
    SPOTI[8][10] = "五福堂站";SPOTI[8][11] = "德茂站";SPOTI[8][12] = "瀛海站";

    SPOTI[9][1] = "国家图书馆站",SPOTI[9][2] = "白石桥南站",SPOTI[9][3] = "白堆子站";
    SPOTI[9][4] = "军事博物馆站",SPOTI[9][5] = "北京西站",SPOTI[9][6] = "六里桥东站";
    SPOTI[9][7] = "六里桥站";SPOTI[9][8] = "七里庄站";SPOTI[9][9] = "丰台东大街站";
    SPOTI[9][10] = "丰台南路站";SPOTI[9][11] = "科怡路站";SPOTI[9][12] = "丰台科技园站";
    SPOTI[9][13] = "郭公庄站";

    SPOTI[10][1] = "巴沟站",SPOTI[10][2] = "苏州街站",SPOTI[10][3] = "海淀黄庄站";
    SPOTI[10][4] = "知春里站",SPOTI[10][5] = "知春路站",SPOTI[10][6] = "西土城站";
    SPOTI[10][7] = "牡丹园站";SPOTI[10][8] = "健德门站";SPOTI[10][9] = "北土城站";
    SPOTI[10][10] = "安贞门站";SPOTI[10][11] = "惠新西街南口站";SPOTI[10][12] = "芍药居站";
    SPOTI[10][13] = "太阳宫站";SPOTI[10][14] = "三元桥站";SPOTI[10][15] = "亮马桥站";
    SPOTI[10][16] = "农业展览馆站";SPOTI[10][17] = "团结湖站";SPOTI[10][18] = "呼家楼站";
    SPOTI[10][19] = "金台夕照站";SPOTI[10][20] = "国贸站";SPOTI[10][21] = "双井站";
    SPOTI[10][22] = "劲松站";SPOTI[10][23] = "潘家园站";SPOTI[10][24] = "十里河站";
    SPOTI[10][25] = "分钟寺站";SPOTI[10][26] = "成寿寺站";SPOTI[10][27] = "宋家庄站";
    SPOTI[10][28] = "石榴庄站";SPOTI[10][29] = "大红门站";SPOTI[10][30] = "角门东站";
    SPOTI[10][31] = "角门西站";SPOTI[10][32] = "草桥站";SPOTI[10][33] = "纪家庙站";
    SPOTI[10][34] = "首经贸站";SPOTI[10][35] = "丰台站";SPOTI[10][36] = "泥洼站";
    SPOTI[10][37] = "西局站";SPOTI[10][38] = "六里桥站";SPOTI[10][39] = "莲花桥站";
    SPOTI[10][40] = "公主坟站";SPOTI[10][41] = "西钓鱼台站";SPOTI[10][42] = "慈寿寺站";
    SPOTI[10][43] = "车道沟站";SPOTI[10][44] = "长春桥站";SPOTI[10][45] = "火器营站";

    SPOTI[11][1] = "西直门站",SPOTI[11][2] = "大钟寺站",SPOTI[11][3] = "知春路站";
    SPOTI[11][4] = "五道口站",SPOTI[11][5] = "上地站",SPOTI[11][6] = "西二旗站";
    SPOTI[11][7] = "龙泽站";SPOTI[11][8] = "回龙观站";SPOTI[11][9] = "霍营站";
    SPOTI[11][10] = "立水桥站";SPOTI[11][11] = "北苑站";SPOTI[11][12] = "望京西站";
    SPOTI[11][13] = "芍药居站";SPOTI[11][14] = "光熙门站";SPOTI[11][15] = "柳芳站";
    SPOTI[11][16] = "东直门站";

    SPOTI[12][1] = "张郭庄站",SPOTI[12][2] = "园博园站",SPOTI[12][3] = "大瓦窑站";
    SPOTI[12][4] = "郭庄子站",SPOTI[12][5] = "大井站",SPOTI[12][6] = "七里庄站";
    SPOTI[12][7] = "西局站";

    SPOTI[13][1] = "北京南站",SPOTI[13][2] = "陶然桥站",SPOTI[13][3] = "永定门外站";
    SPOTI[13][4] = "景泰站",SPOTI[13][5] = "蒲黄榆站",SPOTI[13][6] = "方庄站";
    SPOTI[13][7] = "十里河站";SPOTI[13][8] = "北工大西门站";SPOTI[13][9] = "九龙山站";
    SPOTI[13][10] = "大望路站";SPOTI[13][11] = "金台路站";SPOTI[13][12] = "朝阳公园站";
    SPOTI[13][13] = "枣营站";SPOTI[13][14] = "东风北桥站";SPOTI[13][15] = "将台站";
    SPOTI[13][16] = "望京南站";SPOTI[13][17] = "阜通站";SPOTI[13][18] = "望京站";
    SPOTI[13][19] = "东湖渠站";SPOTI[13][20] = "来广营站";SPOTI[13][21] = "善各庄站";

    SPOTI[14][1] = "清华东路西口站",SPOTI[14][2] = "六道口站",SPOTI[14][3] = "北沙滩站";
    SPOTI[14][4] = "奥林匹克公园站",SPOTI[14][5] = "安立路站",SPOTI[14][6] = "大屯路东站";
    SPOTI[14][7] = "关庄站";SPOTI[14][8] = "望京西站";SPOTI[14][9] = "望京站";
    SPOTI[14][10] = "望京东站";SPOTI[14][11] = "崔各庄站";SPOTI[14][12] = "马泉营站";
    SPOTI[14][13] = "孙河站";SPOTI[14][14] = "国展站";SPOTI[14][15] = "花梨坎站";
    SPOTI[14][16] = "后沙峪站";SPOTI[14][17] = "南法信站";SPOTI[14][18] = "石门站";
    SPOTI[14][19] = "顺义站";SPOTI[14][20] = "俸伯站";

    SPOTI[15][1] = "北安河站",SPOTI[15][2] = "温阳路站",SPOTI[15][3] = "稻香湖路站";
    SPOTI[15][4] = "屯佃站",SPOTI[15][5] = "永丰站",SPOTI[15][6] = "永丰南站";
    SPOTI[15][7] = "西北旺站";SPOTI[15][8] = "马连洼站";SPOTI[15][9] = "农大南路站";
    SPOTI[15][10] = "西苑站";

    SPOTI[16][1] = "四惠站",SPOTI[16][2] = "四惠东站",SPOTI[16][3] = "高碑店站";
    SPOTI[16][4] = "传媒大学站",SPOTI[16][5] = "双桥站",SPOTI[16][6] = "管庄站";
    SPOTI[16][7] = "八里桥站";SPOTI[16][8] = "通州北苑站";SPOTI[16][9] = "果园站";
    SPOTI[16][10] = "九棵树站";SPOTI[16][11] = "梨园站";SPOTI[16][12] = "临河里站";
    SPOTI[16][13] = "土桥站";

    SPOTI[17][1] = "昌平西山口站",SPOTI[17][2] = "十三陵景区站",SPOTI[17][3] = "昌平站";
    SPOTI[17][4] = "昌平东关站",SPOTI[17][5] = "北邵洼站",SPOTI[17][6] = "南邵站";
    SPOTI[17][7] = "沙河高教园站";SPOTI[17][8] = "沙河站";SPOTI[17][9] = "巩华城站";
    SPOTI[17][10] = "朱辛庄站";SPOTI[17][11] = "生命科学园站";SPOTI[17][12] = "西二旗站";

    SPOTI[18][1] = "宋家庄站",SPOTI[18][2] = "肖村站",SPOTI[18][3] = "小红门站";
    SPOTI[18][4] = "旧宫站",SPOTI[18][5] = "亦庄桥站",SPOTI[18][6] = "亦庄文化园站";
    SPOTI[18][7] = "万源街站";SPOTI[18][8] = "荣京东街站";SPOTI[18][9] = "荣昌东街站";
    SPOTI[18][10] = "同济南路站";SPOTI[18][11] = "经海路站";SPOTI[18][12] = "次渠南站";
    SPOTI[18][13] = "次渠站";SPOTI[18][14] = "亦庄火车站";

    SPOTI[19][1] = "郭公庄站",SPOTI[19][2] = "大葆台站",SPOTI[19][3] = "稻田站";
    SPOTI[19][4] = "长阳站",SPOTI[19][5] = "篱笆房站",SPOTI[19][6] = "广阳城站";
    SPOTI[19][7] = "良乡大学城北站";SPOTI[19][8] = "良乡大学城站";SPOTI[19][9] = "良乡大学城西站";
    SPOTI[19][10] = "良乡南关站";SPOTI[19][11] = "苏庄站";SPOTI[19][12] = "阎村东站";

    SPOTI[20][1] = "东直门站",SPOTI[20][2] = "三元桥站",SPOTI[20][3] = "航站楼站";


    //初始化EXCHANGE
//    memset(Pre,0,sizeof(Pre));
//    for (int i = 2 ; i <= 20 ; i ++)
//        Pre[i] = Pre[i-1] + CNT[i-1];

    for (int i = 1 ; i <= 54 ; i ++)
        EXCHANGE[i][2] = -1;

    EXCHANGE[1][0] = 12;EXCHANGE[1][1] = 39;
    EXCHANGE[2][0] = 13;EXCHANGE[2][1] = 60;
    EXCHANGE[3][0] = 9;EXCHANGE[3][1] = 186;
    EXCHANGE[4][0] = 20;EXCHANGE[4][1] = 215;
    EXCHANGE[5][0] = 22;EXCHANGE[5][1] = 315;
    EXCHANGE[6][0] = 21;EXCHANGE[6][1] = 273;
    EXCHANGE[7][0] = 37;EXCHANGE[7][1] = 59;
    EXCHANGE[8][0] = 34;EXCHANGE[8][1] = 82;
    EXCHANGE[9][0] = 41;EXCHANGE[9][1] = 121;
    EXCHANGE[10][0] = 39;EXCHANGE[10][1] = 256;EXCHANGE[10][2] = 366;
    EXCHANGE[11][0] = 58;EXCHANGE[11][1] = 136;
    EXCHANGE[12][0] = 70;EXCHANGE[12][1] = 198;
    EXCHANGE[13][0] = 56;EXCHANGE[13][1] = 264;
    EXCHANGE[14][0] = 85;EXCHANGE[14][1] = 117;
    EXCHANGE[15][0] = 93;EXCHANGE[15][1] = 290;
    EXCHANGE[16][0] = 91;EXCHANGE[16][1] = 206;
    EXCHANGE[17][0] = 96;EXCHANGE[17][1] = 250;
    EXCHANGE[18][0] = 123;EXCHANGE[18][1] = 184;
    EXCHANGE[19][0] = 114;EXCHANGE[19][1] = 213;
    EXCHANGE[20][0] = 132;EXCHANGE[20][1] = 187;
    EXCHANGE[21][0] = 155;EXCHANGE[21][1] = 249;
    EXCHANGE[22][0] = 152;EXCHANGE[22][1] = 250;
    EXCHANGE[23][0] = 190;EXCHANGE[23][1] = 262;
    EXCHANGE[24][0] = 201;EXCHANGE[24][1] = 243;
    EXCHANGE[25][0] = 132;EXCHANGE[25][1] = 263;
    EXCHANGE[26][0] = 119;EXCHANGE[26][1] = 270;
    EXCHANGE[27][0] = 252;EXCHANGE[27][1] = 292;
    EXCHANGE[28][0] = 8;EXCHANGE[28][1] = 32;
    EXCHANGE[29][0] = 17;EXCHANGE[29][1] = 83;
    EXCHANGE[30][0] = 8;EXCHANGE[30][1] = 235;
    EXCHANGE[31][0] = 23;EXCHANGE[31][1] = 316;
    EXCHANGE[32][0] = 24;EXCHANGE[32][1] = 65;EXCHANGE[32][2] = 241;
    EXCHANGE[33][0] = 143;EXCHANGE[33][1] = 272;
    EXCHANGE[34][0] = 28;EXCHANGE[34][1] = 88;
    EXCHANGE[35][0] = 31;EXCHANGE[35][1] = 116;
    EXCHANGE[36][0] = 26;EXCHANGE[36][1] = 157;
    EXCHANGE[37][0] = 63;EXCHANGE[37][1] = 120;
    EXCHANGE[38][0] = 67;EXCHANGE[38][1] = 183;
    EXCHANGE[39][0] = 54;EXCHANGE[39][1] = 226;
    EXCHANGE[40][0] = 74;EXCHANGE[40][1] = 314;
    EXCHANGE[41][0] = 81;EXCHANGE[41][1] = 140;
    EXCHANGE[42][0] = 79;EXCHANGE[42][1] = 268;
    EXCHANGE[43][0] = 77;EXCHANGE[43][1] = 222;EXCHANGE[43][2] = 340;
    EXCHANGE[44][0] = 118;EXCHANGE[44][1] = 169;
    EXCHANGE[45][0] = 125;EXCHANGE[45][1] = 137;
    EXCHANGE[46][0] = 113;EXCHANGE[46][1] = 274;
    EXCHANGE[47][0] = 163;EXCHANGE[47][1] = 204;
    EXCHANGE[48][0] = 162;EXCHANGE[48][1] = 288;
    EXCHANGE[49][0] = 189;EXCHANGE[49][1] = 233;
    EXCHANGE[50][0] = 195;EXCHANGE[50][1] = 354;
    EXCHANGE[51][0] = 207;EXCHANGE[51][1] = 253;
    EXCHANGE[52][0] = 209;EXCHANGE[52][1] = 367;
    EXCHANGE[53][0] = 246;EXCHANGE[53][1] = 339;
    EXCHANGE[54][0] = 281;EXCHANGE[54][1] = 293;


    //初始化图
    for (int i = 1 ; i <= MAXN ; i ++)  //Init
        for (int j = 1 ; j <= MAXN ; j ++)
            G[i][j] = INF;              //普通线性线路
    for (int i = 1 ; i <= 20 ; i ++)
        for (int j = 1 ; j < CNT[i] ; j ++) {
            G[Pre[i]+j][Pre[i]+j+1] = 1;
            G[Pre[i]+j+1][Pre[i]+j] = 1;
        }
                                       //环形相连
    G[Pre[2]+1][Pre[2]+CNT[2]] = 1;
    G[Pre[2]+CNT[2]][Pre[2]+1] = 1;
    G[Pre[10]+1][Pre[10]+CNT[10]] = 1;
    G[Pre[10]+CNT[10]][Pre[10]+1] = 1;
                                       //换乘相连
    for (int i = 1 ; i <= EX ; i ++) {
        G[EXCHANGE[i][0]][EXCHANGE[i][1]] = 0;
        G[EXCHANGE[i][1]][EXCHANGE[i][0]] = 0;
        if (EXCHANGE[i][2] != -1) {
            G[EXCHANGE[i][0]][EXCHANGE[i][2]] = 0;
            G[EXCHANGE[i][2]][EXCHANGE[i][0]] = 0;
            G[EXCHANGE[i][1]][EXCHANGE[i][2]] = 0;
            G[EXCHANGE[i][2]][EXCHANGE[i][1]] = 0;
        }
    }

    for (int i = 0 ; i <= MAXN ; i ++) {
        ANS[i] = -1;
        dis[i] = INF;
    }
    memset(vis,0,sizeof(0));

    // 初始化完成
}


// 主函数
int main()
{
    INIT();

    while (1) {
//        memset(ANS,0,sizeof(ANS));
        MAJOR();
    }

    return 0;
}


// 界面函数
void SPOT(int s,int q)
{
    string temp;
    int w = -1;

    if (s == 1)
        temp = "起点";
    else
        temp = "终点";

    cout << "\n *** 当前界面为" << temp << "站点选择界面 ***\n";
    printf("输入0返回上层界面\n");
    cout << "请根据下表输入您的" << temp << "站点\n";
    SPOTCHART(q);


    while (w < 0 || w > CNT[q]) {
        scanf("%d",&w);
        if (w < 0 || w > CNT[q])
            printf("无效站点参数!\n");
        else
            break;
    }

    if (w == 0)
        ROUTE(s);
    else {
        if (s == 1) {
            strt = q;
            st = Pre[q] + w;
            stt = w;
        } else {
            enrt = q;
            en = Pre[q] + w;
            enn = w;
        }
    }
}

void ROUTE(int s)
{
    string temp;
    int q = -1;

    if (s == 1)
        temp = "起点";
    else
        temp = "终点";

    cout << "\n *** 当前界面为" << temp << "路线选择界面 ***\n";
    printf("输入0返回上层界面\n");
    cout << "请根据下表输入您的" << temp << "路线\n";
    ROUTECHART();

    while (q < 0 || q > 20) {
        scanf("%d",&q);
        if (q < 0 || q > 20)
            printf("无效路线参数!\n");
        else
            break;
    }

    if (q == 0)
        MAJOR();
    else
        SPOT(s,q);
}

void MAJOR()
{
    int op;
    printf("\n当前界面为主界面\n");
    printf("输入-1退出本系统，输入999查看地铁线路信息，输入0开始查询，输入1设定起点，输入2设定终点\n");
    cout << "当前起点： ";
    if (st&&strt)
        cout << SPOTI[strt][stt] << '\n';
    else
        cout << "无\n";
    cout << "当前终点： ";
    if (en&&enrt)
        cout << SPOTI[enrt][enn] << '\n';
    else
        cout << "无\n";

    scanf("%d",&op);
    if (op == -1)
        exit(0);
    else if (op == 999) {
        cout << "\n*** 地铁线路图 ***\n";
        for (int i = 1 ; i <= 20 ; i ++) {
            cout << "<" << ROUTEI[i] << "> :";
            for (int j = 1 ; j <= CNT[i] ; j ++)
                cout << "  " << SPOTI[i][j];
            cout << '\n';
        }
        cout << '\n';
    }
    else if (op == 0) {
        if (st==0 || en==0)
            printf("请先设定起点和终点");
        else
            CAL();
    } else if (op==1 || op==2)
        ROUTE(op);
    else
        printf("无效操作数!\n");
}