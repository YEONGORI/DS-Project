#include "BpTree.h"
bool BpTree::Insert(VaccinationData *newData)
{
    if (!root) // there is no data,
    {
        BpTreeDataNode *input = new BpTreeDataNode;            // declare input
        input->insertDataMap(newData->GetUserName(), newData); // and insert it in data map.
        root = input;                                          // root is input
        return 1;                                              // return true
    }
    if (dup(newData)) // check there are duplicated person.
    {
        setDuplicate(true); // duplicate flag is true
        return 1;           // return true
    }
    if (over) // if over insertion is occured, return false"
        return 0;
    if (AddOp) // if insertion is occured by add operation,
    {
        newData->SetTimes(1); // increase injection times
        AddOp = false;
        if (newData->GetVaccineName() == "Janssen") // if it is Janssen, it is completed vaccination
            done = true;                            // done is true
    }

    BpTreeNode *temp = Find_Root(root, newData->GetUserName()); // find the place that would insert
    temp->insertDataMap(newData->GetUserName(), newData);       // insert Data to index

    if (exceedDataNode(temp)) // if temp has 3 priciples
    {
        splitDataNode(temp); // execute the method
    }
    return 1;
}

BpTreeNode *BpTree::searchDataNode(string name)
{
    BpTreeNode *cur = root;
    while (cur)
    {
        if (!cur->getMostLeftChild())
            return cur;
        string target = cur->getIndexMap()->begin()->first;
        auto end = cur->getIndexMap()->end();
        end--;
        if (name > target || target == name) // if name is same or bigger than targer
        {
            BpTreeNode *sec;
            if (name > end->first || name == end->first) // if name is smae or bigger than end
            {
                sec = end->second;
            }
            else
                sec = cur->getIndexMap()->begin()->second;
            cur = sec;
        }
        else // else go MLC
        {
            cur = cur->getMostLeftChild();
        }
    }
}

void BpTree::splitDataNode(BpTreeNode *pDataNode)
{
    BpTreeNode *newNode = new BpTreeDataNode;          // instantiate newNode
    auto temp = pDataNode->getDataMap()->begin();      // assign first principle of pData's map to temp
    newNode->insertDataMap(temp->first, temp->second); // inset temp's second to newNode's map as temp's first
    temp++;                                            // point next of temp
    if (!pDataNode->getParent())
    {
        BpTreeNode *newRoot = new BpTreeIndexNode;                        // instantiate newRoot
        newRoot->insertIndexMap(temp->first, pDataNode);                  // insert pDataNode to newRoot's map as temp's first
        newRoot->setMostLeftChild(newNode);                               // set newNode to newRoot's MLC
        pDataNode->getDataMap()->erase(pDataNode->getDataMap()->begin()); // delete first principle of pdata's map
        newNode->setNext(pDataNode);                                      // newNode -> pDataNode
        pDataNode->setPrev(newNode);                                      // newNode <- pDataNode
        pDataNode->setParent(newRoot);                                    // set newRoot to pData's parent
        newNode->setParent(newRoot);                                      // set newRoot to newNode's parent
        root = newRoot;                                                   // assign newRoot to root
        return;
    }

    BpTreeNode *parent = pDataNode->getParent();                      // assign pDataNode's parent to parent
    parent->insertIndexMap(temp->first, pDataNode);                   // insert pDatanode to parent's map as temp's first
    pDataNode->getDataMap()->erase(pDataNode->getDataMap()->begin()); // delete first principle of pdata's map
    if (parent->getMostLeftChild() == pDataNode)                      // if parent's MLC equals pData
    {
        parent->setMostLeftChild(newNode); // set newNode as parent's MLC
        newNode->setParent(parent);        // set parent to newNode's parent
    }
    else
    {
        for (auto i = parent->getIndexMap()->begin(); i != parent->getIndexMap()->end(); i++)
        {
            if (i->second == pDataNode) // if current priciple equals target node
            {
                i->second = newNode;        // assign  newNode to current priciple's second
                newNode->setParent(parent); // set parent
                break;
            }
        }
    }
    if (pDataNode->getPrev()) // if pData has prev
    {
        pDataNode->getPrev()->setNext(newNode); // set next of pData's prev to newNode
        newNode->setPrev(pDataNode->getPrev()); // set Data's prev to new Prev
    }
    pDataNode->setPrev(newNode); // pData's prev is set as newNode
    newNode->setNext(pDataNode); // newNode's next is set as pDataNode

    if (exceedIndexNode(parent)) // if parent has 3 priciples,
    {
        splitIndexNode(parent); // execute splitIndexNode
    }
}

