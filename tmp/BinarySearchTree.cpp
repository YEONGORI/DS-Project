#include "BinarySearchTree.h"

void print_tree_node(TreeNode *t, ofstream *f_log)
{
	*f_log << t->tree_data.d_name << " / \"" << t->tree_data.f_name << "\" / " << t->tree_data.index << "\n";
}

void traversal_inorder(TreeNode *t, ofstream *f_log)
{
	if (t != NULL)
	{
		traversal_inorder(t->tree_left, f_log);
		print_tree_node(t, f_log);
		traversal_inorder(t->tree_right, f_log);
	}
}

TreeNode *search_tree_node(TreeNode *t, ofstream *f_log, int index)
{
	if (t->tree_data.index == index)
		return t;
	return (NULL);
}

TreeNode *traversal_preorder(TreeNode *t, ofstream *f_log, int index)
{
	if (t != NULL)
	{
		if (search_tree_node(t, f_log, index))
			return (t);
		traversal_preorder(t->tree_left, f_log, index);
		traversal_preorder(t->tree_right, f_log, index);
	}
	return (NULL);
}