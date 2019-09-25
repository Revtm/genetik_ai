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

vector <isi> populasi;
vector <int> P_fitness;
vector <int> persen_fitness;

void cetakPuzzle(int pzl[3][3]) {
  for(int i=0; i<3; i++ ){
    for(int j=0; j<3; j++){
      cout << pzl[i][j] << " ";
    }
    cout << endl;
  }
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


  tempPuzzle[0][0] = x.a;
  tempPuzzle[0][1] = x.b;
  tempPuzzle[1][1] = x.c;
  tempPuzzle[2][0] = x.d;
  tempPuzzle[2][2] = x.e;

  cetakPuzzle(tempPuzzle);
  cout << endl << endl;

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

  cout  << "fitness: "<<total << endl;
  return total;
}

isi seleksi(){
  int roda[100];
  int temp = 0;
  for(int i = 0 ; i < populasi.size() ; i++){
    for(int j = temp ; j < temp + persen_fitness[i]  ; j++){
      roda[j]=i;
    }
    temp += persen_fitness[i];
  }

  srand(time(0));
  isi x = populasi[roda[rand()%temp]];

  return x;
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
  }
}

int main(){
isi x,y;

  buatPopulasi();

  cout << "===================\n";
  cout << populasi[0].a << endl;
  cout << P_fitness[0] << endl;

  return 0;
}
