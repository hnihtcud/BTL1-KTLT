#include "water_seven.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
bool readInput(
    const string &filename,
    char character[FIXED_CHARACTER][MAX_NAME],
    int hp[FIXED_CHARACTER],
    int skill[FIXED_CHARACTER],
    int &shipHP,
    int &repairCost){
    ifstream fin(filename);
    string name;
    int cnt=0, luu;
    double h, s;
    if(!fin.is_open()) return false;
    while(fin>>name>>h>>s){
        if(h - (long long)h > 1e-9) return false;
        if(s - (long long)s > 1e-9) return false;
        if (name != "LUFFY" && name != "ZORO" && name != "SANJI" && 
            name != "NAMI" && name != "CHOPPER" && name != "USOPP" && 
            name != "ROBIN" && name != "GOING_MERRY") 
                continue;
        bool check=true;
        if(name=="GOING_MERRY"){
            if(h<0) h=0;
            if(h>1000) h=1000;
            if(s<0) s=0;
            if(s>3000) s=3000;
            shipHP=h;
            repairCost=s;
        }
    else{
        if(h<0) h=0;
        if(h>1000) h=1000;
        if(s<0) s=0;
        if(s>100) s=100;
        for(int i=0; i<cnt; i++)
            if(strcmp(character[i], name.c_str())==0){
                check=false;
                luu=i;
                break;
            }
        if(!check){
            hp[luu]=h;
            skill[luu]=s;
        }
        else{
            
            strcpy(character[cnt], name.c_str());
            hp[cnt]=h;
            skill[cnt]=s;
            cnt++;
        }
    }
}
    return true;
}

int damageEvaluation(int shipHP, int repairCost) {
    int n=0, chk=0, t=shipHP;
    while(t>0){
        n+=t%10;
        t/=10;
    }
    for(int i=1; i<n; i++)
        if(n%i==0){
            chk+=i;
        }
    if(chk==n && shipHP<455 && shipHP!=0){
        double res=1.5*repairCost;
        if(res>3000)
            return 3000;
        return ceil(res);
    }
    return repairCost;
}

int conflictSimulation(
    char character[FIXED_CHARACTER][MAX_NAME], int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER],
    int shipHP, int repairCost){
    int sl, su, cI, id, cnt=0;
    for(int i=0; i<FIXED_CHARACTER; i++){
        if(strcmp(character[i],"LUFFY")==0)
            sl=skill[i];
        if(strcmp(character[i],"USOPP")==0)
            su=skill[i];
    }
    cI = sl - su ;
    double t1 = (float)repairCost/100.0;
    double t2 = (float)(500.0-shipHP)/50.0;
    cI +=ceil(t1+t2);
    while(cI < 255 && cnt<10){
        id = cI % 6;
        if(id==0){
            cI+=255;
            return cI;
        }
        if(id==1){
            cnt++;
            cI+=20;
        }
        if(id==2){
            cnt++;
            cI+=50;
        }
        if(id==3){
            cnt++;
            cI+=70;
        }
        if(id==4){
            cnt++;
            cI+=90;
        }
        if(id==5){
            cnt++;
            cI+=100;
        }
    }
    return cI;
}

int arr[10];
int Sub[10];
int skillSupport[40], costSupport[40], mincost=1e9, maxS=0, mincount=6, target, location[10], minskill=1e9;
void check(int len, int cost, int count, int skill1){
    if(len==0) return;
    for(int i=0; i<len; i++){
        cost+=costSupport[Sub[i]];
        skill1+=skillSupport[Sub[i]];
        count++;
    }
    if(skill1<target) return;
    if(cost<mincost || (cost==mincost && count<=mincount)) {
        if(cost==mincost && count==mincount){
            for(int i=0; i<len; i++)
                if(Sub[i]>location[i]) return;
        }
        mincost=cost;
        mincount=count;
        for(int i=0; i<len; i++) location[i]=Sub[i];
        for(int i=0; i<len; i++)
            for(int j=i+1; j<len; j++)
                if(location[i]>location[j]){
                    int temp=location[i];
                    location[i]=location[j];
                    location[j]=temp;
                }
    }
}
void subset(int t, int len, int cnt){
    if(t==cnt){
        check(len, 0, 0, 0);
        return;
    }
    subset(t+1, len, cnt);
    Sub[len] = arr[t];
    subset(t+1, len+1, cnt);
}
void resolveDuel(
    char character[FIXED_CHARACTER][MAX_NAME],
    int hp[FIXED_CHARACTER],
    int skill[FIXED_CHARACTER],
    int conflictIndex,
    int repairCost,
    char duel[FIXED_CHARACTER][MAX_NAME])
{
    for(int i=0; i<FIXED_CHARACTER; i++)
        strcpy(duel[i], "\0");
    memset(arr, 0, sizeof(arr));
    memset(Sub, 0, sizeof(Sub));
    mincost=1e9; maxS=0; mincount=6; minskill=1e9;
    int su, sl, cnt=0;
    char supportName[20][MAX_NAME];
    for(int i = 0; i < FIXED_CHARACTER; i++) {
        if(strcmp(character[i], "LUFFY") == 0) {
            sl=skill[i];
        }
        if(strcmp(character[i], "USOPP") == 0) {
            su=skill[i] ;
            su+=ceil((double)conflictIndex / 20.0 + (double)repairCost / 500.0);
        }
    }
    target = su-sl;
    if(target<=0) return;
    for(int i =0; i<FIXED_CHARACTER; i++)
        if(strcmp(character[i], "LUFFY") != 0 && strcmp(character[i], "USOPP") != 0) {
            strcpy(supportName[cnt], character[i]);
            skillSupport[cnt] = skill[i];
            costSupport[cnt] = hp[i] % 10 + 1;
            cnt++;
        }
    for(int i=0; i<cnt; i++)
        arr[i]=i;
    int Number=0;
    subset(0, 0, cnt);
    if(mincost!=1e9)
        for(int i=0; i<mincount; i++){
            strcpy(duel[Number], supportName[location[i]]);
            Number++;
        }
}

