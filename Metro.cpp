#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

int strt,st,stt,enrt,en,enn;
int CNT[21] = {0,23,18,35,23,32, 20,19,12,13,45, 16,7,21,20, 10,13,12,14,12, 3};
string ROUTEI[21] = {"0","1����","2����","4����","5����","6����","7����","8����","8�����϶�",
                     "9����","10����","13����","14������","14���߶�","15����",
                     "16����","��ͨ��","��ƽ��","��ׯ��","��ɽ��","������"};
string SPOTI[21][46];

int G[369][369];
int MAXN = 368, EX = 54;
int EXCHANGE[55][3];
int ANS[151],RES[151];
int Pre[22] = {0,0,23,41,76,99,131,151,170,182,195,240,256,263,284,304,314,327,339,353,365,368};
bool vis[368];
int dis[368];


// ���㺯��
void PRINT()
{
    int r,ss = en,k = 0;
    cout << "\n *** ��ѯ��� ***\n" << "·�߹�" << dis[en]+1 << "վ��\n";

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
                    ANS[v] = u;//path[v]��ֵ��������ǰһ�����ı��
                }
            }
        }
    }

    PRINT();
}

// �������
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
    printf("��ӭ���뱱����������ϵͳ�������趨���������յ�\n");
    //��ʼ��SPOT
    for (int i = 0 ; i < 21 ; i ++)
        for (int j = 0 ; j < 46 ; j ++)
            SPOTI[i][j] = "";
    SPOTI[1][1] = "ƻ��԰վ",SPOTI[1][2] = "�ų�վ",SPOTI[1][3] = "�˽�����԰վ";
    SPOTI[1][4] = "�˱�ɽվ",SPOTI[1][5] = "��Ȫ·վ",SPOTI[1][6] = "�����վ";
    SPOTI[1][7] = "����·վ";SPOTI[1][8] = "������վ";SPOTI[1][9] = "���²����վ";
    SPOTI[1][10] = "ľ�ص�վ";SPOTI[1][11] = "����ʿ·վ";SPOTI[1][12] = "������վ";
    SPOTI[1][13] = "����վ";SPOTI[1][14] = "�찲����վ";SPOTI[1][15] = "�찲�Ŷ�վ";
    SPOTI[1][16] = "������վ";SPOTI[1][17] = "����վ";SPOTI[1][18] = "������վ";
    SPOTI[1][19] = "������վ";SPOTI[1][20] = "��óվ";SPOTI[1][21] = "����·վ";
    SPOTI[1][22] = "�Ļ�վ";SPOTI[1][23] = "�Ļݶ�վ";

    SPOTI[2][1] = "��ֱ��վ",SPOTI[2][2] = "��ˮ̶վ",SPOTI[2][3] = "��¥���վ";
    SPOTI[2][4] = "������վ",SPOTI[2][5] = "Ӻ�͹�վ",SPOTI[2][6] = "��ֱ��վ";
    SPOTI[2][7] = "����ʮ��վ";SPOTI[2][8] = "������վ";SPOTI[2][9] = "������վ";
    SPOTI[2][10] = "����վ";SPOTI[2][11] = "������վ";SPOTI[2][12] = "ǰ��վ";
    SPOTI[2][13] = "��ƽ��վ";SPOTI[2][14] = "������վ";SPOTI[2][15] = "������վ";
    SPOTI[2][16] = "������վ";SPOTI[2][17] = "������վ";SPOTI[2][18] = "����ׯվ";

    SPOTI[3][1] = "�칬Ժ",SPOTI[3][2] = "����ҽҩ����",SPOTI[3][3] = "���ׯ";
    SPOTI[3][4] = "�ƴ��վ",SPOTI[3][5] = "�ƴ������",SPOTI[3][6] = "��Դ·";
    SPOTI[3][7] = "��԰";SPOTI[3][8] = "���׵���";SPOTI[3][9] = "���׵걱";
    SPOTI[3][10] = "������";SPOTI[3][11] = "�¹�";SPOTI[3][12] = "��������";
    SPOTI[3][13] = "������";SPOTI[3][14] = "��ұ�";SPOTI[3][15] = "������վ";
    SPOTI[3][16] = "��Ȼͤ";SPOTI[3][17] = "���п�";SPOTI[3][18] = "������";
    SPOTI[3][19] = "����";SPOTI[3][20] = "�龳��ͬ";SPOTI[3][21] = "����";
    SPOTI[3][22] = "ƽ����",SPOTI[3][23] = "�½ֿ�",SPOTI[3][24] = "��ֱ��";
    SPOTI[3][25] = "����԰",SPOTI[3][26] = "����ͼ���",SPOTI[3][27] = "κ����";
    SPOTI[3][28] = "�����ѧ";SPOTI[3][29] = "�����ׯ";SPOTI[3][30] = "�йش�";
    SPOTI[3][31] = "������ѧ����";SPOTI[3][32] = "Բ��԰";SPOTI[3][33] = "��Է";
    SPOTI[3][34] = "������";SPOTI[3][35] = "�����ű�";

    SPOTI[4][1] = "�μ�ׯ",SPOTI[4][2] = "����Ҥվ",SPOTI[4][3] = "�ѻ���վ";
    SPOTI[4][4] = "��̳����վ",SPOTI[4][5] = "������վ",SPOTI[4][6] = "������վ";
    SPOTI[4][7] = "����վ";SPOTI[4][8] = "���п�վ";SPOTI[4][9] = "����վ";
    SPOTI[4][10] = "������·վ";SPOTI[4][11] = "������վ";SPOTI[4][12] = "Ӻ�͹�վ";
    SPOTI[4][13] = "��ƽ�ﱱ��վ";SPOTI[4][14] = "��ƽ����վ";SPOTI[4][15] = "���������Ͽ�վ";
    SPOTI[4][16] = "�������ֱ���վ";SPOTI[4][17] = "����·��վ";SPOTI[4][18] = "��Է·��վ";
    SPOTI[4][19] = "��ˮ����վ";SPOTI[4][20] = "��ˮ��վ";SPOTI[4][21] = "��ͨԷ��վ";
    SPOTI[4][22] = "��ͨԷվ";SPOTI[4][23] = "��ͨԷ��վ";

    SPOTI[5][1] = "º��վ",SPOTI[5][2] = "����԰վ",SPOTI[5][3] = "�¼Ҹ�վ";
    SPOTI[5][4] = "���˺Ӷ�վ",SPOTI[5][5] = "���˺���վ",SPOTI[5][6] = "ͨ�ݱ���վ";
    SPOTI[5][7] = "����ѧԺ·վ";SPOTI[5][8] = "�ݷ�վ";SPOTI[5][9] = "��Ӫվ";
    SPOTI[5][10] = "����վ";SPOTI[5][11] = "������վ";SPOTI[5][12] = "����·վ";
    SPOTI[5][13] = "ʮ�ﱤվ";SPOTI[5][14] = "��̨·վ";SPOTI[5][15] = "����¥վ";
    SPOTI[5][16] = "������վ";SPOTI[5][17] = "������վ";SPOTI[5][18] = "����վ";
    SPOTI[5][19] = "�������վ";SPOTI[5][20] = "������վ";SPOTI[5][21] = "ƽ����վ";
    SPOTI[5][22] = "����ׯվ";SPOTI[5][23] = "����ׯ��վ";SPOTI[5][24] = "��ʯ����վ";
    SPOTI[5][25] = "��԰��վ";SPOTI[5][26] = "������վ";SPOTI[5][27] = "������·��վ";
    SPOTI[5][28] = "���վ";SPOTI[5][29] = "�ι�ׯվ";SPOTI[5][30] = "���ƴ�վ";
    SPOTI[5][31] = "��ׯվ";SPOTI[5][32] = "����վ";

    SPOTI[6][1] = "������վ",SPOTI[6][2] = "����վ",SPOTI[6][3] = "���Ӫվ";
    SPOTI[6][4] = "�㰲����վ",SPOTI[6][5] = "���п�վ",SPOTI[6][6] = "������վ";
    SPOTI[6][7] = "���п�վ";SPOTI[6][8] = "����վ";SPOTI[6][9] = "������վ";
    SPOTI[6][10] = "��������վ";SPOTI[6][11] = "��������վ";SPOTI[6][12] = "����ɽվ";
    SPOTI[6][13] = "��ͤվ";SPOTI[6][14] = "������վ";SPOTI[6][15] = "����վ";
    SPOTI[6][16] = "��¥��ׯվ";SPOTI[6][17] = "���ֹȾ���վ";SPOTI[6][18] = "��ͷվ";
    SPOTI[6][19] = "˫��վ";SPOTI[6][20] = "������վ";

    SPOTI[7][1] = "����ׯվ",SPOTI[7][2] = "��֪·վ",SPOTI[7][3] = "ƽ����վ";
    SPOTI[7][4] = "�����۶����վ",SPOTI[7][5] = "��Ӫվ",SPOTI[7][6] = "����վ";
    SPOTI[7][7] = "��С��վ";SPOTI[7][8] = "��̩ׯվ";SPOTI[7][9] = "������վ";
    SPOTI[7][10] = "ɭ�ֹ�԰����վ";SPOTI[7][11] = "����ƥ�˹�԰վ";SPOTI[7][12] = "��������վ";
    SPOTI[7][13] = "������վ";SPOTI[7][14] = "������վ";SPOTI[7][15] = "�����ﱱ��վ";
    SPOTI[7][16] = "��¥���վ";SPOTI[7][17] = "ʲɲ��վ";SPOTI[7][18] = "�������վ";
    SPOTI[7][19] = "�й�������վ";

    SPOTI[8][1] = "���п�վ",SPOTI[8][2] = "����վ",SPOTI[8][3] = "��������վ";
    SPOTI[8][4] = "ľ��԰վ",SPOTI[8][5] = "������վ",SPOTI[8][6] = "�������վ";
    SPOTI[8][7] = "����վ";SPOTI[8][8] = "���ߵ�վ";SPOTI[8][9] = "�����Դվ";
    SPOTI[8][10] = "�帣��վ";SPOTI[8][11] = "��ïվ";SPOTI[8][12] = "孺�վ";

    SPOTI[9][1] = "����ͼ���վ",SPOTI[9][2] = "��ʯ����վ",SPOTI[9][3] = "�׶���վ";
    SPOTI[9][4] = "���²����վ",SPOTI[9][5] = "������վ",SPOTI[9][6] = "�����Ŷ�վ";
    SPOTI[9][7] = "������վ";SPOTI[9][8] = "����ׯվ";SPOTI[9][9] = "��̨�����վ";
    SPOTI[9][10] = "��̨��·վ";SPOTI[9][11] = "����·վ";SPOTI[9][12] = "��̨�Ƽ�԰վ";
    SPOTI[9][13] = "����ׯվ";

    SPOTI[10][1] = "�͹�վ",SPOTI[10][2] = "���ݽ�վ",SPOTI[10][3] = "�����ׯվ";
    SPOTI[10][4] = "֪����վ",SPOTI[10][5] = "֪��·վ",SPOTI[10][6] = "������վ";
    SPOTI[10][7] = "ĵ��԰վ";SPOTI[10][8] = "������վ";SPOTI[10][9] = "������վ";
    SPOTI[10][10] = "������վ";SPOTI[10][11] = "���������Ͽ�վ";SPOTI[10][12] = "��ҩ��վ";
    SPOTI[10][13] = "̫����վ";SPOTI[10][14] = "��Ԫ��վ";SPOTI[10][15] = "������վ";
    SPOTI[10][16] = "ũҵչ����վ";SPOTI[10][17] = "�Ž��վ";SPOTI[10][18] = "����¥վ";
    SPOTI[10][19] = "��̨Ϧ��վ";SPOTI[10][20] = "��óվ";SPOTI[10][21] = "˫��վ";
    SPOTI[10][22] = "����վ";SPOTI[10][23] = "�˼�԰վ";SPOTI[10][24] = "ʮ���վ";
    SPOTI[10][25] = "������վ";SPOTI[10][26] = "������վ";SPOTI[10][27] = "�μ�ׯվ";
    SPOTI[10][28] = "ʯ��ׯվ";SPOTI[10][29] = "�����վ";SPOTI[10][30] = "���Ŷ�վ";
    SPOTI[10][31] = "������վ";SPOTI[10][32] = "����վ";SPOTI[10][33] = "�ͼ���վ";
    SPOTI[10][34] = "�׾�óվ";SPOTI[10][35] = "��̨վ";SPOTI[10][36] = "����վ";
    SPOTI[10][37] = "����վ";SPOTI[10][38] = "������վ";SPOTI[10][39] = "������վ";
    SPOTI[10][40] = "������վ";SPOTI[10][41] = "������̨վ";SPOTI[10][42] = "������վ";
    SPOTI[10][43] = "������վ";SPOTI[10][44] = "������վ";SPOTI[10][45] = "����Ӫվ";

    SPOTI[11][1] = "��ֱ��վ",SPOTI[11][2] = "������վ",SPOTI[11][3] = "֪��·վ";
    SPOTI[11][4] = "�����վ",SPOTI[11][5] = "�ϵ�վ",SPOTI[11][6] = "������վ";
    SPOTI[11][7] = "����վ";SPOTI[11][8] = "������վ";SPOTI[11][9] = "��Ӫվ";
    SPOTI[11][10] = "��ˮ��վ";SPOTI[11][11] = "��Էվ";SPOTI[11][12] = "������վ";
    SPOTI[11][13] = "��ҩ��վ";SPOTI[11][14] = "������վ";SPOTI[11][15] = "����վ";
    SPOTI[11][16] = "��ֱ��վ";

    SPOTI[12][1] = "�Ź�ׯվ",SPOTI[12][2] = "԰��԰վ",SPOTI[12][3] = "����Ҥվ";
    SPOTI[12][4] = "��ׯ��վ",SPOTI[12][5] = "��վ",SPOTI[12][6] = "����ׯվ";
    SPOTI[12][7] = "����վ";

    SPOTI[13][1] = "������վ",SPOTI[13][2] = "��Ȼ��վ",SPOTI[13][3] = "��������վ";
    SPOTI[13][4] = "��̩վ",SPOTI[13][5] = "�ѻ���վ",SPOTI[13][6] = "��ׯվ";
    SPOTI[13][7] = "ʮ���վ";SPOTI[13][8] = "����������վ";SPOTI[13][9] = "����ɽվ";
    SPOTI[13][10] = "����·վ";SPOTI[13][11] = "��̨·վ";SPOTI[13][12] = "������԰վ";
    SPOTI[13][13] = "��Ӫվ";SPOTI[13][14] = "���籱��վ";SPOTI[13][15] = "��̨վ";
    SPOTI[13][16] = "������վ";SPOTI[13][17] = "��ͨվ";SPOTI[13][18] = "����վ";
    SPOTI[13][19] = "������վ";SPOTI[13][20] = "����Ӫվ";SPOTI[13][21] = "�Ƹ�ׯվ";

    SPOTI[14][1] = "�廪��·����վ",SPOTI[14][2] = "������վ",SPOTI[14][3] = "��ɳ̲վ";
    SPOTI[14][4] = "����ƥ�˹�԰վ",SPOTI[14][5] = "����·վ",SPOTI[14][6] = "����·��վ";
    SPOTI[14][7] = "��ׯվ";SPOTI[14][8] = "������վ";SPOTI[14][9] = "����վ";
    SPOTI[14][10] = "������վ";SPOTI[14][11] = "�޸�ׯվ";SPOTI[14][12] = "��ȪӪվ";
    SPOTI[14][13] = "���վ";SPOTI[14][14] = "��չվ";SPOTI[14][15] = "���濲վ";
    SPOTI[14][16] = "��ɳ��վ";SPOTI[14][17] = "�Ϸ���վ";SPOTI[14][18] = "ʯ��վ";
    SPOTI[14][19] = "˳��վ";SPOTI[14][20] = "ٺ��վ";

    SPOTI[15][1] = "������վ",SPOTI[15][2] = "����·վ",SPOTI[15][3] = "�����·վ";
    SPOTI[15][4] = "�͵�վ",SPOTI[15][5] = "����վ",SPOTI[15][6] = "������վ";
    SPOTI[15][7] = "������վ";SPOTI[15][8] = "������վ";SPOTI[15][9] = "ũ����·վ";
    SPOTI[15][10] = "��Էվ";

    SPOTI[16][1] = "�Ļ�վ",SPOTI[16][2] = "�Ļݶ�վ",SPOTI[16][3] = "�߱���վ";
    SPOTI[16][4] = "��ý��ѧվ",SPOTI[16][5] = "˫��վ",SPOTI[16][6] = "��ׯվ";
    SPOTI[16][7] = "������վ";SPOTI[16][8] = "ͨ�ݱ�Էվ";SPOTI[16][9] = "��԰վ";
    SPOTI[16][10] = "�ſ���վ";SPOTI[16][11] = "��԰վ";SPOTI[16][12] = "�ٺ���վ";
    SPOTI[16][13] = "����վ";

    SPOTI[17][1] = "��ƽ��ɽ��վ",SPOTI[17][2] = "ʮ���꾰��վ",SPOTI[17][3] = "��ƽվ";
    SPOTI[17][4] = "��ƽ����վ",SPOTI[17][5] = "������վ",SPOTI[17][6] = "����վ";
    SPOTI[17][7] = "ɳ�Ӹ߽�԰վ";SPOTI[17][8] = "ɳ��վ";SPOTI[17][9] = "������վ";
    SPOTI[17][10] = "����ׯվ";SPOTI[17][11] = "������ѧ԰վ";SPOTI[17][12] = "������վ";

    SPOTI[18][1] = "�μ�ׯվ",SPOTI[18][2] = "Ф��վ",SPOTI[18][3] = "С����վ";
    SPOTI[18][4] = "�ɹ�վ",SPOTI[18][5] = "��ׯ��վ",SPOTI[18][6] = "��ׯ�Ļ�԰վ";
    SPOTI[18][7] = "��Դ��վ";SPOTI[18][8] = "�پ�����վ";SPOTI[18][9] = "�ٲ�����վ";
    SPOTI[18][10] = "ͬ����·վ";SPOTI[18][11] = "����·վ";SPOTI[18][12] = "������վ";
    SPOTI[18][13] = "����վ";SPOTI[18][14] = "��ׯ��վ";

    SPOTI[19][1] = "����ׯվ",SPOTI[19][2] = "����̨վ",SPOTI[19][3] = "����վ";
    SPOTI[19][4] = "����վ",SPOTI[19][5] = "��ʷ�վ",SPOTI[19][6] = "������վ";
    SPOTI[19][7] = "�����ѧ�Ǳ�վ";SPOTI[19][8] = "�����ѧ��վ";SPOTI[19][9] = "�����ѧ����վ";
    SPOTI[19][10] = "�����Ϲ�վ";SPOTI[19][11] = "��ׯվ";SPOTI[19][12] = "�ִ嶫վ";

    SPOTI[20][1] = "��ֱ��վ",SPOTI[20][2] = "��Ԫ��վ",SPOTI[20][3] = "��վ¥վ";


    //��ʼ��EXCHANGE
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


    //��ʼ��ͼ
    for (int i = 1 ; i <= MAXN ; i ++)  //Init
        for (int j = 1 ; j <= MAXN ; j ++)
            G[i][j] = INF;              //��ͨ������·
    for (int i = 1 ; i <= 20 ; i ++)
        for (int j = 1 ; j < CNT[i] ; j ++) {
            G[Pre[i]+j][Pre[i]+j+1] = 1;
            G[Pre[i]+j+1][Pre[i]+j] = 1;
        }
                                       //��������
    G[Pre[2]+1][Pre[2]+CNT[2]] = 1;
    G[Pre[2]+CNT[2]][Pre[2]+1] = 1;
    G[Pre[10]+1][Pre[10]+CNT[10]] = 1;
    G[Pre[10]+CNT[10]][Pre[10]+1] = 1;
                                       //��������
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

    // ��ʼ�����
}


