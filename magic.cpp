#include <bits/stdc++.h>
using namespace std;



int puzzle[3][3] = {
  {0,0,8},
  {9,0,1},
  {0,7,0}
};

struct isi{
  int a;
  int b;
  int c;
  int d;
  int e;
};

struct parent{
  isi par1;
  isi par2;
};

vector <isi> populasi;
vector <int> P_fitness;
vector <int> persen_fitness;

void cetakPuzzle(isi x) {
  int tempPuzzle[3][3] = {
  {0,0,8},
  {9,0,1},
  {0,7,0}
  };


  tempPuzzle[0][0] = x.a;
  tempPuzzle[0][1] = x.b;
  tempPuzzle[1][1] = x.c;
  tempPuzzle[2][0] = x.d;
  tempPuzzle[2][2] = x.e;

  for(int i=0; i<3; i++ ){
    for(int j=0; j<3; j++){
      cout << tempPuzzle[i][j] << " ";
    }
    cout << endl;
  }
}

void cetakHasil(isi x){
  int tempPuzzle[3][3] = {
  {0,0,8},
  {9,0,1},
  {0,7,0}
  };

  tempPuzzle[0][0] = x.a;
  tempPuzzle[0][1] = x.b;
  tempPuzzle[1][1] = x.c;
  tempPuzzle[2][0] = x.d;
  tempPuzzle[2][2] = x.e;

   // cetakPuzzle(tempPuzzle);
   // cout << endl << endl;
}

void hitungPersenFitness(){
  int total = 0;
  int x = 0;
  for(int i = 0 ; i < P_fitness.size() ; i++){
    total += P_fitness[i];
  }

  for(int i = 0 ; i < P_fitness.size() ; i++){
    x = (P_fitness[i] * 100)/total;
    persen_fitness.push_back(x);
  }

}

int hitungFitness(isi x){
  int total = 0;
  int temp = 0;

  int tempPuzzle[3][3] = {
  {0,0,8},
  {9,0,1},
  {0,7,0}
  };

  int target[5]={4,3,5,2,6};
  tempPuzzle[0][0] = x.a;
  tempPuzzle[0][1] = x.b;
  tempPuzzle[1][1] = x.c;
  tempPuzzle[2][0] = x.d;
  tempPuzzle[2][2] = x.e;

  int tempPuzz[5];
  tempPuzz[0] = x.a;
  tempPuzz[1] = x.b;
  tempPuzz[2] = x.c;
  tempPuzz[3] = x.d;
  tempPuzz[4] = x.e;

  for(int i = 0 ; i < 3 ; i++){
    if(tempPuzzle[i][0] != tempPuzzle[i][1] &&  tempPuzzle[i][0] != tempPuzzle[i][2] && tempPuzzle[i][1] != tempPuzzle[i][2]){
      for(int j = 0 ; j < 3 ; j++){
        temp += tempPuzzle[i][j];
      }
      if(temp == 15){
        total++;
      }
    }
    temp = 0;
  }

  for(int i = 0 ; i < 3 ; i++){
    if(tempPuzzle[0][i] != tempPuzzle[1][i] &&  tempPuzzle[0][i] != tempPuzzle[2][i] && tempPuzzle[1][i] != tempPuzzle[2][i]){
      for(int j = 0 ; j < 3 ; j++){
        temp += tempPuzzle[j][i];
      }
      if(temp == 15){
        total++;
      }
    }
    temp = 0;
  }

  if(tempPuzzle[0][0] != tempPuzzle[1][1] &&  tempPuzzle[1][1] != tempPuzzle[2][2] && tempPuzzle[0][0] != tempPuzzle[2][2]){
      temp = tempPuzzle[0][0] + tempPuzzle[1][1] + tempPuzzle[2][2];

      if(temp == 15){
        total++;
      }
  }
  temp = 0;

  if(tempPuzzle[0][0] != tempPuzzle[1][1] &&  tempPuzzle[1][1] != tempPuzzle[2][2] && tempPuzzle[0][0] != tempPuzzle[2][2]){
      temp = tempPuzzle[0][2] + tempPuzzle[1][1] + tempPuzzle[2][0];

      if(temp == 15){
        total++;
      }
  }
  temp = 0;



  cout  << "fitness: "<< total << endl;

  return total;
}

