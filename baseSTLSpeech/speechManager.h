#pragma once
#include<iostream> 
#include<vector> 
#include<map> 
#include "speaker.h" 
using namespace std;


class SpeechManager {
public:
	//����
	SpeechManager();

	//��ӡ���
	void PrintIndex(vector<int> v);

	//չʾ�˵�����
	void showMnue();

	//�˳�
	void exitSystem();

	//��ʼ������
	void initSpeech();

	//����12��ѡ��
	void creatSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();
	
	//��ʾ�������
	void showScore();

	//�������
	void saveRecord();

	 
	//����
	~SpeechManager();



	//�����һ�ֵı��	 12��
	vector<int> v1;

	//����ڶ��ֵı��   6��
	vector<int> v2;


	//����ǰ�����ı��	 3��
	vector<int> v3;


	//ʵ�ֱ�Ŷ�Ӧѡ�ֵ�����
	map<int, Speaker> mSpeaker;

	//��¼����
	int Index;
};