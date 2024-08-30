#include <iostream>
#include "speechManager.h"
#include <algorithm>
#include <deque>
#include <numeric>
#include <fstream>

using namespace std;

//构造
SpeechManager::SpeechManager() {
	this->initSpeech();		//构造函数里调用 初始化属性 函数
	this->creatSpeaker();	//构造函数里调用 创建选手 函数
}


//打印编号
void SpeechManager::PrintIndex(vector<int> v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//展示菜单功能
void SpeechManager::showMnue() {
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出
void SpeechManager::exitSystem() {
	cout << "结束了" << endl;
	exit(0);
}

//初始化属性
void SpeechManager::initSpeech() {
	//容器置空
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->mSpeaker.clear();
	//初始化比赛轮数
	this->Index = 1;
}

//创建12个选手
void SpeechManager::creatSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0;i < nameSeed.size();i++) {
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.name = name;

		for (int j = 0;j < 2;j++) {
			sp.Score[j] = 0;
		}


		this->v1.push_back(i + 100001);
		//编号和对应的人 放入map类型的容器里
		this->mSpeaker.insert(make_pair(i + 100001, sp));


	}
}

//开始比赛
void SpeechManager::startSpeech() {
	// 第一轮比赛
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示晋级结果
	this->showScore();
	//第二轮比赛
	this->Index++;
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示最终结果
	this->showScore();
	//4、保存分数
	this->saveRecord();
	cout << "比赛结束!" << endl;
	system("pause");
	system("cls");

}

//抽签	 (把顺序打乱)
void SpeechManager::speechDraw() {
	cout << this->Index << "轮比赛正在抽签" << endl;
	cout << "---------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->Index == 1) {		//第一轮
		random_shuffle(v1.begin(),v1.end());	//打乱顺序
		PrintIndex(v1);

	}
	else {	 //第二轮
		random_shuffle(v2.begin(), v2.end());
		PrintIndex(v2);
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}

//比赛
void SpeechManager::speechContest() {
	cout << "------------- 第" << this->Index << "轮正式比赛开始：------------- " << endl;
	multimap<double, int, greater<int>> tempScore;	//临时容器，key存分数，value存编号
	int num = 0;  //记录人员个数
	vector<int> tempVec;	//比赛人员的容器
	if (this->Index == 1) {
		tempVec = this->v1;
	}
	else {
		tempVec = this->v2;
	}

	//遍历所有参赛选手
	for (vector<int>::iterator it = tempVec.begin(); it != tempVec.end(); it++) {
		num++;

		//随机赋分
		deque<double>d;
		for (int i = 0;i < 10;i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//排序
		//掐头去尾
		d.pop_back();
		d.pop_front();

		//取平均分
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / d.size();

		//赋值到具体的人上
		this->mSpeaker[*it].Score[this->Index - 1] = avg;

		//前6个一组，后6个一组
		tempScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator it = tempScore.begin();it != tempScore.end();it++) {
				cout << "编号:" << it->second << "姓名：" << this->mSpeaker[it->second].name << "成绩:" << this->mSpeaker[it->second].Score[this->Index - 1] << endl;

			}
			int count = 0;

			//取前三名
			for (multimap<double, int, greater<int>>::iterator it = tempScore.begin(); it != tempScore.end() && count < 3; it++, count++)
			{
				if (this->Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					v3.push_back((*it).second);
				}
			}
			tempScore.clear();
			cout << endl;
		}


	}
	cout << "------------- 第" << this->Index << "轮比赛完毕  ------------- " << endl;
	system("pause");
}

//显示晋级结果
void SpeechManager::showScore() {
	cout << "---------第" << this->Index << "轮晋级选手信息如下：-----------" << endl;
	vector<int> v;
	if (this->Index == 1) {
		v = v2;	//speechContest()里面两组的前三存到了v2里
	}
	else {
		v = v3;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << " 姓名： " << mSpeaker[*it].name << " 得分： " << mSpeaker[*it].Score[this->Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showMnue();


}

//保存分数
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);	// 用输出的方式打开文件  -- 写文件

	//将每个人数据写入到文件中
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << ","
			<< mSpeaker[*it].Score[1] << ",";
	}
	ofs.close();
	cout << "记录已经保存" << endl;
}

//析构
SpeechManager::~SpeechManager() {

}