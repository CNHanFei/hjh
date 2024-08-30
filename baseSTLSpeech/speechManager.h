#pragma once
#include<iostream> 
#include<vector> 
#include<map> 
#include "speaker.h" 
using namespace std;


class SpeechManager {
public:
	//构造
	SpeechManager();

	//打印编号
	void PrintIndex(vector<int> v);

	//展示菜单功能
	void showMnue();

	//退出
	void exitSystem();

	//初始化属性
	void initSpeech();

	//创建12个选手
	void creatSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();
	
	//显示晋级结果
	void showScore();

	//保存分数
	void saveRecord();

	 
	//析构
	~SpeechManager();



	//保存第一轮的编号	 12人
	vector<int> v1;

	//保存第二轮的编号   6人
	vector<int> v2;


	//保存前三名的编号	 3人
	vector<int> v3;


	//实现编号对应选手的容器
	map<int, Speaker> mSpeaker;

	//记录轮数
	int Index;
};