void BpTree::splitIndexNode(BpTreeNode *pIndexNode)
{
    BpTreeNode *newNode = new BpTreeIndexNode;                            // instantiate newNode
    auto temp = pIndexNode->getIndexMap()->begin();                       // temp is assigned as first principle of pIndexNode's map
    newNode->insertIndexMap(temp->first, temp->second);                   // insert temp's second to newNode's map
    temp->second->setParent(newNode);                                     // set temp's second to newNode
    newNode->setMostLeftChild(pIndexNode->getMostLeftChild());            // set newNode's MLC to pIndex's
    pIndexNode->getMostLeftChild()->setParent(newNode);                   // set parent pIndex's MLC to newNode
    temp++;                                                               // point next of temp
    pIndexNode->getIndexMap()->erase(pIndexNode->getIndexMap()->begin()); // delete first priciple of pIndex's map
    if (!pIndexNode->getParent())                                         // if it has no parent
    {
        BpTreeNode *newParent = new BpTreeIndexNode;                          // instatiate newParent
        newParent->insertIndexMap(temp->first, pIndexNode);                   // insert pIndexnode to newParent
        newParent->setMostLeftChild(newNode);                                 // newParent's MLC is set as newNode
        newNode->setParent(newParent);                                        // newNode's parent is set as newParent
        pIndexNode->setParent(newParent);                                     // set pIndexNOde to newParent
        pIndexNode->setMostLeftChild(temp->second);                           // set pIndex's MLC to temp's second
        pIndexNode->getIndexMap()->erase(pIndexNode->getIndexMap()->begin()); // delete first priciple of pIndex's map
        newNode->setParent(newParent);                                        // newNode's parent is set as newParent
        pIndexNode->setParent(newParent);                                     // set pIndexNOde to newParent
        root = newParent;                                                     // root is assigned as newParent
        return;
    }
    BpTreeNode *parent = pIndexNode->getParent();                         // assign pIndex's parent to parent
    parent->insertIndexMap(temp->first, pIndexNode);                      // insert pIndex to parent's map
    pIndexNode->setMostLeftChild(temp->second);                           // set temp's second to pIndex's MLC
    pIndexNode->getIndexMap()->erase(pIndexNode->getIndexMap()->begin()); // delete first priciple of pIndex's map
    if (parent->getMostLeftChild() == pIndexNode)                         // if parent's MLC equals pIndexNode
    {
        parent->setMostLeftChild(newNode); // assign newNode to parent's MLC
        newNode->setParent(parent);        // parent is newNode's parent
    }
    else
    {
        for (auto i = parent->getIndexMap()->begin(); i != parent->getIndexMap()->end(); i++)
        {
            if (i->second == pIndexNode) // if current priciple equals target node
            {
                i->second = newNode;        // assign  newNode to current priciple's second
                newNode->setParent(parent); // set parent
                break;
            }
        }
    }
    if (exceedIndexNode(parent)) // if parent has 3 principle
    {
        splitIndexNode(parent); // excute method
    }
}

bool BpTree::exceedDataNode(BpTreeNode *pDataNode)
{
    if (pDataNode->getDataMap()->size() > order - 1) // if dataNode's size is 3
        return 1;
    else
        return 0;
}

bool BpTree::exceedIndexNode(BpTreeNode *pIndexNode)
{
    if (pIndexNode->getIndexMap()->size() > order - 1) // if indexNode's size is 3
        return 1;
    else
        return 0;
}

