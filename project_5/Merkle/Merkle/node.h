#pragma once
#pragma once
#include <iostream>
#include <sstream>
#include "sha256.h"
#include <string>
#include <vector>
using namespace std;

class node
{
private:
	string hash_str;
	node* parent;
	node* children[2];
public:
	node();
	node* getParent();
	void setChildren(node* children_l, node* children_r);
	node* getChildren(int index);
	void setParent(node* parent);
	string getHash();
	int checkDir();
	node* getSibling();
	void setHash(string hash_str);
	virtual ~node();
};
node::node()
{
	parent = nullptr;
	children[0] = nullptr;
	children[1] = nullptr;
}

//���ù�ϣֵ
void node::setHash(string hash_str)
{
	this->hash_str = sha2::hash256_hex_string(hash_str);
}
node* node::getParent()
{
	return parent;
}
void node::setParent(node* parent)
{
	this->parent = parent;
}
void node::setChildren(node* children_l, node* children_r)
{
	children[0] = children_l;
	children[1] = children_r;
}
node* node::getSibling() //�����ӵõ��Һ��ӣ����Һ��ӵõ�����
{
	//�õ��ýڵ�ĸ��ڵ�
	node* parent = getParent();

	//�жϸ��ڵ�����Ӻͱ��ڵ��Ƿ���ͬ
	//��ͬ�����Һ��ӣ���ͬ��������
	return parent->getChildren(0) == this ? parent->getChildren(1) : parent->getChildren(0);
}
node* node::getChildren(int index)
{
	return index <= 1 ? children[index] : nullptr;
}
string node::getHash()
{
	return hash_str;
}
int node::checkDir()
{
	//����丸�ڵ�������Ǹýڵ� ����0 �����򷵻�1
	return parent->getChildren(0) == this ? 0 : 1;
}

node::~node() {}


