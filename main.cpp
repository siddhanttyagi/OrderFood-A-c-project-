#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<cwchar>
using namespace std;

class dish{
    public:
    string dname;
    int dprice;
    int dtime;
    string dno;
    dish()
    {
        dno=" ";
    }
};
class cuisine{
    string cname;
    dish *d[7];
};

class hotel{
    string hname;
    string location;
    cuisine *c[5];
};

class user{
    string pin;
    string userId;
    string fname;
    string lname;
    string location;
    string code;           //LX
    public:
    void userLogin();
    void createNewUser();
};
string cno;
struct Gnode{
    struct Gnode *next;
    string cd;
    int d;
};
int countRL(){
    ifstream fin;
    fin.open("area_map.txt");
    if(!fin)
        cout<<"area_map.txt not opened";
    int l=0;            //total land marks
    string lin;         //to store each line for counting purpose
    while(fin){
        l++;
        getline(fin,lin);
    }
    l=l-1;
       //as file handling counts last line twice so we do -1
    fin.close();
    return l;
}

Gnode * createGraph(){
    int l=countRL();
    struct Gnode * G=new struct Gnode[l];
    ifstream fin;
    fin.open("area_map.txt");
    int c=0,nt=0;
    string st;
    int n;
    struct Gnode * k;
    while(c!=l){
        fin>>st;
        k = &G[c];
        G[c].cd=st;
        G[c].d=nt;
        nt++;
        G[c].next=0;
        while(fin){
            fin>>st;
            if(st!="e"){
                struct Gnode *t=new struct Gnode;
                t->next=0;
                t->cd=st;
                fin>>n;
                t->d=n;
                k->next=t;
                k=t;
            }
            else
                break;
        }
        c+=1;
    }
    //for(int j=0;j<l;j++)
      //  cout<<G[j].cd<<" ";
    return G;
}
int minDistance(int dist[], int sptSet[],int V)
{
   // Initialize min value
   int min = INT_MAX,min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == 0 && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}
void printRestaurants(int *dist,string d[],int rnum)
{
    struct Gnode *G = createGraph();
    int l= countRL();

    struct Gnode * tmp;
    int rt;
    string rst,ct;
    float n1,n2;
   cout<<"Restaurant\t\t\tdistance\t\tRating(for "<<cno<<")\n";
   for (int i = 0; i < rnum; i++){
        tmp=G;
        for(int j=0;j<l;j++){
        if(tmp[j].cd==d[i]){
            rt=tmp[j].d;
            break;
        }
    }
    cout<<"\t"<<d[i]<<"\t\t\t\t"<<dist[rt]<<"\t\t";
    ifstream fin;
    fin.open("feedbackAll.txt");
    while(fin>>rst){
      fin>>ct>>n1>>n2;
      if(rst==d[i] && ct==cno){
        cout<<n1/n2<<endl;
      }
    }
    cout<<endl;
    fin.close();
   }
}
int *dijkstra(string s)
{
    struct Gnode * G= createGraph();
    int l=countRL();
    //displaying the Graph
    /*struct Gnode * gs1;
    for(int i=0;i<l;i++){
      gs1=G+i;
      while(gs1){
        cout<<gs1->cd<<" "<<gs1->d<<" ";
        gs1=(gs1->next);

      }
      cout<<endl;
    }*/
    //--------------------
    int src;
    struct Gnode * tmp=G;
    for(int i=0;i<l;i++){
    if(tmp[i].cd==s){
        src=tmp[i].d;
        break;
        }
    }
    int * dist=new int[l];
    int * sptSet=new int[l];
    for(int i=0;i<l;i++){
        dist[i]=INT_MAX;
        sptSet[i]=0;
        }

    dist[src]=0;
    int countVis=0;
    string land;
    int landnum,dland;
     while(countVis<l) {
        int u = minDistance(dist, sptSet,l);
        sptSet[u] = 1;
        countVis++;
       // Update dist value of the adjacent vertices of the picked vertex.
       tmp=G+u;
       tmp=tmp->next;
       while(tmp)
       {
        dland=tmp->d;
        land=tmp->cd;
        if(land[0]=='R')
       {
          landnum=(int)land[1]-48+15;
       }
        else if(land[0]=='L')
        {
          if(land.length()==2)
        {
          landnum=(int)land[1]-48;
        }
        else
        {
            landnum=(((int)land[1]-48)*10)+(int)land[2]-48;
        }
        }
        if(sptSet[landnum]==0){
          dist[landnum]=min(dist[landnum],dland+dist[u]);
        }
        tmp=tmp->next;
     }
     }

     return dist;
     // print the constructed distance array
     //printRestaurants(dist,l,G,d,rnum);
}

