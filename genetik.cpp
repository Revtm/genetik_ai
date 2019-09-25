#include <bits/stdc++.h>
using namespace std;

string target = "00001111";
char karakter[2] = {'0', '1'};
vector <string> populasi;

int fitnessScore(string indiv){
  int score = 0;
  for(int i = 0 ; i < indiv.size() ; i++){
    if(indiv[i] == target[i]){
      score++;
    }
  }

  return score;
}

void seleksiIndividu(){
  vector <int> scoreIndividu;
  vector <int> persenScoreIndividu;
  int temp = 0;
  int totalTemp = 0;
  int tempF = 0;

  for(int i = 0 ; i < populasi.size() ; i++){
      temp = fitnessScore(populasi[i]);
      totalTemp += temp;
      cout << temp << endl;
      scoreIndividu.push_back(temp);
  }


  for(int j = 0 ; j < populasi.size() ; j++){
      tempF = (scoreIndividu[j]*100)/totalTemp;
      cout << tempF << endl;
      persenScoreIndividu.push_back(tempF);
  }

  scoreIndividu.clear();
  persenScoreIndividu.clear();

}

string buatIndividu(int x){
  string indiv = "";
  for(int i = 0; i < target.size() ; i++){
      srand(time(0)+i+x);
      indiv += karakter[rand()%2];
  }
  return indiv;
}

void buatPopulasi (vector <string> *populasi){
  string temp = "";
  for(int i = 0 ; i < 4 ; i++){
    temp = buatIndividu(rand());
    (*populasi).push_back(temp);
  }
}

void tampilPopulasi(){
  for(int i = 0 ; i < populasi.size() ; i++){
    cout << populasi[i] << endl;
  }
}

int main(){
  buatPopulasi(&populasi);
  tampilPopulasi();

  seleksiIndividu();
  return 0;
}