void BpTree::SearchRange(string start, string end)
{
    ofstream flog;
    flog.open("log.txt", ios::app);
    BpTreeNode *cur = root;
    while (cur)
    {
        if (!cur->getMostLeftChild())
        {
            break;
        }
        string target = cur->getIndexMap()->begin()->first;
        auto end = cur->getIndexMap()->end();
        end--;
        if (start[0] > target[0] || start[0] == start[0]) // if name is same or bigger than targer
        {
            BpTreeNode *sec;
            if (start[0] > end->first[0] || start[0] == end->first[0]) // if name is smae or bigger than end
            {
                sec = end->second;
            }
            else
                sec = cur->getIndexMap()->begin()->second;
            cur = sec;
        }
        else // else go MLC
        {
            cur = cur->getMostLeftChild();
        }
    }
    flog << "=======SEARCH_BP=======" << endl;
    while (cur)
    {
        for (auto i = cur->getDataMap()->begin(); i != cur->getDataMap()->end(); i++)
        {
            char iniTemp = i->first[0];
            if (iniTemp >= start[0] && iniTemp <= end[0]) // print data in range
            {
                flog << i->first << " " << i->second->GetVaccineName() << " " << i->second->GetTimes() << " " << i->second->GetAge() << " " << i->second->GetLocationName() << " " << endl;
            }
        }
        cur = cur->getNext();
    }
    flog << "======================" << endl
         << endl;
    flog.close();
}

void BpTree::Print()
{
    ofstream flog;
    flog.open("log.txt", ios::app);
    BpTreeNode *cur = root;
    while (cur->getMostLeftChild()) // go data leaf
    {
        cur = cur->getMostLeftChild();
    }
    // print all the data in bptree
    flog << "=======PRINT_BP========" << endl;
    while (cur)
    {
        for (auto i = cur->getDataMap()->begin(); i != cur->getDataMap()->end(); i++)
        {
            flog << i->first << " " << i->second->GetVaccineName() << " " << i->second->GetTimes() << " " << i->second->GetAge() << " " << i->second->GetLocationName() << " " << endl;
        }
        cur = cur->getNext();
    }
    flog << "=======================" << endl
         << endl;
    flog.close();
}

bool BpTree::dup(VaccinationData *data)
{
    bool dup = false;
    int inj = 0;
    BpTreeNode *temp = root;
    while (temp->getMostLeftChild()) // go to leaf node
    {
        temp = temp->getMostLeftChild();
    }
    while (temp)
    {
        for (auto i = temp->getDataMap()->begin(); i != temp->getDataMap()->end(); i++)
        {
            if (i->first == data->GetUserName())
            {
                if (i->second->GetVaccineName() == "Janssen") // if it is Janssen
                {
                    if (i->second->GetTimes() == 1) // if it is completed vaccination
                    {
                        over = true; // over is true
                        return 0;    // return false
                    }
                }
                else
                {
                    if (i->second->GetTimes() == 2) // if it is completed vaccination
                    {
                        over = true; // over is true
                        return 0;    // return false
                    }
                }
                dup = true;                  // dup is true
                inj = i->second->GetTimes(); // increase injection time
                i->second->SetTimes(inj + 1);
                if (i->second->GetVaccineName() == "Janssen") // if it is janssen,
                {
                    if (i->second->GetTimes() == 1) // if it is just completed vaccination
                    {
                        done = true; // done is true
                        return 1;    // return true
                    }
                }
                else
                {
                    if (i->second->GetTimes() == 2) // if it is just completed vaccination
                    {
                        done = true; // done is true
                        return 1;    // return true
                    }
                }
                return dup; // return dup
            }
        }
        temp = temp->getNext();
    }
    return dup; // return dup
}

void BpTree::delete_all(BpTreeNode *node)
{
    queue<BpTreeNode *> list;
    BpTreeNode *temp;
    if (!root)
        return;
    list.push(root);
    // root = nullptr;
    while (!list.empty()) // excute while list is not empty
    {
        temp = list.front();
        if (!temp->getMostLeftChild())
            break;
        list.push(temp->getMostLeftChild());                                              // push list's MLC
        for (auto i = temp->getIndexMap()->begin(); i != temp->getIndexMap()->end(); i++) // push temp's childs
        {
            list.push(i->second);
        }
        temp->getIndexMap()->clear();
        delete temp; // delete indexnode
        list.pop();  // pop list's front
    }
    while (!list.empty()) // excute while list is not empty
    {
        temp = list.front();
        for (int i = temp->getDataMap()->size(); i > 0; i--)
        {
            auto end = temp->getDataMap()->end();
            end--;
            delete end->second; // delete data node's second
            end->second = nullptr;
            temp->deleteMap(end->first);
        }
        temp->getDataMap()->clear();
        delete temp; // delete data node
        temp = nullptr;
        list.pop(); // pop list's front
    }
}