#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>

#include "Manager.h"
#include "Queue.h"
#include "Stack.h"
#include "TreeManager.h"
#include "BinarySearchTree.h"

#define BUFF_SIZE 128
#define HEIGHT 6000
#define WIDTH 16

using namespace std;

Manager::~Manager()
{
    if (f_log.is_open())
        f_log.close();
}

void Manager::Run(const char *filepath)
{
    f_log.open(RESULT_LOG_PATH); // file open
    f_cmd.open("command.txt");
    f_file.open("img_files/filesnumbers.csv");

    Loaded_LIST *LIST = new Loaded_LIST; // total list
    Database_BST *BST = new Database_BST;

    FILE *input_file, *output_file;

    string img_path;

    int list_size = 0, bst_size = 0, file_size = 0;
    char cmd[BUFF_SIZE] = {};

    unsigned char input_data[HEIGHT][WIDTH];
    unsigned char output_data[HEIGHT][WIDTH];

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
            f_log << "==========LOAD==========\n";
            if (!f_file)
            {
                f_log << "==========ERROR==========\n100\n=========================\n";
                continue;
            }

            ROW_LIST *NEW_LIST = new ROW_LIST;
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
                if (list_size > 100)
                {
                    NEW_LIST->PopNode();
                    list_size--;
                }

                NEW_LIST->PushNode(file_name, "img_files", index);
                list_size++;
                f_log << file_name << "/" << index << '\n';
            }
            LIST->PushList(NEW_LIST);
            f_log << "========================\n\n";
        }
        else if (strcmp(tmp, "ADD") == 0)
        {
            string path, d_name, f_name;
            if (list_size == 0)
                f_log << "==========ERROR==========\n200\n=========================\n";
            d_name = strtok(NULL, " ");
            if (d_name.empty())
            {
                f_log << "==========ERROR==========\n200\n=========================\n";
                continue;
            }
            f_name = strtok(NULL, "\n");
            if (f_name.empty())
            {
                f_log << "==========ERROR==========\n200\n=========================\n";
                continue;
            }
            path.append(d_name).append("/").append(f_name);
            path.erase(path.find(13));

            f_new.open(path);
            ROW_LIST *NEW_LIST = new ROW_LIST;
            while (!f_new.eof())
            {
                char buff[BUFF_SIZE];
                string index, file_name;

                if (!f_new.getline(buff, BUFF_SIZE))
                    break;
                index = strtok(buff, ",");
                file_name = strtok(NULL, "\n");
                file_name.erase(file_name.find(13));

                if (list_size > 100)
                {
                    NEW_LIST->PopNode();
                    list_size--;
                }
                NEW_LIST->PushNode(file_name, d_name, index);
                list_size++;
            }
            LIST->PushList(NEW_LIST);
            f_log << "==========ADD===========\nSUCCESS\n========================\n\n";
        }
        else if (strcmp(tmp, "MODIFY") == 0)
        {
            string d_name, f_name, index;
            Loaded_LIST_Node *cur_node = LIST->top_list->edge_left;
            Loaded_LIST_Node *tmp_node;
            ROW_LIST *CUR_LIST = LIST->top_list;

            d_name = strtok(NULL, " ");
            if (d_name.empty())
            {
                f_log << "==========ERROR==========\n300\n=========================\n";
                continue;
            }
            f_name = strtok(NULL, "\"");
            if (f_name.empty())
            {
                f_log << "==========ERROR==========\n300\n=========================\n";
                continue;
            }
            index = strtok(NULL, " ");
            if (index.empty())
            {
                f_log << "==========ERROR==========\n300\n=========================\n";
                continue;
            }

            while (cur_node->dir_name != d_name)
            {
                CUR_LIST = CUR_LIST->go_down;
                if (CUR_LIST == NULL)
                    break;
                cur_node = CUR_LIST->edge_left;
            }
            if (CUR_LIST == NULL)
            {
                f_log << "==========ERROR==========\n300\n=========================\n";
                continue;
            }

            while (cur_node->file_name != f_name)
            {
                cur_node = cur_node->next;
                if (cur_node == NULL)
                    break;
            }
            if (cur_node == NULL || cur_node->index == index)
            {
                f_log << "==========ERROR==========\n300\n=========================\n";
                continue;
            }

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
            if (list_size == 0)
            {
                f_log << "==========ERROR==========\n400\n=========================\n";
                continue;
            }

            int low_index = BUFF_SIZE * BUFF_SIZE;
            ROW_LIST *START_LIST = LIST->bottom_list;
            while (START_LIST != NULL)
            {
                Loaded_LIST_Node *start_node = START_LIST->edge_right;
                while (start_node != NULL)
                {
                    if (bst_size > 300)
                    {
                        Database_BST_Node *cur_tree_node = BST->tree_root;

                        while (cur_tree_node->tree_left) //왼쪽 끝 노드로 이동
                            cur_tree_node = cur_tree_node->tree_left;
                        low_index = cur_tree_node->tree_data->index; //가장 작은 고유번호 구함
                        BST->deletion(low_index);                    // 삭제
                        bst_size--;
                    }
                    Loaded_LIST_Node *tmp_node = new Loaded_LIST_Node("", "", "", NULL, NULL);

                    BST->insert(start_node);
                    bst_size++;
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
            if (bst_size == 0)
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
            string file_name = strtok(NULL, "\"");
            if (file_name.empty() || bst_size == 0)
            {
                f_log << "==========ERROR==========\n600\n=========================\n";
                continue;
            }
            f_log << "=========SEARCH==========\n";

            STACK<Database_BST_Node> *S = new STACK<Database_BST_Node>();
            STACK<Database_BST_Node> *temp = new STACK<Database_BST_Node>();
            QUEUE<Database_BST_Node> *Q = new QUEUE<Database_BST_Node>();

            temp->push(*BST->tree_root);

            while (!temp->empty())
            {
                Database_BST_Node curr = temp->top();
                temp->pop();

                S->push(curr);
                if (curr.getLeftNode())
                    temp->push(*curr.getLeftNode());
                if (curr.getRightNode())
                    temp->push(*curr.getRightNode());
            }

            while (!S->empty())
            {
                Q->push(S->top());
                S->pop();
            }
            boyer_moore(Q, &f_log, file_name);
            f_log << "=========================\n\n";
        }
        else if (strcmp(tmp, "SELECT") == 0)
        {
            char *temp = strtok(NULL, " ");
            if (temp == NULL)
            {
                f_log << "==========ERROR==========\n700\n=========================\n";
                continue;
            }
            int index = stoi(temp);

            Database_BST_Node *bst_node = traversal_preorder(BST->tree_root, &f_log, index);
            img_path = "img_files/";
            img_path = img_path.append(bst_node->tree_data->file_name);
            img_path.append(".RAW");

            input_file = fopen(img_path.c_str(), "rb");
            if (input_file == NULL)
            {
                f_log << "==========ERROR==========\n700\n=========================\n";
                continue;
            }
            fread(input_data, sizeof(unsigned char), HEIGHT * WIDTH, input_file);
            f_log << "==========SELECT==========\nSUCCESS\n==========================\n\n";
        }
        else if (strcmp(tmp, "EDIT") == 0)
        {
            char *opt = strtok(NULL, " ");
            string img_path_origin = img_path;

            memset(output_data, 0, HEIGHT * WIDTH);
            if (opt[2] != '\0')
                opt[2] = 0;
            if (strcmp(opt, "-f") == 0)
            {
                STACK<int> *S = new STACK<int>();
                for (int i = 0; i < HEIGHT; i++)
                {
                    for (int j = 0; j < WIDTH; j++)
                        S->push(input_data[i][j]);
                }
                for (int i = 0; i < HEIGHT; i++)
                {
                    for (int j = 0; j < WIDTH; j++)
                    {
                        output_data[i][j] = S->top();
                        S->pop();
                    }
                }
                img_path_origin = img_path_origin.substr(0, img_path_origin.find('.'));
                img_path_origin.append("_flipped.RAW");

                output_file = fopen(img_path_origin.c_str(), "wb+");
                fwrite(output_data, sizeof(unsigned char), HEIGHT * WIDTH, output_file);
            }
            else if (strcmp(opt, "-l") == 0)
            {
                string temp = strtok(NULL, " ");
                if (temp.empty())
                {
                    f_log << "==========ERROR==========\n900\n=========================\n";
                    continue;
                }
                int val = stoi(temp.erase(temp.find(13))); // value
                QUEUE<char> *Q = new QUEUE<char>();
                for (int i = 0; i < HEIGHT; i++)
                {
                    for (int j = 0; j < WIDTH; j++)
                        Q->push(input_data[i][j]);
                }
                for (int i = 0; i < HEIGHT; i++)
                {
                    for (int j = 0; j < WIDTH; j++)
                    {
                        int pix = Q->top() + val;
                        if (pix >= 255)
                            output_data[i][j] = 255;
                        else
                            output_data[i][j] = pix;
                        Q->pop();
                    }
                }
                img_path = img_path.substr(0, img_path.find('.'));
                img_path.append("_flipped.RAW");

                img_path_origin = img_path_origin.substr(0, img_path_origin.find('.'));
                img_path_origin.append("_adjusted.RAW");

                output_file = fopen(img_path_origin.c_str(), "wb+");
                fwrite(output_data, sizeof(unsigned char), HEIGHT * WIDTH, output_file);
            }
            else if (strcmp(opt, "-r") == 0)
            {
                for (int i = 0; i < HEIGHT; i += 2)
                {
                    for (int j = 0; j < WIDTH; j += 2)
                        output_data[i / 2][j / 2] = (input_data[i][j] + input_data[i][j + 1] + input_data[i + 1][j] + input_data[i + 1][j + 1]) / 4;
                }

                img_path_origin = img_path_origin.substr(0, img_path_origin.find('.'));
                img_path_origin.append("_resized.RAW");

                output_file = fopen(img_path_origin.c_str(), "wb+");
                fwrite(output_data, sizeof(unsigned char), (HEIGHT / 2) * (WIDTH / 2), output_file);
            }
            f_log << "===========EDIT===========\nSUCCESS\n==========================\n\n";
        }
        else if (strcmp(tmp, "EXIT") == 0)
        {
            delete LIST;
            delete BST;
            f_log << "===========EXIT===========\nSUCCESS\n==========================\n\n";
        }
        else
        {
            f_log << "==========ERROR==========\n777\n=========================\n";
        }
    }
}