// ������
int main()
{
    INIT();

    while (1) {
//        memset(ANS,0,sizeof(ANS));
        MAJOR();
    }

    return 0;
}


// ���溯��
void SPOT(int s,int q)
{
    string temp;
    int w = -1;

    if (s == 1)
        temp = "���";
    else
        temp = "�յ�";

    cout << "\n *** ��ǰ����Ϊ" << temp << "վ��ѡ����� ***\n";
    printf("����0�����ϲ����\n");
    cout << "������±���������" << temp << "վ��\n";
    SPOTCHART(q);


    while (w < 0 || w > CNT[q]) {
        scanf("%d",&w);
        if (w < 0 || w > CNT[q])
            printf("��Чվ�����!\n");
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
        temp = "���";
    else
        temp = "�յ�";

    cout << "\n *** ��ǰ����Ϊ" << temp << "·��ѡ����� ***\n";
    printf("����0�����ϲ����\n");
    cout << "������±���������" << temp << "·��\n";
    ROUTECHART();

    while (q < 0 || q > 20) {
        scanf("%d",&q);
        if (q < 0 || q > 20)
            printf("��Ч·�߲���!\n");
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
    printf("\n��ǰ����Ϊ������\n");
    printf("����-1�˳���ϵͳ������999�鿴������·��Ϣ������0��ʼ��ѯ������1�趨��㣬����2�趨�յ�\n");
    cout << "��ǰ��㣺 ";
    if (st&&strt)
        cout << SPOTI[strt][stt] << '\n';
    else
        cout << "��\n";
    cout << "��ǰ�յ㣺 ";
    if (en&&enrt)
        cout << SPOTI[enrt][enn] << '\n';
    else
        cout << "��\n";

    scanf("%d",&op);
    if (op == -1)
        exit(0);
    else if (op == 999) {
        cout << "\n*** ������·ͼ ***\n";
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
            printf("�����趨�����յ�");
        else
            CAL();
    } else if (op==1 || op==2)
        ROUTE(op);
    else
        printf("��Ч������!\n");
}