#include <bits/stdc++.h>
using namespace std;

int gen[5]={2,3,4,5,6};

int magic[3][3]={
  {0,0,8},
  {9,0,1},
  {0,7,0}
};

struct individu{
  int kromosom[5];
  int fitness;
};

vector <individu> populasi;

int fungsirandom(int n, int i, int j){
  srand(time(0)+i+j);
  int r =rand()%n;

  return r;
}

void cetakPuzzle(individu baru) {
  int tempPuzzle[3][3] = {
  {0,0,8},
  {9,0,1},
  {0,7,0}
  };


  tempPuzzle[0][0] = baru.kromosom[0];
  tempPuzzle[0][1] = baru.kromosom[1];
  tempPuzzle[1][1] = baru.kromosom[2];
  tempPuzzle[2][0] = baru.kromosom[3];
  tempPuzzle[2][2] = baru.kromosom[4];

  for(int i=0; i<3; i++ ){
    for(int j=0; j<3; j++){
      cout << tempPuzzle[i][j] << " ";
    }
    cout << endl;
  }
}

void sortingPop(){
  individu temp;
  for(int i=0; i< populasi.size()-1 ; i++){
    for(int j=0 ; j < populasi.size()-i-1 ;j++){
      if(populasi[j].fitness < populasi[j+1].fitness){
        temp = populasi[j];
        populasi[j]=populasi[j+1];
        populasi[j+1] = temp;
      }
    }
  }
}

int hitungFitness(individu baru){
  int total = 0;
  int temp = 0;

  int tempPuzzle[3][3] = {
  {0,0,8},
  {9,0,1},
  {0,7,0}
  };

  tempPuzzle[0][0] = baru.kromosom[0];
  tempPuzzle[0][1] = baru.kromosom[1];
  tempPuzzle[1][1] = baru.kromosom[2];
  tempPuzzle[2][0] = baru.kromosom[3];
  tempPuzzle[2][2] = baru.kromosom[4];


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

individu buatIndividu(int j){
  individu baru;

  for(int i = 0 ; i < 5 ; i++ ){
    baru.kromosom[i] = gen[fungsirandom(5,i,j)];
  }

  baru.fitness = hitungFitness(baru);

  return baru;

}


bool cekFit(int fitness){
  return (fitness == 8);
}

void buatPopulasi(bool *fit){
  individu baru;
  for(int i = 0 ; i < 10 ; i++){
    baru = buatIndividu(i);
    cetakPuzzle(baru);
    *fit=cekFit(baru.fitness);
    populasi.push_back(baru);
  }

}

individu seleksi(int i, int j){
  return populasi[fungsirandom(10, i, j)];
}

int mutasi(int i){
  return gen[fungsirandom(5,1,i)];
}

void cross_over(bool *fit){
  individu child, parent1, parent2;
  int temp=0;

  parent1 = seleksi(1,1);
  parent2 = seleksi(4,5);

  for(int i = 0 ; i < 5; i++){
    int prob = (fungsirandom(100,i,2));

    if(prob < 45){
      child.kromosom[i] = mutasi(i);
    }else if(prob < 90){
      child.kromosom[i] = parent2.kromosom[i];
    }else{
      child.kromosom[i] = parent1.kromosom[i];
    }
  }

  child.fitness=hitungFitness(child);
  *fit = cekFit(child.fitness);
  cetakPuzzle(child);

  populasi.push_back(child);

}


int main(){
  bool fit = false;

  buatPopulasi(&fit);
  while(fit == false){
    sortingPop();
    cross_over(&fit);
  }

  sortingPop();
  if(fit == true){
    cout << endl;
    cout <<"hasil: \n";
    cetakPuzzle(populasi[0]);
  }

  return 0;
}
