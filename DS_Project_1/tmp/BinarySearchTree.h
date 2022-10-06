#pragma once

#include "TreeNode.h"
#include "Manager.h"
#include <iostream>
#include <string>

class BinarySearchTree
{
	friend class TreeManager;

private:
public:
	TreeNode* m_root;
	int size = 0;
	BinarySearchTree() { m_root = NULL; }
	~BinarySearchTree();

	void insert(Node* node)
	{
		TreeNode* p = m_root, * pp = NULL;
		while (p)
		{
			pp = p;
			if (stoi(node->number) < p->m_data.unique_number)
				p = p->m_left;
			else if (stoi(node->number) > p->m_data.unique_number)
				p = p->m_right;
		}

		p = new TreeNode;
		p->m_data.dirname = node->dir;
		p->m_data.m_name = node->file;
		p->m_data.unique_number = stoi(node->number);
		if (m_root != NULL)
		{
			if (stoi(node->number) < pp->m_data.unique_number)
				pp->m_left = p;
			else
				pp->m_right = p;
		}
		else
			m_root = p;
		size++;
	}; // Data

	void deletion(int key) { // unique number = key
		TreeNode* p = m_root;
		TreeNode* q = 0;
		while (p && key != p->m_data.unique_number) {
			q = p;
			if (key < p->m_data.unique_number) {
				p = p->m_left;
			}
			else {
				p = p->m_right;
			}
		}
		if (p == 0) {
			return;
		}
		if (p->m_left == 0 && p->m_right == 0) { //leaf
			if (q == 0) {
				m_root = 0;
			}
			else if (q->m_left == p) {
				q->m_left = 0;
			}
			else {
				q->m_right = 0;
			}
			delete p;
		}
		else if (p->m_left == 0) {//오른쪽 자식만 있음
			if (q == 0) {
				m_root = p->m_right;
			}
			else if (q->m_left == p) {
				q->m_left = p->m_right;
			}
			else {
				q->m_right = p->m_right;
			}
			delete p;
		}
		else if (p->m_right == 0) {//왼쪽 자식만 있음
			if (q == 0) {
				m_root = p->m_left;
			}
			else if (q->m_left == p) {
				q->m_left = p->m_left;
			}
			else {
				q->m_left = p->m_left;
			}
			delete p;
		}
		else { //양쪽 다 자식이 있는 경우
			TreeNode* prevprev = p;
			TreeNode* prev = p->m_left;
			TreeNode* curr = p->m_left->m_right;

			while (curr) {// 왼쪽에서 가장 큰 값 찾기
				prevprev = prev;
				prev = curr;
				curr = curr->m_right;
			}

			p->m_data.unique_number = prev->m_data.unique_number;
			if (prevprev == p) {
				prevprev->m_left = prev->m_left;
			}
			else {
				prevprev->m_right = prev->m_left;
			}
			delete prev;
		}



	}
	// friend std::ostream &operator<<(std::ostream &os, const BinarySearchTree &tree)
	// {

	// 	// fill in your code to print a node in binary search tree
	// 	return os;
	// }

	void visit(TreeNode* t, ofstream* fout) {
		*fout << t->m_data.dirname << " / \"" << t->m_data.m_name << "\" / " << t->m_data.unique_number << endl;
	}

	void print_inorder(TreeNode* t, ofstream* fout) {
		if (t != NULL) {
			print_inorder(t->m_left, fout);
			visit(t, fout);
			print_inorder(t->m_right, fout);
		}

	}

	TreeNode* visit_inputdata(TreeNode* t, ofstream* fout, int key) {
		
		if (t->m_data.unique_number == key) {
			return t;
		}
		else {
			return NULL;
		}
	}

	TreeNode* print_preorder(TreeNode* t, ofstream* fout, int key) {
		if (t != NULL) {

			if (visit_inputdata(t, fout, key)) {
				return t;
			}
			print_preorder(t->m_left, fout, key);
			print_preorder(t->m_right, fout, key);
		}
	}

};
