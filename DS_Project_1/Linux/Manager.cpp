#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "Manager.h"
#include "Queue.h"
#include "Stack.h"
#include "TreeManager.h"
#include "BinarySearchTree.h"

#define BUFF_SIZE 128

using namespace std;

Manager::~Manager()
{
    if (f_log.is_open())
        f_log.close();
}

void Manager::Run(const char *filepath)
{
    f_log.open(RESULT_LOG_PATH);
    f_cmd.open("command.txt");
    f_file.open("filesnumbers.csv");
    f_new.open("new_filenumbers.csv");

    Loaded_LIST *LIST = new Loaded_LIST;
    BinarySearchTree *BST = new BinarySearchTree;

    FILE *input_file, *output_file;

    string img_path;

    char cmd[BUFF_SIZE] = {};
    unsigned char input_data[512][512];
    unsigned char output_data[512][512];

    while (!f_cmd.eof())
    {
        // Read the command
        f_cmd.getline(cmd, BUFF_SIZE);
        char *tmp = strtok(cmd, " ");
        char *ch_cr = strrchr(tmp, 13);
        if (ch_cr)
            *ch_cr = 0;
        if (strcmp(tmp, "LOAD") == 0)
        {
            ROW_LIST *NEW_LIST = new ROW_LIST;

            f_log << "==========LOAD==========\n";
            if (!f_log)
            {
                f_log << "==========ERROR==========\n100\n=========================\n";
                continue;
            }
            while (!f_file.eof())
            {
                char buff[BUFF_SIZE];
                string index, file_name;

                if (!f_file.getline(buff, sizeof(buff)))
                    break;

                index = strtok(buff, ",");
                file_name = strtok(NULL, "\n");
                file_name = file_name.substr(0, file_name.find('.'));

                if (NEW_LIST->edge_left == NULL)
                    index = index.substr(3, index.size());
                if (NEW_LIST->size >= 100)
                    ; // 이거 팝이 잘못됨

                NEW_LIST->PushNode(file_name, "images", index);
                f_log << file_name << "/" << index << '\n';
            }
            LIST->PushList(NEW_LIST);
            f_log << "========================\n\n";
        }
        else if (strcmp(tmp, "ADD") == 0)
        {
            ROW_LIST *NEW_LIST = new ROW_LIST;
            string path, d_name, f_name;

            d_name = strtok(NULL, " ");
            f_name = strtok(NULL, "\n");
            while (1)
                ;

            path.append(d_name).append("/").append(f_name);
            path.erase(path.find(13));

            while (!f_new.eof())
            {
                char buff[BUFF_SIZE];
                string index, file_name;

                if (!f_new.getline(buff, BUFF_SIZE))
                    break;
                index = strtok(buff, ",");
                file_name = strtok(NULL, "\n");
                file_name.erase(file_name.find(13));

                // if (1) 전체 리스트의 크기가 100이 넘는 경우 에러처리
                if (LIST->IsEmpty())
                    f_log << "==========ERROR==========\n100\n=========================\n";
                NEW_LIST->PushNode(file_name, d_name, index);
            }
            LIST->PushList(NEW_LIST);
            f_log << "==========ADD===========\nSUCCESS\n========================\n\n";
        }
        else if (strcmp(tmp, "MODIFY") == 0)
        {
            string d_name, f_name, index;
            Node *cur_node = LIST->top_list->edge_left;
            Node *tmp_node;
            ROW_LIST *CUR_LIST = LIST->top_list;

            d_name = strtok(NULL, " ");
            f_name = strtok(NULL, "\"");
            index = strtok(NULL, " ");

            // if () dir_name, file_name, index 중 하나라도 안들어 있으면 에러처리

            while (cur_node->dir_name != d_name)
            {
                CUR_LIST = CUR_LIST->go_down;
                if (CUR_LIST == NULL)
                {
                    f_log << "==========ERROR==========\n300\n=========================\n";
                    break;
                }
                cur_node = CUR_LIST->edge_left;
            }
            if (!CUR_LIST)
                continue;

            while (cur_node->file_name != f_name)
            {
                cur_node = cur_node->next;
                if (cur_node == NULL)
                {
                    f_log << "==========ERROR==========\n300\n=========================\n";
                    break;
                }
            }
            if (!cur_node)
                continue;

            tmp_node = cur_node->next;
            tmp_node->prev = cur_node->prev;
            cur_node->prev->next = tmp_node;
            cur_node->next->prev = tmp_node->prev;
            delete cur_node;
            CUR_LIST->PushNode(f_name, d_name, index);
            f_log << "=========MODIFY==========\nSUCCESS\n=========================\n\n";
        }
        else if (strcmp(tmp, "MOVE") == 0)
        {
            if (LIST->IsEmpty())
            {
                f_log << "==========ERROR==========\n400\n=========================\n";
                continue;
            }

            int low_index = BUFF_SIZE * BUFF_SIZE;
            ROW_LIST *START_LIST = LIST->bottom_list;
            while (START_LIST != NULL)
            {
                Node *start_node = START_LIST->edge_right;
                while (start_node != NULL)
                {
                    if (BST->bst_size > 300)
                    {
                        TreeNode *cur_tree_node = BST->tree_root;

                        while (cur_tree_node->tree_left) //왼쪽 끝 노드로 이동
                            cur_tree_node = cur_tree_node->tree_left;

                        low_index = cur_tree_node->tree_data.index; //가장 작은 고유번호 구함
                        BST->deletion(low_index);                   // 삭제
                    }
                    Node *tmp_node = new Node("", "", "", NULL, NULL);

                    BST->insert(start_node);
                    tmp_node = start_node;
                    start_node = start_node->prev;
                    delete (tmp_node);
                }
                START_LIST = START_LIST->go_up;
            }
            f_log << "==========MOVE===========\nSUCCESS\n=========================\n\n";
        }
        else if (strcmp(tmp, "PRINT") == 0)
        {
            if (!BST->tree_root)
            {
                f_log << "==========ERROR==========\n500\n=========================\n";
                continue;
            }
            f_log << "=========PRINT===========\n";
            traversal_inorder(BST->tree_root, &f_log);
            f_log << "=========================\n\n";
        }
        else if (strcmp(tmp, "SEARCH") == 0)
        {
            if (BST->tree_root->tree_data.index == NULL)
            {
                f_log << "==========ERROR==========\n600\n=========================\n";
                continue;
            }

            f_log << "=========SEARCH==========\n";
            string file_name;
            TREE_STACK *S = new TREE_STACK();
            TREE_STACK *out = new TREE_STACK();
            TREE_QUEUE *Q = new TREE_QUEUE();

            file_name = strtok(NULL, "\"");
            S->push(BST->tree_root);

            while (!S->empty())
            {
                TreeNode *curr = S->top();
                S->pop();

                out->push(curr);
                if (curr->getLeftNode())
                    S->push(curr->getLeftNode());
                if (curr->getRightNode())
                    S->push(curr->getRightNode());
            }

            while (!out->empty())
            {
                Q->push(out->top());
                out->pop();
            }
            boyer_moore(Q, &f_log, file_name);
            f_log << "=========================\n\n";
        }
        else if (strcmp(tmp, "SELECT") == 0)
        {
            int index = stoi(strtok(NULL, " "));

            TreeNode *inputdata = traversal_preorder(BST->tree_root, &f_log, index);
            img_path = inputdata->tree_data.f_name;
            img_path.append(".RAW");

            input_file = fopen(img_path.c_str(), "rb");
            if (input_file == NULL)
            {
                f_log << "==========ERROR==========\n700\n=========================\n";
                continue;
            }
            fread(input_data, sizeof(unsigned char), IMG_SIZE * IMG_SIZE, input_file);
            f_log << "==========SELECT==========\nSUCCESS\n========================\n\n";
        }
        else if (strcmp(tmp, "EDIT") == 0)
        {
            char *opt = strtok(NULL, " ");
            INT_STACK *S = new INT_STACK;

            if (opt[2] != NULL)
                opt[2] = 0;
            if (strcmp(opt, "-f") == 0)
            {
                for (int i = 0; i < IMG_SIZE; i++)
                {
                    for (int j = 0; j < IMG_SIZE; j++)
                        S->push(input_data[i][j]);
                }
                for (int i = 0; i < IMG_SIZE; i++)
                {
                    for (int j = 0; j < IMG_SIZE; j++)
                        output_data[i][j] = S->top();
                    S->pop();
                }
                img_path = img_path.substr(0, img_path.find('.'));
                img_path.append("_flipped.RAW");

                output_file = fopen(img_path.c_str(), "wb+");
                fwrite(output_data, sizeof(unsigned char), IMG_SIZE * IMG_SIZE, output_file);
            }
        }
    }
}