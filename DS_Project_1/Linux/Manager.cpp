#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "Manager.h"
#include "Queue.h"
#include "Stack.h"
#include "TreeManager.h"
#include "BinarySearchTree.h"

#define BUFF_SIZE 100

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
    f_file.open("../Dataset/filesnumbers.csv");

    char buf[40];
    f_file.getline(buf, 10);
    cout << buf<<'\n';
    // while(1);
    

    Loaded_LIST *LIST = new Loaded_LIST;
    BinarySearchTree *BST = new BinarySearchTree;
    
    FILE *input_file, *output_file;

    char cmd[100] = {};
    char data_path[100] = {};

    unsigned char input_data[512][512];
    unsigned char output_data[512][512];

    while (!f_cmd.eof())
    {
        // Read the command
        f_cmd.getline(cmd, 100);
        char *tmp = strtok(cmd, " ");
        cout << tmp << '\n';

        if (strcmp(tmp, "LOAD") == 0)
        {
            ROW_LIST *NEW_LIST = new ROW_LIST;

            f_log << "==========LOAD==========\n";
            if(!f_log) {
                f_log << "==========ERROR==========\n100\n=========================\n";
                return ;
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
                
                NEW_LIST->PushNode(file_name, "img_files", index);
                f_log << file_name << "/" << index << '\n';
            }
            LIST->PushList(NEW_LIST);
            f_log << "========================\n";
        }
        else if (strcmp(tmp, "ADD") == 0)
        {
            ROW_LIST *NEW_LIST = new ROW_LIST;
            string path, d_name, f_name;

            d_name = strtok(NULL, " ");
            f_name = strtok(NULL, "\n");

            path.append("../Dataset/");
            path.append(d_name).append("/").append(f_name);
            path.erase(find(path.begin(), path.end(), 13));

            f_new.open(path);
            while (!f_new.eof())
            {
                char buff[BUFF_SIZE];
                string index, file_name;

                if (!f_new.getline(buff, BUFF_SIZE))
                    break;
                index = strtok(buff, ",");
                file_name = strtok(NULL, "\n");

                // if (1) 전체 리스트의 크기가 100이 넘는 경우 에러처리
                if (LIST->IsEmpty())
                    f_log << "==========ERROR==========\n100\n=========================\n";
                NEW_LIST->PushNode(file_name, d_name, index);
            }
            LIST->PushList(NEW_LIST);
            f_log << "=========ADD========\nSUCCESS\n===================\n\n";
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

            while (cur_node->dir_name != d_name) {
                CUR_LIST = CUR_LIST->go_down;
                if (CUR_LIST == NULL) {
                    f_log << "==========ERROR==========\n300\n=========================\n";
                    break;
                }
                cur_node = CUR_LIST->edge_left;
            }
            if (!CUR_LIST) continue;

            while ((cur_node->file_name != f_name) && CUR_LIST) {
                cur_node = cur_node->next;
                if (cur_node ==  NULL) {
                    f_log << "==========ERROR==========\n300\n=========================\n";
                    break;
                }
            }
            if (!cur_node) continue;

            tmp_node = cur_node->next;
            tmp_node->prev = cur_node->prev;
            cur_node->prev->next = tmp_node;
            cur_node->next->prev = tmp_node->prev;
            delete cur_node;
            CUR_LIST->PushNode(f_name, d_name, index);
            f_log << "==========MODIFY==========\nSUCCESS\n=========================\n\n";
        }
        else if (cmd[0] == 'M' && cmd[1] == 'O' && cmd[2] == 'V' && cmd[3] == 'E')
        {
            if (LIST->IsEmpty())
            {
                f_log << "==========ERROR==========\n300\n=========================\n";
                continue;
            }

            ROW_LIST *START_LIST = LIST->bottom_list;
            int low_index = 10000;
            while (START_LIST != NULL)
            {
                Node *start_node = START_LIST->edge_right;
                while (start_node != NULL)
                {
                    Node *tmp_node = new Node("", "", "", NULL, NULL);
                    if (BST->size > 300)
                    { // 300개 넘으면
                        TreeNode *cur_tree_node = BST->m_root;

                        while (cur_tree_node->m_left)
                        { //왼쪽 끝 노드로 이동
                            cur_tree_node = cur_tree_node->m_left;
                        }

                        low_index = cur_tree_node->m_data.unique_number; //가장 작은 고유번호 구함
                        cout << cur_tree_node->m_data.unique_number << endl;
                        BST->deletion(low_index); // 삭제
                        cout << cur_tree_node->m_data.unique_number << "abc" << endl;
                        BST->size--;
                    }

                    BST->insert(start_node);
                    tmp_node = start_node;
                    start_node = start_node->prev;
                    delete (tmp_node);
                }
                START_LIST = START_LIST->go_up;
            }
        }
        else if (strcmp(tmp, "PRINT") == 0)
        {
            if (!BST->m_root)
            {
                f_log << "========ERROR========\n500\n====================\n"
                     << endl;
                continue;
            }
            f_log << "=======PRINT================" << endl;

            BST->print_inorder(BST->m_root, &f_log);

            f_log << "===========================\n"
                 << endl;
        }
        else if (strcmp(tmp, "SEARCH") == 0)
        {
            if (BST->m_root->m_data.unique_number == NULL)
            {
                f_log << "========ERROR========\n600\n====================\n"
                     << endl;
                continue;
            }

            f_log << "=======SEARCH===============\n";

            char *filename = strtok(NULL, "\"");
            string file_name = filename;

            MINI_STACK *s = new MINI_STACK();
            s->push(BST->m_root);
            MINI_STACK *out = new MINI_STACK();

            while (!s->empty())
            {
                TreeNode *curr = s->top();
                s->pop();

                out->push(curr);

                if (curr->getLeftNode())
                {
                    s->push(curr->getLeftNode());
                }
                if (curr->getRightNode())
                {
                    s->push(curr->getRightNode());
                }
            }

            MINI_QUEUE *q = new MINI_QUEUE;

            while (!out->empty())
            { //큐 넣기
                q->push(out->top());
                out->pop();
            }

            while (!q->empty())
            {
                for (int i = 0; i < q->top()->m_data.m_name.length(); i++)
                {
                    int j;
                    for (j = 0; j < file_name.length(); j++)
                    {
                        if (q->top()->m_data.m_name[i + j] != file_name[j])
                            break;
                    }
                    if (j == file_name.length())
                        f_log << "\"" << q->top()->m_data.m_name << "\" / " << q->top()->m_data.unique_number << endl;
                }

                q->pop();
            }
            f_log << "======================\n"
                 << endl;
        }

        else if (strcmp(tmp, "SELECT") == 0)
        {
            char *tmp = strtok(NULL, " ");
            string tmp_num = tmp;
            int tmp_number = stoi(tmp_num);

            TreeNode *inputdata = BST->print_preorder(BST->m_root, &f_log, tmp_number);

            // rawreader
            int width = 512, height = 512;

            strcpy(data_path, inputdata->m_data.m_name.c_str());
            strcat(data_path, ".RAW");
            // raw 파일 읽어오기
            input_file = fopen(data_path, "rb");
            if (input_file == NULL)
            {
                f_log << "========ERROR========\n700\n====================\n"
                     << endl;
                return;
            }
            fread(input_data, sizeof(unsigned char), width * height, input_file);
            f_log << "=======SEARCH===============\n";
            f_log << "SUCCESS" << endl;
            f_log << "======================\n"
                 << endl;
        }

        else if (strcmp(tmp, "EDIT") == 0)
        {
            char *tmp = strtok(NULL, " ");
            int number;
            /*if (strcmp(tmp, "-l")) {
                char* tmp2 = strtok(NULL, " ");
                string num = tmp2;
                number = stoi(num);
            }*/

            IntStack *s = new IntStack;

            if (strcmp(tmp, "-f") == 0)
            {
                for (int i = 0; i < 512; i++)
                { //스택에 인풋 데이터 넣음
                    for (int j = 0; j < 512; j++)
                    {
                        s->push(input_data[i][j]);
                    }
                }

                for (int i = 0; i < 512; i++)
                { // 아웃풋 데이터에 스택 데이터 넣음
                    for (int j = 0; j < 512; j++)
                    {
                        output_data[i][j] = s->top();
                        s->pop();
                    }
                }

                char *path_tmp = data_path;
                path_tmp = strtok(data_path, ".");
                strcat(path_tmp, "_flipped");
                strcat(path_tmp, ".RAW");

                output_file = fopen(path_tmp, "wb+");
                fwrite(output_data, sizeof(unsigned char), 512 * 512, output_file);
            }
        }
        // cout << "4" << ' ';
    }

    // TODO: implement
}