void menu(string loc,string uid,int cuisineTake,string cuisineNo){
    string a;
    dish D;
    dish d1;
    int sugg=0,avg;
    if(cuisineTake==0){
    cout<<"\n\n\t\t\t\t\t\t\t=====EXPLORE YOUR FAVOURITE CUISINES====="<<endl;
    cout<<"\n\n\n\t===========================\t\t\t==========================\t\t\t\t==========================="<<endl;
    cout<<"\n[1] NORTH INDIAN\n[2] MUGHLAI\n[3] CHINESE\n[4] CONTINENTAL\n[5] SOUTH INDIAN\n[6] HYDERABADI\n[7] THAI\n[8] ITALIAN\n===========================\t\t\t==============================\t\t\t\t===========================\n\n\n\t\t\t\t\t\t\t\t[9] EXIT"<<endl;
    cout<<"\n\t======================================================================================================================================="<<endl;
    cout<<"Enter cuisine number:";
    cin>>a;
    if(a=="9"){
      return;
    }
  }
  else{
    a=cuisineNo;
    sugg=1;
    avg=cuisineTake;
    cout<<"\nAll these Restaurants have your preferences\n\n";
  }
    cno="C"+a;
    system("clear");

    ifstream fin;
    fin.open("Rcuisines.txt");
    if(!fin)
        cout<<"Not found Rcuisines"<<endl;
    string Rt,num="0";
    string Rarr[6];
    int rnum=0;
    fin>>Rt;
    while(fin){
        while(num[0]!='R' && fin){
            fin>>num;
            if(num==a){
                //cout<<Rt<<" ";
                Rarr[rnum++]=Rt;
            }
        }
        Rt=num;
        num="0";
    }
    fin.close();
    int *distpointer = dijkstra(loc);
    printRestaurants(distpointer, Rarr, rnum);

    //--------------------------------
    ifstream fiin;
    string sa,c="C"+a,rloc;
    cout<<"Enter restaurant of your choice:   ";
    cin>>sa;
    rloc=sa;
    system("clear");
    sa=sa+".txt";
    string sb=sa;
    fiin.open(sa);
    if(!fiin)
        cout<<"not open";
    while(fiin){
        fiin>>sa;
        if(sa==c){
            cout<<"\t\t\t\t\tORDER-ORDER\n\n\n";
            while(D.dno[0]!='C'){
                fiin>>D.dno>>D.dname>>D.dprice>>D.dtime;
                if(D.dno[0]!='C'){
                if(sugg==0)
                cout<<D.dno<<" "<<D.dname<<" "<<D.dprice<<" "<<D.dtime<<endl;
                else{
                  if(D.dprice>=avg-50 && D.dprice<=avg+50){
                    cout<<D.dno<<" "<<D.dname<<" "<<D.dprice<<" "<<D.dtime<<endl;
                  }
                }
              }
            }
            break;
        }
    }
    fiin.close();
    int qty;
    char ch='Y';
    string d;
    dish ordered;
    int bill=0;
    int ocount=0;
    string odish[5];
    int oqty[5];
    while((ch=='Y'||ch=='y')&& ocount<=5){
        ocount++;
        cout<<"Enter dish number you want to order:\t"<<endl;
        cin>>d;
        cout<<"Enter quantity:\t"<<endl;
        cin>>qty;
        fiin.open(sb);
     while(fiin){
        fiin>>sa;
        if(sa==c){
            D.dno="X";
            while(D.dno[0]!='C'){
                fiin>>D.dno>>D.dname>>D.dprice>>D.dtime;
                if(D.dno[0]!='C'){
                if(D.dno==d){
                    ordered.dno=D.dno;
                    ordered.dname=D.dname;
                    odish[ocount-1]=D.dname;
                    oqty[ocount-1]=qty;
                    ordered.dprice=D.dprice*qty;
                    cout<<"\nDish Price: "<<ordered.dprice<<" ";
                    ordered.dtime=D.dtime;
                }
                }
            }
            break;
        }
    }
    fiin.close();
    bill+=ordered.dprice;

       cout<<"\n\nWants to order more?[y/n]";
       cin>>ch;
       cout<<endl;
    }

    cout<<"------------BILL-------------\n";
    cout<<"ordered dishes\t\tquantity\n";
    for(int dco=0;dco<ocount;dco++)
        cout<<"\n\n"<<odish[dco]<<"\t\t\t"<<oqty[dco];
    cout<<"\nTotal bill: "<<bill<<endl;
    //------writing order in user file for future suggestions---------------
    ifstream feedin;
    fstream feedout;
    feedin.open("userHistory.txt");
    feedout.open("tempHistory.txt",ios::out);
    if(!feedin)
      cout<<"userHistory file not opened\n";
    if(!feedout)
      cout<<"tempHistory file not opened\n";
    string uidd,cnam;
    int ccno=8;
    int cprice,ff;
    int ccount;
    int tdsum=0;
    for(int dco=0;dco<ocount;dco++)
        tdsum+=oqty[dco];
    while(feedin>>uidd){
      feedout<<"\n"<<uidd<<" ";
      for(int i=1;i<=ccno;i++){
        feedin>>cnam>>cprice>>ccount;
        //ff=((int)cnam[1])-48;
        if(uidd==uid && cno==cnam){
          cprice+=bill;
          ccount+=tdsum;
      }
        feedout<<cnam<<" "<<cprice<<" "<<ccount<<" ";
    }
    }
    feedin.close();
    feedout.close();
    remove("userHistory.txt");
    rename("tempHistory.txt","userHistory.txt");

    //-------------writing all order in one file for future rating purpose-----------------
    fstream foout;
    foout.open("ordered.txt", ios::out | ios::app);
    if(!foout){
    cout<<"ordered.txt not opened";
    }
    foout<<"\n"<<uid<<" "<<rloc<<" "<<cno<<" "<<bill<<" "<<ocount<<" ";
    for(int dco=0;dco<ocount;dco++)
        foout<<odish[dco]<<" "<<oqty[dco]<<" ";
    foout.close();
    //-------------writing order in specific restaurant file to apply stenner algo-----------------
    string x1=rloc+"orders.txt";
    foout.open(x1, ios::out | ios::app);
    if(!foout){
    cout<<rloc<<"orders.txt not opened\n";
    }
    foout<<"\n"<<loc<<" "<<" "<<uid<<" "<<ocount<<" ";
    for(int dco=0;dco<ocount;dco++)
        foout<<odish[dco]<<" "<<oqty[dco]<<" ";
    foout<<bill;
    foout.close();
}

