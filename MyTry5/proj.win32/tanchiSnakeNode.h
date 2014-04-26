#ifndef __TANCHI_SNAKE_NODE_H__
#define __TANCHI_SNAKE_NODE_H__

#include <iostream>
#include "SnakeNode.h"
#include <vector>

using namespace std;

//ö��
typedef enum {  
	UP=1,  
	DOWN=2,  
	LEFT=3,  
	RIGHT=4  
};

//�ߵĽڵ�
class tanchiSnakeNode : public SnakeNode
{
	int row;//�ڼ���  
	int col;//�ڼ���  
	int dir;//���� 
public:  
	tanchiSnakeNode()
	{
		row = rand()%10;  //0~9
		col = rand()%10;
		dir=1;//������
	}

	void BodyMove();
	void HeadMove();
	void eat();
};

#endif 