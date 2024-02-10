#include <iostream>

using namespace std;

void playerData(char* id, int* player){
    cin>>*id;
    int x;
    for (int i=0;i<4;i++){
        cin>>x;
        player[x-1]++;
        //cout << "tablica gracza: "<<player[x-1] << endl;
    }
}

void clearPlayers(int* a,int* b){
    for (int i=0;i<4;i++){
        a[i]=0;
        b[i]=0;
    }
}

void determineWin(int* player, int* win){
    if(player[0] == 1 && player[1] == 1 && player[2] == 1 && player[3] == 1)
    {
        win[0]=2;
        win[1]=0;
    }
    else if(player[3] == 2 && (player[2] == 2 || player[1] == 2 || player[0] == 2)){
        win[0]=3;
        win[1]=4;
    }else if(player[2] == 2 && (player[1] == 2 || player[0] == 2))
    {
        win[0]=3;
        win[1]=3;
    }else if(player[1] == 2 && player[0] == 2)
    {
        win[0]=3;
        win[1]=2;
    }
    else
        win[0]=6;

    win[2] = player[0] + player[1]*2 + player[2]*3 + player[3]*4;

    for (int i=3;i>=0;i--){
        if(1 < win[0] && player[i]==4){
            win[0] = 1;
            win[1] = i+1;
        }else if(4 < win[0] && player[i]==3){
            win[0] = 4;
            win[1] = i+1;
        }else if(5 < win[0] && player[i] == 2)
        {
            win[0] = 5;
            win[1] = i+1;
        }
    }
}

int chooseWinner(int* a,int* b){
    if (a[0] < b[0])
        return 1;
    if (b[0] < a[0])
        return -1;

    if (a[1] > b[1])
        return 1;
    else if (a[1] < b[1])
        return -1;
    else if (a[2] > b[2])
        return 1;
    else if (a[2] <b[2])
        return -1;

    return 0;
}

int stats[26][3];

int main()
{
    int n=0;
    char A,B;
    int playerA[4]={0},playerB[4]={0};
    int winA[3]={0},winB[3]={0},win;

    cin>>n;

    for (int i=0;i<n;i++){
        playerData(&A,playerA);
        playerData(&B,playerB);
        determineWin(playerA, winA);
        determineWin(playerB, winB);

        win = chooseWinner(winA,winB);
        if (win == 1){
            stats['z'-A*1][0]++;
            stats['z'-B*1][2]++;
        }else if(win == 0){
            stats['z'-A*1][1]++;
            stats['z'-B*1][1]++;
        }else{
            stats['z'-A*1][2]++;
            stats['z'-B*1][0]++;
        }
        clearPlayers(playerA,playerB);
    }
    double w,r,l;
    double suma;
    char znak;

    for (int i=25;i>=0;i--)
    {
        znak = 1*'z'-i;
        w = stats[i][0];
        r = stats[i][1];
        l = stats[i][2];
        suma = w+r+l;
        if (suma)
        {
            cout<<"gracz "<<znak<< "\n";
            if (w)
                cout<<"    wygrane: "<<w/suma*100<<"%" << "\n";
            if (r)
                cout<<"    remisy: "<<r/suma*100<<"%" << "\n";
            if (l)
                cout<<"    przegrane: "<<l/suma*100<<"%" << "\n";

            cout << "\n";
        }
    }
    return 0;
}