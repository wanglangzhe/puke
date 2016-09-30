#include"judge.h"
#include <cstdlib>
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

bool Judge::DiscardValid(Player *player, Card card){
	vector<Card> handCards = getCurrentCards(player);
	bool has = false;
	for (size_t i = 0; i < handCards.size();++i){
		if (handCards[i] == card){
			has = true;
			break;
		}
	}
	if (!has)return false;
	vector<pair<Card,int> > turnCards = getCurrentTurn(player);
	if (turnCards.empty())return true;
	Card firstCard = turnCards[0].first;
	Card mainCard = getMainCard(player);
	int curColor = firstCard.color; 
	if (firstCard.number == mainCard.number)curColor = mainCard.color;
	int myColor = card.color;
	if (card.number == mainCard.number)myColor = mainCard.color;
	if (curColor == myColor)return true;

	for (size_t i = 0; i < handCards.size();++i){
		//��������ɫ, ���ǲ���!
		if (handCards[i].color == curColor)return false;
	}
	return true;
}

Card Judge::DisRightCard(Player *player){
	vector<Card> handCards = getCurrentCards(player);
	vector<pair<Card,int> > turnCards = getCurrentTurn(player);
	if (turnCards.empty()){
		return handCards[rand() % handCards.size()];
	}
	vector<Card> vc;
	int curColor = turnCards[0].first.color;
	Card mainCard = getMainCard(player);
	bool force = false;
	//���Ʊ�ɫ
	if (turnCards[0].first.number == mainCard.number)curColor = mainCard.color;
	for (size_t i = 0;i < handCards.size();++i){
		int myColor = handCards[i].color;
		if (handCards[i].number == mainCard.number){
			myColor = mainCard.color;
		}
		if (myColor == curColor){
			force = true;
			vc.push_back(handCards[i]);
		}
	}
	if (!force){
		for (size_t i = 0;i < handCards.size();++i){
			vc.push_back(handCards[i]);
		}
	}
	return vc[rand() % vc.size()];

}
