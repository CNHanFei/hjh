#include <iostream>
#include "speechManager.h"
#include <algorithm>
#include <deque>
#include <numeric>
#include <fstream>

using namespace std;

//����
SpeechManager::SpeechManager() {
	this->initSpeech();		//���캯������� ��ʼ������ ����
	this->creatSpeaker();	//���캯������� ����ѡ�� ����
}


//��ӡ���
void SpeechManager::PrintIndex(vector<int> v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//չʾ�˵�����
void SpeechManager::showMnue() {
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//�˳�
void SpeechManager::exitSystem() {
	cout << "������" << endl;
	exit(0);
}

//��ʼ������
void SpeechManager::initSpeech() {
	//�����ÿ�
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->mSpeaker.clear();
	//��ʼ����������
	this->Index = 1;
}

//����12��ѡ��
void SpeechManager::creatSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0;i < nameSeed.size();i++) {
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.name = name;

		for (int j = 0;j < 2;j++) {
			sp.Score[j] = 0;
		}


		this->v1.push_back(i + 100001);
		//��źͶ�Ӧ���� ����map���͵�������
		this->mSpeaker.insert(make_pair(i + 100001, sp));


	}
}

//��ʼ����
void SpeechManager::startSpeech() {
	// ��һ�ֱ���
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ�������
	this->showScore();
	//�ڶ��ֱ���
	this->Index++;
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ���ս��
	this->showScore();
	//4���������
	this->saveRecord();
	cout << "��������!" << endl;
	system("pause");
	system("cls");

}

//��ǩ	 (��˳�����)
void SpeechManager::speechDraw() {
	cout << this->Index << "�ֱ������ڳ�ǩ" << endl;
	cout << "---------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->Index == 1) {		//��һ��
		random_shuffle(v1.begin(),v1.end());	//����˳��
		PrintIndex(v1);

	}
	else {	 //�ڶ���
		random_shuffle(v2.begin(), v2.end());
		PrintIndex(v2);
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}

//����
void SpeechManager::speechContest() {
	cout << "------------- ��" << this->Index << "����ʽ������ʼ��------------- " << endl;
	multimap<double, int, greater<int>> tempScore;	//��ʱ������key�������value����
	int num = 0;  //��¼��Ա����
	vector<int> tempVec;	//������Ա������
	if (this->Index == 1) {
		tempVec = this->v1;
	}
	else {
		tempVec = this->v2;
	}

	//�������в���ѡ��
	for (vector<int>::iterator it = tempVec.begin(); it != tempVec.end(); it++) {
		num++;

		//�������
		deque<double>d;
		for (int i = 0;i < 10;i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//����
		//��ͷȥβ
		d.pop_back();
		d.pop_front();

		//ȡƽ����
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / d.size();

		//��ֵ�����������
		this->mSpeaker[*it].Score[this->Index - 1] = avg;

		//ǰ6��һ�飬��6��һ��
		tempScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator it = tempScore.begin();it != tempScore.end();it++) {
				cout << "���:" << it->second << "������" << this->mSpeaker[it->second].name << "�ɼ�:" << this->mSpeaker[it->second].Score[this->Index - 1] << endl;

			}
			int count = 0;

			//ȡǰ����
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
	cout << "------------- ��" << this->Index << "�ֱ������  ------------- " << endl;
	system("pause");
}

//��ʾ�������
void SpeechManager::showScore() {
	cout << "---------��" << this->Index << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
	vector<int> v;
	if (this->Index == 1) {
		v = v2;	//speechContest()���������ǰ���浽��v2��
	}
	else {
		v = v3;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << mSpeaker[*it].name << " �÷֣� " << mSpeaker[*it].Score[this->Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showMnue();


}

//�������
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);	// ������ķ�ʽ���ļ�  -- д�ļ�

	//��ÿ��������д�뵽�ļ���
	for (vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	{
		ofs << *it << ","
			<< mSpeaker[*it].Score[1] << ",";
	}
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;
}

//����
SpeechManager::~SpeechManager() {

}