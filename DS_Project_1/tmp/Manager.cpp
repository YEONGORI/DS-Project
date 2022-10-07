#include "Manager.h"
#include <cstring>
#include <iostream>
#include <string.h>
#include <string>
#include "BinarySearchTree.h"
#include "TreeManager.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();
}

void Manager::Run(const char *filepath)
{
    fout.open(RESULT_LOG_PATH);
    fin.open("command.txt");
    fdata.open("filesnumbers.csv");

    char cmd[100];
    if (filepath)
        cout << "";
    Loaded_LIST *LIST = new Loaded_LIST;
    BinarySearchTree *BST = new BinarySearchTree;

    char data_path[100] = {};

    unsigned char input_data[512][512];
    unsigned char output_data[512][512];

    FILE *input_file, *output_file;

    while (!fin.eof())
    {
        // Read the command
        fin.getline(cmd, 100);
        char *tmp = strtok(cmd, " ");
        cout << tmp << '\n';

        if (strcmp(tmp, "LOAD") == 0)
        {
            ROW_LIST *R_LIST = new ROW_LIST;

            fout << "=========LOAD=========" << endl;
            if (!fdata)
            {
                fout << "========ERROR========\n100\n====================" << endl;
                break;
            }
            int byte3_int = 0;
            while (!fdata.eof())
            {
                char buffer[100];
                char *raw1, *raw2;

                if (!fdata.getline(buffer, sizeof(buffer)))
                    break;

                if (byte3_int == 0)
                {
                    string byte3 = buffer;
                    byte3 = byte3.substr(3);
                    for (int j = 0; j < byte3.length(); j++)
                    {
                        buffer[j] = byte3[j];
                    }
                    byte3_int++;
                }

                raw1 = strtok(buffer, ",");
                raw2 = strtok(NULL, "\n");

                int i;
                for (i = 0; raw2[i]; i++)
                    ;
                raw2[i - 1] = '\0';
                string r1 = raw1; // r1 = 고유번호
                string r2 = raw2; // 파일 이름
                if (R_LIST->size >= 100)
                {
                    R_LIST->QueuePop();
                    cout << "check" << endl;
                }
                R_LIST->QueuePush(r2, "images", r1);
                fout << r2 << "/";
                fout << r1 << endl;
            }
            LIST->QueuePush(R_LIST);

            fout << "=================\n"
                 << endl;
        }
        else if (strcmp(tmp, "ADD") == 0)
        {
            ROW_LIST *rowlist = new ROW_LIST;

            char path[100] = {0};
            char *dir = strtok(NULL, " ");
            char *file = strtok(NULL, " ");
            if (dir == NULL || file == NULL)
            {
                fout << "========ERROR========\n200\n====================\n"
                     << endl;
            }
            strcat(path, dir);
            strcat(path, "/");
            strcat(path, file);

            int i;
            for (i = 0; path[i]; i++)
                ;
            path[i - 1] = 0;

            ndata.open("new_filenumbers.csv");

            while (!ndata.eof())
            {
                char raw1[100], raw2[100];

                if (!ndata.getline(raw1, sizeof(raw1), ','))
                    break;
                ndata.getline(raw2, sizeof(raw2), '\n');

                string r1 = raw1;
                string r2 = raw2;

                /*if (rowlist->size >= 100)
                {
                    rowlist->QueuePop();
                }*/
                if (LIST->isEmpty())
                {
                    fout << "========ERROR========\n200\n====================\n"
                         << endl;
                }
                rowlist->QueuePush(r2, dir, r1);
            }
            LIST->QueuePush(rowlist);
            fout << "=======ADD========\nSUCCESS\n===================\n"
                 << endl;
        }
        else if (strcmp(tmp, "MODIFY") == 0)
        {
            char *dir = strtok(NULL, " ");   // dir
            char *file = strtok(NULL, "\""); // file
            char *index = strtok(NULL, " "); // index
            if (dir == NULL || file == NULL || index == NULL)
            {
                fout << "========ERROR========\n300\n====================\n"
                     << endl;
                continue;
            }
            Node *curNode = LIST->start_list->first;
            ROW_LIST *curRowList = LIST->start_list;
            bool dir_case = false;
            bool file_case = false;
            while (curNode->dir != dir)
            {
                curRowList = curRowList->down;
                if (curRowList == NULL)
                {
                    fout << "========ERROR========\n300\n====================\n"
                         << endl;
                    dir_case = true;
                    break;
                }
                curNode = curRowList->first;
            }
            if (dir_case)
                continue;
            while (curNode->file != file)
            {
                curNode = curNode->back;
                if (curNode == NULL)
                {
                    fout << "========ERROR========\n300\n====================\n"
                         << endl;
                    file_case = true;
                    break;
                }
            }
            if (file_case)
                continue;
            Node *frontNode;
            Node *backNode;
            frontNode = curNode->front;
            backNode = curNode->back;
            frontNode->back = backNode;
            backNode->front = frontNode;
            delete curNode;
            curRowList->QueuePush(file, dir, index);
            fout << "=======MODIFY========\nSUCCESS\n====================\n"
                 << endl;
        }
        else if (cmd[0] == 'M' && cmd[1] == 'O' && cmd[2] == 'V' && cmd[3] == 'E')
        {
            if (LIST->isEmpty())
            {
                fout << "========ERROR========\n400\n====================\n"
                     << endl;
                continue;
            }
            // new_files가 있는지 없는지 찾기
            // 찾으면 그거부LI터 옮기고 삭제
            // 다 옮기면 img_files에 있는거 옮기고 삭제
            ROW_LIST *StartList = LIST->end_list;
            int low_index = 10000;
            while (StartList != NULL)
            {
                Node *StartNode = StartList->last;
                while (StartNode != NULL)
                {
                    Node *TmpNode = new Node("", "", "", NULL, NULL);
                    if (BST->size > 300)
                    { // 300개 넘으면
                        TreeNode *curTreeNode = BST->m_root;

                        while (curTreeNode->m_left)
                        { //왼쪽 끝 노드로 이동
                            curTreeNode = curTreeNode->m_left;
                        }

                        low_index = curTreeNode->m_data.unique_number; //가장 작은 고유번호 구함
                        cout << curTreeNode->m_data.unique_number << endl;
                        BST->deletion(low_index); // 삭제
                        cout << curTreeNode->m_data.unique_number << "abc" << endl;
                        BST->size--;
                    }

                    BST->insert(StartNode);
                    TmpNode = StartNode;
                    StartNode = StartNode->front;
                    delete (TmpNode);
                }
                StartList = StartList->up;
            }
            cout << BST->m_root->getLeftNode() << "\n\n";
        }
        else if (strcmp(tmp, "PRINT") == 0)
        {
            if (!BST->m_root)
            {
                fout << "========ERROR========\n500\n====================\n"
                     << endl;
                continue;
            }
            fout << "=======PRINT================" << endl;

            BST->print_inorder(BST->m_root, &fout);

            fout << "===========================\n"
                 << endl;
        }
        else if (strcmp(tmp, "SEARCH") == 0)
        {
            if (BST->m_root->m_data.unique_number == NULL)
            {
                fout << "========ERROR========\n600\n====================\n"
                     << endl;
                continue;
            }

            fout << "=======SEARCH===============\n";

            char *filename = strtok(NULL, "\"");
            string file_name = filename;

            MiniStack *s = new MiniStack();
            s->push(BST->m_root);
            MiniStack *out = new MiniStack();

            while (!s->empty())
            {
                TreeNode *curr = s->peek();
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

            Queue *q = new Queue;

            while (!out->empty())
            { //큐 넣기
                q->push(out->peek());
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
                        fout << "\"" << q->top()->m_data.m_name << "\" / " << q->top()->m_data.unique_number << endl;
                }

                q->pop();
            }
            fout << "======================\n"
                 << endl;
        }

        else if (strcmp(tmp, "SELECT") == 0)
        {
            char *tmp = strtok(NULL, " ");
            string tmp_num = tmp;
            int tmp_number = stoi(tmp_num);

            TreeNode *inputdata = BST->print_preorder(BST->m_root, &fout, tmp_number);

            // rawreader
            int width = 512, height = 512;

            strcpy(data_path, inputdata->m_data.m_name.c_str());
            strcat(data_path, ".RAW");
            // raw 파일 읽어오기
            input_file = fopen(data_path, "rb");
            if (input_file == NULL)
            {
                fout << "========ERROR========\n700\n====================\n"
                     << endl;
                return;
            }
            fread(input_data, sizeof(unsigned char), width * height, input_file);
            fout << "=======SEARCH===============\n";
            fout << "SUCCESS" << endl;
            fout << "======================\n"
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
                        output_data[i][j] = s->peek();
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