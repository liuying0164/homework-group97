#pragma once
#pragma once
#include "node.h"
#include <iostream>
#include "sha256.h"
using namespace std;
class tree
{
private:
	string merkleRoot;
	int makeBinary(vector<node*>& node_vector);
	void printTreeLevel(vector<node*> v);
	vector<vector<node*>> base; //��������һ�����ڵ��б�
public:
	tree();
	void buildTree();
	void buildBaseLeafes(vector<string> base_leafs);
	int verify(string hash);
	virtual ~tree();
};

tree::tree() {}

int tree::makeBinary(vector<node*>& node_vector) //ʹҶ�ӽڵ��Ϊ˫��
{
	int vectSize = node_vector.size();
	if ((vectSize % 2) != 0) //���Ԫ�ظ���Ϊ�������Ͱ������һ���ڵ�push_backһ��
	{
		node_vector.push_back(node_vector.end()[-1]);
		vectSize++;
	}
	return vectSize;
}

void tree::printTreeLevel(vector<node*> v)
{
	for (node* el : v)
	{
		cout << el->getHash() << endl;
	}
	cout << endl;
}

void tree::buildTree() //����merkle tree
{
	do
	{
		vector<node*> new_nodes;
		makeBinary(base.end()[-1]); //����βԪ�� ��һ���ڵ��б�

		for (int i = 0; i < base.end()[-1].size(); i += 2)
		{
			node* new_parent = new node; //���ø��׽ڵ� �������һ��Ԫ�� ��һ���ڵ��б�ĵ�i��i+1��
			base.end()[-1][i]->setParent(new_parent);
			base.end()[-1][i + 1]->setParent(new_parent);

			//ͨ���������ӽڵ�Ĺ�ϣֵ���ø��ڵ��ϣֵ
			new_parent->setHash(base.end()[-1][i]->getHash() + base.end()[-1][i + 1]->getHash());
			//���ø��ڵ�����Һ��ӽڵ�����Ϊ������
			new_parent->setChildren(base.end()[-1][i], base.end()[-1][i + 1]);
			//��new_parentѹ��new_nodes
			new_nodes.push_back(new_parent);

			cout << "�� " << base.end()[-1][i]->getHash() << " �� " << base.end()[-1][i + 1]->getHash() << " ����,�õ���Ӧ���ڵ�Ĺ�ϣֵ " << endl;
		}

		cout << endl;
		cout << "�õ��Ķ�Ӧ���ڵ�Ĺ�ϣֵ:" << endl;
		printTreeLevel(new_nodes);

		base.push_back(new_nodes); //����һ�ֵĸ��ڵ�new_nodesѹ��base

		cout << "�ò�Ľ���� " << base.end()[-1].size() << " ��:" << endl;
	} while (base.end()[-1].size() > 1); //����ÿһ�ֵõ���һ��ĸ��ڵ㣬֪���õ����ڵ� �˳�ѭ��

	merkleRoot = base.end()[-1][0]->getHash(); //���ڵ�Ĺ�ϣֵ

	cout << "Merkle Root : " << merkleRoot << endl << endl;
}

void tree::buildBaseLeafes(vector<string> base_leafs) //����Ҷ�ӽڵ��б�
{
	vector<node*> new_nodes;

	cout << "Ҷ�ӽ�㼰��Ӧ�Ĺ�ϣֵ: " << endl;

	for (auto leaf : base_leafs) //��ÿһ���ַ���������Ӧ�ڵ㣬��ͨ������ַ������ù�ϣֵ
	{
		node* new_node = new node;
		new_node->setHash(leaf);
		cout << leaf << ":" << new_node->getHash() << endl;

		new_nodes.push_back(new_node);
	}

	base.push_back(new_nodes);
	cout << endl;
}

int tree::verify(string hash)
{
	node* el_node = nullptr;
	string act_hash = hash;

	for (int i = 0; i < base[0].size(); i++)
	{
		if (base[0][i]->getHash() == hash)
		{
			el_node = base[0][i];
		}
	}
	if (el_node == nullptr)
	{
		return 0;
	}

	cout << "ʹ�õ��Ĺ�ϣֵ:" << endl;
	cout << act_hash << endl;

	do  //��֤merkle tree�Ƿ�ı�� 
	{
		//���ڵ�Ĺ�ϣ�����ӵĹ�ϣstring+�Һ��ӵĹ�ϣstring
		//���el_node�ĸ��ڵ����ڵ���el_node
		if (el_node->checkDir() == 0)
		{
			//�����Ӿ� �����ӵĹ�ϣstring+�Һ��ӵĹ�ϣstring
			act_hash = sha2::hash256_hex_string(act_hash + el_node->getSibling()->getHash());
		}
		else
		{
			act_hash = sha2::hash256_hex_string(el_node->getSibling()->getHash() + act_hash);
		}

		std::cout << act_hash << endl;

		el_node = el_node->getParent();
	} while ((el_node->getParent()) != NULL); //������ڵ�

	return act_hash == merkleRoot ? 1 : 0;
}

tree::~tree() {}

