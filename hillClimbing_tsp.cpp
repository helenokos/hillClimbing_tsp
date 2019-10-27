#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>	//pow, sqrt
#include <cfloat>	//DBL_MAX
#include <utility>	//pair
using namespace std;

//51個city
#define NUM 51

//紀錄第幾個城市及其座標
struct city {
	public : 
		city();
		city(int i, int j, int k) : index(i), x(j), y(k) {}
		int index, x, y;
};

bool openFileSuccess(ifstream&);								//判斷有無開檔成功
void buildData(ifstream&, vector<city>&, double[NUM][NUM]);		//建立所需資料
void hillClimbing(vector<city>&, double[NUM][NUM]);				//hillClimbing演算法
pair<int, int> swapCity(vector<city>&);							//隨機交換兩個城市
double travel(vector<city>&, double[NUM][NUM]);					//新路線的長度
void output(vector<city>&);										//輸出

int main() {
	ifstream fin;			//file io
	vector<city> road;		//紀錄目前路線
	double dis[NUM][NUM];	//兩兩城市之間的距離
	
	if (openFileSuccess(fin)) {		//如果開檔成功
		buildData(fin, road, dis);	//建立所需資料
		fin.close();				//關檔
	} else return -1;				//開檔失敗，離開程式
	hillClimbing(road, dis);		//開始Hill Climbing演算法
	output(road);					//輸出結果

	return 0;
}
//判斷有無開檔成功
bool openFileSuccess(ifstream& fin) {
	fin.open("eil51.txt");
	if (fin.fail()) {		//開檔失敗
		cout << "Can't not open file \"eil51.txt\"" << endl;
		return false;
	}
	//開檔成功
	cout << "Open file \"eil51.txt\" successfully" << endl;
	return true;
}
//建立所需資料
void buildData(ifstream& fin, vector<city>& road, double dis[NUM][NUM]) {
	//建立城市資訊，及彼此距離
	int index, x, y;
	while (fin >> index >> x >> y) {
		city tmp = city(index, x, y);
		road.push_back(tmp);
	}
	
	for (int i = 0; i < NUM; ++i) {
		for (int j = 0; j < NUM; ++j) {
			if (i == j) dis[i][j] = 0;
			else if (i > j) dis[i][j] = dis[j][i];
			else dis[i][j] = sqrt(pow(road[i].x - road[j].x, 2) + pow(road[i].y - road[j].y, 2));
		}
	}
	
}
//hillClimbing演算法
void hillClimbing(vector<city>& road, double dis[NUM][NUM]) {
	int cnt = 0;
	double minDis = DBL_MAX;
	srand(time(NULL));
	
	cout << "Hill Climbing..." << endl;
	while (cnt < 1000000) {						//若搜尋了1000000仍沒找到更好的答案就當目前為最佳解
		pair<int, int> chg = swapCity(road);	//更換旅行兩城市的順序
		double tmpDis = travel(road, dis);		//新路線距離
		if (tmpDis < minDis) {					//新路線更短->採用
			minDis = tmpDis;
			cnt = 0;
		} else {								//新路線沒比較好->不採用
			swap(road[chg.first], road[chg.second]);
			++cnt;
		}
	}
	
}
//隨機交換兩個城市
pair<int, int> swapCity(vector<city>& road) {
	int a = rand()%NUM, b = rand()%NUM;
	swap(road[a], road[b]);
	return make_pair(a, b);
}
//新路線的長度
double travel(vector<city>& road, double dis[NUM][NUM]) {
	double cnt = 0;
	for (int i = 0; i < NUM; ++i) {
		cnt += dis[road[i].index-1][road[i+1%NUM].index-1];
	}
	return cnt;
}
//輸出
void output(vector<city>& road) {
	for (int i = 0; i < NUM; ++i) {
		cout << road[i].index;
		if (i != NUM-1) cout << "->";
	}
	cout << endl;
}