void feedback(string uid){
  ifstream fin;
  fstream fout;
  fin.open("ordered.txt");
  fout.open("tempord.txt",ios::out);
  if(!fin)
    cout<<"ordered.txt file not found for FEEDBACK\n";
  if(!fout){
    cout<<"tempord.txt not opened for FEEDBACK\n";
    }
  string id;
  int tbill,tdish,dqty[10];
  string rloc,cusi,dname[10];
  while (fin>>id) {
      float fd;
      fin>>rloc>>cusi>>tbill>>tdish;
      for(int i=0;i<tdish;i++){
        fin>>dname[i]>>dqty[i];
      }
      if(id==uid){
      cout<<"\n\t\t ******** Time For Some FEEDBACK ********\n\n";
      cout<<"Rate your previous dishes out of 5: \n";
      cout<<"Restaurant :"<<rloc;
      cout<<"\n\tYou ordered "<<tdish<<"dishes :\n";
      for(int i=0;i<tdish;i++){
        cout<<dname[i]<<"\t"<<dqty[i]<<endl;
      }
      cout<<"You Paid:  "<<tbill<<endl;
      cout<<"Enter your rating [out of 5]: ";
      cin>>fd;
      ifstream feedin;
      fstream feedout;
      feedin.open("feedbackAll.txt");
      feedout.open("tempfeedback.txt",ios::out);
      if(!feedin)
        cout<<"feedbackAll file not opened\n";
      if(!feedout)
        cout<<"tempfeedback file not opened\n";
      string rname,cname;
      int peoplect;
      float rating;
      while(feedin>>rname){
        feedin>>cname>>rating>>peoplect;
        if(rloc==rname && cname==cusi){
          peoplect+=1;
          rating+=fd;
        }
        feedout<<"\n"<<rname<<" "<<cname<<" "<<rating<<" "<<peoplect;
      }
      feedin.close();
      feedout.close();
      remove("feedbackAll.txt");
      rename("tempfeedback.txt","feedbackAll.txt");
      }
      else{
        fout<<"\n"<<id<<" "<<rloc<<" "<<cusi<<" "<<tbill<<" "<<tdish<<" ";
        for(int i=0;i<tdish;i++){
          fout<<dname[i]<<" "<<dqty[i]<<" ";
        }
      }
  }
fout.close();
fin.close();
remove("ordered.txt");
rename("tempord.txt","ordered.txt");
}

