#include"judge.cpp"
#include"player14348000.cpp"

using namespace std;

//�ô���������Ҫʵ�ֲ��еĺ�����,���ܱ��� 
//������һ�����Ե����� 
int main(){
	Player14348000 players[4]; //��λ��� 
	vector<Player*> va;
	int i;
	
	for(i=0;i<4;++i) 
		va.push_back(players+i);
		
	Judge judge(va);  //���� 
	
	for(i=0;i<4;++i)
		va[i]->setJudge(&judge); //ÿλ���Ҫ����ͬһ������ 
	
	judge.run(); //��ʼ��Ϸ 
}