#include <cctype>
#include <cstring>
bool check(char cipherText[])
{
    int chk=0, chk1=0;
    if(strlen(cipherText)<3) return false;
    for(int i = 0; i < (int)strlen(cipherText)-3; i++)
        chk+=(int)cipherText[i];
    chk%=100;
    chk1+=cipherText[(int)strlen(cipherText)-2]-'0';
    chk1*=10;
    chk1+=cipherText[(int)strlen(cipherText)-1]-'0';
    return (chk==chk1);
}
void decodeCP9Message(char character[FIXED_CHARACTER][MAX_NAME], 
    int hp[FIXED_CHARACTER], int skill[FIXED_CHARACTER], int conflictIndex, 
    int repairCost, char cipherText[], char resultText[])
{
    char cipherText1[1000], resultText1[1000];
    //resultText[0] = '\0';
    bool flag=false;
    int key, b, j=0;
    key = (conflictIndex + repairCost) % 26;
    b = key % 5 + 4;
    if(!check(cipherText)){
        strcpy(resultText, "");
        return;
    }
    int h=0,t;
    int len=strlen(cipherText)-3;
    for(int i=0; i<len; i+=b){
        if(i+b<len) 
            t=i+b-1;
        else t=len-1;
        for(int j=t; j>=i; j--)
            cipherText1[h++]=cipherText[j];
    }
    cipherText1[h]='\0';
    int l=strlen(cipherText1);
    for(int i=0; i<l; i++){
        if(cipherText1[i]>='A' && cipherText1[i]<='Z'){
            resultText[i] = (cipherText1[i]-'A'-key+26)%26 + 'A';
        }
        else if(cipherText1[i]>='a' && cipherText1[i]<='z'){
            resultText[i] = (cipherText1[i]-'a'-key+26)%26 + 'a';
        }
        else if(cipherText1[i]>='0' && cipherText1[i]<='9'){
            resultText[i] = (cipherText1[i]-'0'-(key%10)+10)%10 + '0';
        }
        else{
            resultText[i] = cipherText1[i];
        }
    }
    resultText[l] = '\0';
    if (strstr(resultText, "CP9") != NULL || strstr(resultText, "ENIESLOBBY") != NULL){
            flag=true;
        }
    if(flag){
        strcat(resultText, "_TRUE");
    }
    else{
        strcat(resultText, "_FALSE");
    }
}
#define MAX 1e9


int analyzeDangerLimit(int grid[MAX_GRID][MAX_GRID], int rows, int cols)
{
    int maxrowsum=-1, maxcell=-1, temp;
    for(int i=0; i<rows; i++){
        temp=0;
        for(int j=0; j<cols; j++){
            if(grid[i][j]>maxcell) maxcell=grid[i][j];
            if(grid[i][j]>-1)
                temp+=grid[i][j];
        }
        if(temp>maxrowsum) maxrowsum=temp;
    }
    return (maxrowsum+maxcell);
}

bool evaluateRoute(int grid[MAX_GRID][MAX_GRID], int rows, int cols, int dangerLimit)
{
    if(grid[0][0]==-1 || grid[0][0]>dangerLimit) return false;
    int dp[1000][1000];
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            dp[i][j]=MAX;
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++){
            int T=MAX, L=MAX;
            if(i==0 && j==0) dp[0][0]=grid[0][0];
            else{
            if(grid[i][j]!=-1){
                if(i>0) T=dp[i-1][j];
                if(j>0) L=dp[i][j-1];
                dp[i][j]=grid[i][j]+min(T, L);
            }
        }
    }
    if(dp[rows-1][cols-1]<=dangerLimit)
        return true;
    return false;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////