string suggestion(string userId,int & avg)
{
  system("clear");
  //to give suggestions
  ifstream fin;
  fin.open("userHistory.txt");
  if(!fin)
    cout<<"userHistory.txt file not found for FEEDBACK\n";
  string id,c,mxc="C1";
  int cpeople,cmrp,mx=0;
  avg=0;
  char sug;
  while(fin>>id)
  {
    if(id==userId)
    {
      for(int i=0;i<8;i++){
        fin>>c>>cmrp>>cpeople;
        if(cpeople>mx){
          mx=cpeople;
          mxc=c;
          avg=(cmrp)/cpeople;
        }
      }
    }
    else{
        for(int i=0;i<8;i++){
          fin>>c>>cmrp>>cpeople;
        }
    }
  }
  fin.close();
  if(avg==0)
  {
    cout<<"YOU HAVE NOT ORDERED ANYTHING YET! NO SUGGESTIONS FOR YOU";
    cout<<"\n\n\t\tPress enter to continue";
    string tmp;
    getline(cin,tmp);
    getline(cin,tmp);
    return "x";
  }
  else
  {
    cout<<"\n\n\n\n\n\t****  SUGGESTIONS FOR YOU  ****\n\n\n"<<endl;
    cout<<"According to your past food orders,we think you will love these cuisines"<<endl;
    cout<<"YOU WANT TO GO WITH THE SUGGESTION(y/n)"<<endl;
    cin>>sug;
    if(sug=='n')
    {
      return "x";
    }
    else if(sug=='y')
    {
      string aa;
      aa=mxc[1];
      //menu(cd,userId,1,aa);
      return aa;
  }
}
}

void user::userLogin(){
    system("clear");
    cout<<"\t\t\t\t If new user enter id=0 and pass=0"<<endl;
    cout<<"Enter ID:";
    cin>>userId;
    cout<<"Enter pin:";
    cin>>pin;
    if(pin=="0" && userId=="0"){
        createNewUser();
        }
    else{
        ifstream fin;
        string f,l,i,p,loc,cd;
        bool userExist=false;
        fin.open("user_detail.txt");
        if(!fin)
        cout<<"file not found";
        while (fin) {
            fin>>f>>l>>i>>p>>loc>>cd;
            if(i==userId && p==pin){
            cout<<"Welcome "<<f<<" "<<l<<endl;
            userExist=true;
            break;
            }
        }
    fin.close();

    if(!userExist){
        cout<<"Invalid Pin or UserId\n1.try again\n2.exit";
    int ch;
    cin>>ch;
    if(ch==1)
        userLogin();
    else
        exit(0);
    }
    else{
        feedback(userId);
        string sug;
        int avg;
        sug=suggestion(userId,avg);
        if(sug=="x")
          menu(cd,userId,0,"x");
        else
          menu(cd,userId,avg,sug);
        }
    }
}