int carimax(){
  int max = 0;
  for(int i = 0 ; i < P_fitness.size() ; i++){
    if(P_fitness[i] > max){
      max = P_fitness[i];
    }
  }
  return max;
}

void sortingpop(){
  int temp;
  isi tempindiv;
  for(int i=0; i< populasi.size()-1 ; i++){
    for(int j=0 ; j < populasi.size()-i-1 ;j++){
      if(P_fitness[j] < P_fitness[j+1]){
        temp = P_fitness[j];
        P_fitness[j]=P_fitness[j+1];
        P_fitness[j+1]=temp;

        tempindiv = populasi[j];
        populasi[j]=populasi[j+1];
        populasi[j+1]=tempindiv;
      }
    }
  }
}

isi seleksi(int n){
  // int roda[100];
  // int temp = 0, temp2 = 0;
  // for(int i = 0 ; i < populasi.size() ; i++){
  //   if(persen_fitness[i] > 0){
  //     temp2=temp + persen_fitness[i];
  //     for(int j = temp ; j <= temp2+1  ; j++){
  //       roda[j]=i;
  //     }
  //     temp += persen_fitness[i];
  //   }
  // }


  srand(time(0)+n);
  isi x ;
  x= populasi[rand()%10];
  //cout << "\njumlah temp: " <<temp<< endl << endl;
  return x;
}

int mutasi(){

  int gen[5]={2,3,4,5,6};

  srand(time(0));
  return gen[rand()%5];

}

void crossover(){
  parent parent1;

  int temp, fitness;
  sortingpop();
  parent1.par1 = seleksi(2);
  parent1.par2 = seleksi(6);

  int mutasianak[5] = {parent1.par1.a, parent1.par1.b, parent1.par1.c, parent1.par1.d, parent1.par1.e};
  int mutasianak2[5] = {parent1.par2.a, parent1.par2.b, parent1.par2.c, parent1.par2.d, parent1.par2.e};

  for(int i = 0 ; i < 2 ; i++){
    srand(time(0));
    int r =rand()%5;
    srand(time(0)+3);
    int r2 =rand()%5;
    temp = mutasianak[r];
    mutasianak[r] = mutasianak2[r2];
    mutasianak2[r2] = temp;

  }

  parent1.par1.a = mutasianak2[0];
  parent1.par1.b = mutasianak2[1];
  parent1.par1.c = mutasianak[2];
  parent1.par1.d = mutasianak[3];
  parent1.par1.e = mutasianak[4];

  parent1.par2.a = mutasianak[0];
  parent1.par2.b = mutasianak[1];
  parent1.par2.c = mutasianak2[2];
  parent1.par2.d = mutasianak2[3];
  parent1.par2.e = mutasianak2[4];


  int mutasianak3[5] = {parent1.par1.a, parent1.par1.b, parent1.par1.c, parent1.par1.d, parent1.par1.e};
  int mutasianak4[5] = {parent1.par2.a, parent1.par2.b, parent1.par2.c, parent1.par2.d, parent1.par2.e};

  for(int i = 0 ; i < 5 ;i++){
    srand(time(0));
    int prob = rand()%100;
    if(prob < 45){
      srand(time(0));
      mutasianak3[rand()%5] = mutasi();
      srand(time(0));
      mutasianak4[rand()%5] = mutasi();
    }
  }

  parent1.par1.a = mutasianak3[0];
  parent1.par1.b = mutasianak3[1];
  parent1.par1.c = mutasianak3[2];
  parent1.par1.d = mutasianak3[3];
  parent1.par1.e = mutasianak3[4];

  parent1.par2.a = mutasianak4[0];
  parent1.par2.b = mutasianak4[1];
  parent1.par2.c = mutasianak4[2];
  parent1.par2.d = mutasianak4[3];
  parent1.par2.e = mutasianak4[4];

  cout << "\n======cross-over==========\n";

  populasi.push_back(parent1.par1);
  fitness = hitungFitness(parent1.par1);
  P_fitness.push_back(fitness);

  populasi.push_back(parent1.par2);
  fitness = hitungFitness(parent1.par2);
  P_fitness.push_back(fitness);

  cetakPuzzle(parent1.par1);
  cout << endl;
  cetakPuzzle(parent1.par2);
  cout << endl;

  persen_fitness.clear();
  hitungPersenFitness();

}

