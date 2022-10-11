#include "BinarySearchTree.h"

void print_bst_node(Database_BST_Node *t, ofstream *f_log)
{
	*f_log << t->tree_data->dir_name << " / \"" << t->tree_data->file_name << "\" / " << t->tree_data->index << "\n";
}

void traversal_inorder(Database_BST_Node *t, ofstream *f_log)
{
	if (t != NULL)
	{
		traversal_inorder(t->tree_left, f_log);
		print_bst_node(t, f_log);
		traversal_inorder(t->tree_right, f_log);
	}
}

Database_BST_Node *search_bst_node(Database_BST_Node *t, int index)
{
	if (t->tree_data->index == index)
		return t;
	return (NULL);
}

Database_BST_Node *traversal_preorder(Database_BST_Node *t, ofstream *f_log, int index)
{
	if (t != NULL)
	{
		if (search_bst_node(t, index))
			return (t);
		traversal_preorder(t->tree_left, f_log, index);
		traversal_preorder(t->tree_right, f_log, index);
	}
	return (NULL);
}