string checklocation(string loc){
    ifstream flin;
    flin.open("landmarks.txt");
    string l,cd;int f=0;
    while(flin){
        flin>>l;
        if(l==loc){
            cout<<"correct location found"<<loc;
            f=1;
            flin>>cd;
            cout<<cd;
            break;}
        }
    flin.close();
    if(f==0){
        cout<<"You entered wrong location. Renter right location:";
        cin>>loc;
        cd=checklocation(loc);
        }
        return cd;
}
void user::createNewUser(){
    ofstream fout;
    fout.open("user_detail.txt",ios::app);
    cout<<endl;
    cout<<"Enter first name: ";
    cin>>fname;
    cout<<"Enter last name: ";
    cin>>lname;
    cout<<"Enter user Id: ";
    cin>>userId;
    cout<<"Enter pin: ";
    cin>>pin;
    cout<<"Enter location: ";
    cin>>location;
    code=checklocation(location);
    fout<<fname<<" "<<lname<<" "<<userId<<" "<<pin<<" "<<location<<" "<<code<<endl;
    fout.close();
    system("clear");
    //----Enter a new entry in userHistory-------------------
    fout.open("userHistory.txt",ios::app);
    fout<<endl<<userId<<" C1 0 0 C2 0 0 C3 0 0 C4 0 0 C5 0 0 C6 0 0 C7 0 0 C8 0 0 ";
    fout.close();
    cout<<"------------Id created sucessfully.Enjoy OrderMeFood!!------------";
    menu(code,userId,0,0);
}
/*
int ulocpresent(string uloc[] , string check, int index)
{
  for(int i=0;i<index;i++)
  {
  if(uloc[i]==check)
  return 0;
}
return 1;
}`












*/
int present(string uloc[], int ind, int uindex)
{

  for(int i=0;i<uindex;i++)
  {
    string curr=uloc[i];
    int indexcheck=0;
    if(int(curr[0])==76)
    {
      if(curr.length()==3)
      {
        indexcheck=((curr[1]-48)*10)+(curr[2]-48);
      }
      else
      {
        indexcheck=curr[1]-48;
      }
    }
    else
    {
      indexcheck=curr[1]-48+15;
    }
    if(indexcheck-1==ind)
    {
      return 0;
    }
  }
  return 1;
}
void steiner(string uloc[], int index)
{
  int i=0;
  int sendindex=0;
  while(i<3)
  {
  if(i==0)
  {
    int sendindex=index;
  }
  int *distptrstner = dijkstra(uloc[sendindex]);
  int l=countRL();
  int rmin=INT_MAX;
  string rminind;
  for(int i=0;i<l;i++)
  {
    if(distptrstner[i]<rmin && present(uloc,i,index)==0)
    {
      rmin=distptrstner[i];
      string out;
      if(i<15)
      {
        out="L";
        string add = to_string(i+1);
        out+=add;
        rminind=out;
      }
    }
  }
  cout<<rminind;
  if(i!=2)
  {
    cout<<"->";
  }
  for(int i=0;i<index;i++)
  {
    if(uloc[i]==rminind)
    {
      sendindex=i;
      break;
    }
  }
  i++;
}


  /*int i=0;
  while(G[i].cd!=uloc[index])
  {
    i=i+1;
  }
  struct Gnode *temp= G[i];
  struct Gnode root;dj
  root.next=0;
  root.cd=G[i].cd;
  struct Gnode *treepointer=root;
  struct Gnode *treepointerlast=root;
  int min=10000;
  string minstr;
  while(visited!=index+1)
  {
    while(temp->next!=0)
    {
      if(ulocpresent(uloc,temp->next->cd,index)==0)
      {
        if((temp->next->d)<min)
          minstr=temp->next->cd;
      }
    }
    visited++;
    struct Gnode new;
    new.cd=minstr;
    treepointerlast->next=new;
    treepointerlast=new;
    for(int i=0;i<index;i++)
    {
      if(uloc[i]==minstr)
      {
      uloc[i]='0';
    }
  }
    int l=countRL();
    for(int i=0;i<l;i++)
    {
      if(G[i].cd==minstr)
        {
        temp=G[i];
        break;
      }
    }
  }
  */
}
void adminu(string rid)
{
  string rid2;
  rid2=rid+"orders.txt";

  ifstream fin;
  fin.open(rid2);
  if(!fin)
  {
    cout<<"restaurant does not exist";
  }
    string uloc[20];
    int index=0;
    for(int i=0;i<20;i++)
    {
    uloc[i]="0";
  }
  while(fin)
  {

    string currloc;
    getline(fin,currloc);
    while(getline(fin,currloc))
    {

      string getuloc;
      getuloc=currloc[0];
      getuloc+=currloc[1];
      getuloc+=currloc[2];
      if(int(getuloc[2])==32)
      {
        getuloc.erase(2);
      }
      uloc[index++]=getuloc;
    }
  }
    // apply steiner on map with restaurant rid and locations in uloc array
    uloc[index]=rid;
    steiner(uloc,index);
}

int main()
{
    int var=0;
    cout<<"\n\n\n\t=============== WELCOME TO FOOD ORDERING SYSTEM ===============\n\n\n"<<endl;
    cout<<"\t\t\t\t[1] USER\n\t\t\t\t[2] ADMIN\n\t\t\t\t[3] EXIT\n\n\n\nEnter choice:  ";
    cin>>var;
    if(var==1){
        user U;
        U.userLogin();
        }
    else if(var==2){
          cout<<"Enter Restaurant\n";
          string rid;
          cin>>rid;
          cout<<rid<<"->";
          adminu(rid);

//       cout<<"Work Under Construction:";
    }
    else{
        exit(0);
    }
}
