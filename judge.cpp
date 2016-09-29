#include"judge.h"
using namespace std; 

//���еĺ���������ʵ��

//��������һ�ȡ�Լ��ı�ţ�ID�� 
int Judge::getId(Player* player){
	for(int i=0;i<4;++i)
		if(players[i]==player)
			return i;
	//error		
	return -1;
} 

//��ȡ�Ƶļ���, ����Խ�������Խ��
int Judge::getCardLevel(Card card){
	if (card == mainCard)return 4;
	if (card.number == mainCard.number)return 3;
	if (card.color == mainCard.color)return 2;
	return 1;
}

//card1 �� card2 �ȳ�
//��card1 ���� card2, �򷵻�true
bool Judge::cmpCard2(Card card1, Card card2){
	//��С�Ƚ�
	//���е���>����>����>����
	//�ڲ�����: A>K>Q>J>10>...>2
	int lv1 = getCardLevel(card1);
	int lv2 = getCardLevel(card2);
	if (lv1 > lv2)return true;
	if (lv1 < lv2)return false;
	// when lv1 == lv2
	// ͬ��ͬ��, �ȳ���ʤ
	return card1.number >= card2.number;
}

//���һ���غ�(ÿ�˳�һ����)��ʤ��
//�������: ��ǰ�غϵĳ���˳��(������˳������), (Card, ������ID)
//���ظûغϵ�ʤ��
//���贫��Ĳ�����Υ��
int Judge::getTurnWinner(vector<pair<Card,int> > vp){
	pair<Card,int> p = vp[0];
	Card card1 = p.first;
	int win = p.second;
	//ע��, i���ǳ����˵�id
	for (int i = 1;i < 4;++i){
		pair<Card,int> w = vp[i];
		Card card2 = w.first;
		if (!cmpCard2(card1, card2)){
			card1 = card2;
			win = w.second;
		}
	}
	return win;
}