isi buatIndividu(int acak){
  isi x;
  int temp;
  vector<int> gen;
  gen.push_back(2);
  gen.push_back(3);
  gen.push_back(4);
  gen.push_back(5);
  gen.push_back(6);

  vector<int>genT;

  srand(time(0) + 1 + acak);
  temp = rand()%5;
  x.a = gen[temp];

  for(int i = 0 ; i < gen.size(); i++){
    if(gen[i] != x.a){
      genT.push_back(gen[i]);
    }
  }
  gen.clear();

  srand(time(0) + 2 + acak);
  temp = rand()%4;
  x.b = genT[temp];

  for(int i = 0 ; i < genT.size(); i++){
    if(genT[i] != x.b){
      gen.push_back(genT[i]);
    }
  }
  genT.clear();

  srand(time(0) + 3 + acak);
  temp = rand()%3;
  x.c = gen[temp];

  for(int i = 0 ; i < gen.size(); i++){
    if(gen[i] != x.c){
      genT.push_back(gen[i]);
    }
  }
  gen.clear();


  srand(time(0) + 4 + acak);
  temp = rand()%2;
  x.d = genT[temp];

  for(int i = 0 ; i < genT.size(); i++){
    if(genT[i] != x.d){
      gen.push_back(genT[i]);
    }
  }
  genT.clear();


  srand(time(0) + 5 + acak);
  temp = rand()%1;
  x.e = gen[temp];

  for(int i = 0 ; i < gen.size(); i++){
    if(gen[i] != x.e){
      genT.push_back(gen[i]);
    }
  }
  gen.clear();



  return x;
}

void buatPopulasi(){
  isi x; int fitness;
  for(int i = 0 ; i < 10 ; i++){
    x = buatIndividu(i);
    populasi.push_back(x);
    fitness = hitungFitness(x);
    P_fitness.push_back(fitness);
    cetakPuzzle(x);
  }
  hitungPersenFitness();
}

bool cekFit(){
  for(int i = 0 ; i < populasi.size() ; i ++){
    if(P_fitness[i] == 5){
      cout << "============================ \n hasil: \n";
      cetakPuzzle(populasi[i]);
      cout << endl;
      return true;
    }
  }
  return false;
}

int main(){
isi x,y;
  bool fitnesstarget = false;

  buatPopulasi();
  // for(int i = 0 ; i < populasi.size() ; i++){
  //   cout << P_fitness[i] << endl;
  //   cout << populasi[i].a << populasi[i].b<<populasi[i].c<<populasi[i].d<<populasi[i].e << endl;
  // }
  //
  // cout << "\n====================\n";
   sortingpop();
  // for(int i = 0 ; i < populasi.size() ; i++){
  //   cout << P_fitness[i] << endl;
  //   cout << populasi[i].a << populasi[i].b<<populasi[i].c<<populasi[i].d<<populasi[i].e << endl;
  // }

  while(fitnesstarget == false){
    sortingpop();
    crossover();
    fitnesstarget = cekFit();
  }

  return 0;
}
