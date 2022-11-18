#include "Manager.h"
#include <fstream>
#include <string>
#include <iostream>

Manager::Manager(int bpOrder)
{
	bp = new BpTree(bpOrder);
	avl = new AVLTree;
	done = false;
}

Manager::~Manager()
{
	delete bp;
	delete avl;
	bp = nullptr;
	avl = nullptr;
	Print_vector.clear();
}

void Manager::run(const char *command_txt)
{
	//declare fsteram object
	ifstream fin;
	ofstream flog;
	ofstream error;
	fin.open(command_txt); //open command_txt
	if (fin.fail())		   //when the command file does not exist, it will be made.
	{
		error.open("command.txt");
		error.close();
		fin.open("command.txt");
	}
	flog.open("log.txt"); //open log file

	char cmd[100]; //make char variable to contain the command.

	while (!fin.eof())
	{
		fin.getline(cmd, 100);
		string input(cmd);
		char *tmp;
		tmp = strtok(cmd, " ");
		if (strcmp(tmp, "LOAD") == 0)
		{
			//when LOAD has no problem, print out success message
			if (!bp->getRoot())
			{
				if (LOAD())
				{
					flog << "=======LOAD=======" << endl;
					flog << "Success" << endl;
					flog << "==================" << endl
						 << endl;
				}
				else //else, print out error code
				{
					printErrorCode(100);
				}
			}
			else //else, print out error code
			{
				printErrorCode(100);
			}
		}
		else if (strcmp(tmp, "VLOAD") == 0)
		{
			if (avl->getRoot()) //avl's root exists
			{
				if (VLOAD()) //vload is successfully completed
				{
					flog << "========VLOAD========" << endl;
					flog << "Success" << endl;
					flog << "===================" << endl
						 << endl;
				}
				else //else, print out error code
					printErrorCode(200);
			}
			else //else, print out error code
			{
				printErrorCode(200);
			}
		}
		else if (strcmp(tmp, "ADD") == 0)
		{
			char *contents = strtok(NULL, "\0");
			if (!ADD(contents))		 //if add method is not successfully executed
				printErrorCode(300); //print error code
		}
		else if (strcmp(tmp, "SEARCH_BP") == 0)
		{
			if (bp->getRoot()) //if bp is not empty
			{
				if (FindSpace(input) == 1) //if input data is 1,
				{
					char *nameTmp = strtok(NULL, " ");
					string name(nameTmp);
					if (!SEARCH_BP(name)) //if search_bp method is not successfully completed
					{
						printErrorCode(400); //print error code
					}
				}
				else if (FindSpace(input) == 2) //else if input data are 2,
				{
					char *nameTmp1 = strtok(NULL, " ");
					char *nameTmp2 = strtok(NULL, " ");
					string name1(nameTmp1);
					string name2(nameTmp2);
					if (!SEARCH_BP(name1, name2)) //if search_bp method is not successfully completed
					{
						printErrorCode(400); //print error code
					}
				}
				else //input data is not enough or over
				{
					printErrorCode(400); //print error code
				}
			}
			else					 //bp is empty
				printErrorCode(400); //print error code
		}
		else if (strcmp(tmp, "SEARCH_AVL") == 0)
		{
			if (avl->getRoot()) //if avl is not empty
			{
				if (FindSpace(input) == 1) //if data is not proper
				{
					string name = strtok(NULL, " ");
					if (!SEARCH_AVL(name)) //if search_avl method is not successfully executed
						printErrorCode(500);
				}
				else //else print error code
					printErrorCode(500);
			}
			else //else, print error code
				printErrorCode(500);
		}
		else if (strcmp(tmp, "VPRINT") == 0)
		{
			if (avl->getRoot()) //if avl is not empty
			{
				if (FindSpace(input) == 1) //if data is not proper
				{
					char *typeTmp = strtok(NULL, " ");
					string tt(typeTmp);
					if (!VPRINT(tt)) //if vprint method is not successfully executed
					{
						printErrorCode(600); //print error code
					}
				}
				else
					printErrorCode(600); //print error code
			}
			else
				printErrorCode(600); //print error code
		}
		else if (strcmp(tmp, "PRINT_BP") == 0)
		{
			if (bp->getRoot()) //if bp is not empty
			{
				bp->Print();
			}
			else
			{
				printErrorCode(700); //print error code
			}
		}
		else if (strcmp(tmp, "EXIT") == 0)
		{
			//print success message when exit is called
			flog << "========EXIT========" << endl;
			flog << "Success" << endl;
			flog << "====================" << endl
				 << endl;
			return;
		}
		else //other input is called
		{
			printErrorCode(800); //print erro code
		}
	}
	fin.close();
	flog.close();

	error.close();
}

bool Manager::LOAD()
{
	ifstream din;
	din.open("input_data.txt"); //open input_data.txt file
	if (!din)
		return 0;
	char data[100]; //variable that would be assigned the data
	while (!din.eof())
	{
		din.getline(data, 100);
		string input(data);
		if (numofdata(input)) //detect whether number of data are enough , bigger or smaller.
			return 0;
		string name = strtok(data, " ");
		string vaccine = strtok(NULL, " ");
		string injectionTemp = strtok(NULL, " ");
		string ageTemp = strtok(NULL, " ");
		string location = strtok(NULL, " ");
		if (FindDataError(name, vaccine, injectionTemp, ageTemp, location)) //find error of the data are incorrect
			return 0;

		//declare VaccinationData to contain given data
		//and fill the data
		VaccinationData *newData = new VaccinationData;
		newData->SetUserName(name);
		newData->SetVaccineName(vaccine);
		newData->SetTimes(stoi(injectionTemp));
		newData->SetAge(stoi(ageTemp));
		newData->SetLocationName(location);

		//If there's an error during the insertion process, delete newData and return false
		if (!bp->Insert(newData))
		{
			delete newData;
			newData = nullptr;
			return 0;
		}
		//if there is vaccination completed person,
		//insert that to avl, and make done flag false
		if (bp->getDone())
		{
			VaccinationData *temp = new VaccinationData; //instatiate vaccinationdata
			temp->SetUserName(name);
			temp->SetVaccineName(vaccine);
			temp->SetAge(stoi(ageTemp));
			temp->SetLocationName(location);
			avl->Insert(temp);	//insert temp to avl
			bp->setDone(false); //bf's done is false
		}
	}
	return 1;
}

bool Manager::VLOAD()
{
	avl->GetVector(Print_vector); //get print_vector
	return 1;
}

bool Manager::ADD(char *input)
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	if (FindSpace(input) == 3) //detect error that data is not enough
	{
		string name = strtok(input, " ");
		string vaccine = strtok(NULL, " ");
		string ageTemp = strtok(NULL, " ");
		string location = strtok(NULL, " ");
		if (FindDataError(name, vaccine, ageTemp, location)) //given data is not correct
			return 0;										 //return false

		VaccinationData *newData = new VaccinationData; //instantiate vaccinationdata
		newData->SetUserName(name);
		newData->SetVaccineName(vaccine);
		newData->SetAge(stoi(ageTemp));
		newData->SetLocationName(location);
		bp->setAddOp(true);		  //set addopd true,
		if (!bp->Insert(newData)) //if insertion is not successfully completed
		{
			delete newData; //delete newData
			newData = nullptr;
			flog.close();
			bp->setOver(false); //over is false
			return 0;
		}
		if (bp->getDuplicate()) //if newdata is duplacated, delete newData
		{
			bp->setDuplicate(false);
			delete newData;
		}
		if (bp->getDone()) // if Vaccination is completed,
		{
			//instantiate vaccinationdata
			VaccinationData *temp = new VaccinationData;
			temp->SetUserName(name);
			temp->SetVaccineName(vaccine);
			temp->SetAge(stoi(ageTemp));
			temp->SetLocationName(location);
			if (vaccine == "Janssen")
				temp->SetTimes(1);
			else
				temp->SetTimes(2);
			avl->Insert(temp); //insert temp to avl
			bp->setDone(false);
		}
		//print out added data
		flog << "========ADD========" << endl;
		flog << name << " " << vaccine << " " << ageTemp << " " << location << endl;
		flog << "===================" << endl
			 << endl;
		flog.close();
		return 1;
	}
	else //else, return false
	{
		flog.close();
		return 0;
	}
}

bool Manager::SEARCH_BP(string name)
{
	BpTreeNode *result = bp->searchDataNode(name);
	ofstream flog;
	bool no = true;
	flog.open("log.txt", ios::app);
	if (result) //if there is data i find
	{
		for (auto i = result->getDataMap()->begin(); i != result->getDataMap()->end(); i++)
		{
			if (i->second->GetUserName() == name)
			{ //print out searched data
				flog << "=======SEARCH_BP=======" << endl;
				flog << i->second->GetUserName() << " " << i->second->GetVaccineName() << " " << i->second->GetTimes() << " " << i->second->GetAge() << " " << i->second->GetLocationName() << endl;
				flog << "=======================" << endl
					 << endl;
				no = false;
				break;
			}
		}
		if (no)
			return 0;
		else
			return 1;
	}
	else //else return false
		return 0;
}

bool Manager::SEARCH_BP(string start, string end)
{
	if (start.size() > 1 || end.size() > 1) //if start and end alphabet is larger than 1
		return 0;
	bool exist = false;
	BpTreeNode *cur = bp->getRoot();
	while (cur->getMostLeftChild()) //go to leaf node
	{
		cur = cur->getMostLeftChild();
	}
	while (cur)
	{
		for (auto i = cur->getDataMap()->begin(); i != cur->getDataMap()->end(); i++)
		{
			char iniTemp = i->first[0];
			if (iniTemp >= start[0] && iniTemp <= end[0]) //if there is data i find in range,
			{
				exist = true;
			}
			if (exist)
				break;
		}
		if (exist)
			break;
		cur = cur->getNext();
	}

	if (!exist)
		return 0;
	bp->SearchRange(start, end); //execute searchRange method
	return 1;
}

bool Manager::SEARCH_AVL(string name)
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	VaccinationData *temp = avl->Search(name);
	if (temp)
	{ //print data i find
		flog << "======= SEARCH_AVL =======" << endl;
		flog << temp->GetUserName() << " " << temp->GetVaccineName() << " " << temp->GetTimes() << " " << temp->GetAge() << " " << temp->GetLocationName() << endl;
		flog << "==========================" << endl
			 << endl;
		return 1;
	}
	else
		return 0;
}

bool Compare(VaccinationData *vac1, VaccinationData *vac2)
{
}

bool Manager::VPRINT(string type_)
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	if (type_ == "A")
	{
		//sort vector by type A
		sort(Print_vector.begin(), Print_vector.end(), typeA);
		//print vector
		flog << "======= VPRINT A =======" << endl;
		for (int i = 0; i < Print_vector.size(); i++)
		{
			flog << Print_vector[i]->GetUserName() << " " << Print_vector[i]->GetVaccineName() << " " << Print_vector[i]->GetTimes() << " " << Print_vector[i]->GetAge() << " " << Print_vector[i]->GetLocationName() << endl;
		}
		flog << "========================" << endl
			 << endl;
		return 1;
	}
	else if (type_ == "B")
	{
		//sort vector by type B
		sort(Print_vector.begin(), Print_vector.end(), typeB);
		//print vector
		flog << "======= VPRINT B =======" << endl;
		for (int i = 0; i < Print_vector.size(); i++)
		{
			flog << Print_vector[i]->GetUserName() << " " << Print_vector[i]->GetVaccineName() << " " << Print_vector[i]->GetTimes() << " " << Print_vector[i]->GetAge() << " " << Print_vector[i]->GetLocationName() << endl;
		}
		flog << "========================" << endl
			 << endl;
		return 1;
	}
	else		  //if input is not correct
		return 0; //return false
}

void Manager::printErrorCode(int n)
{
	ofstream fout;
	fout.open("log.txt", ofstream::app); //open log.txt file
	fout << "========== ERROR ==========" << endl;
	fout << n << endl;
	fout << "===========================" << endl
		 << endl;
	fout.close();
}

bool Manager::typeA(VaccinationData *a, VaccinationData *b)
{
	string tempA(a->GetVaccineName());
	string tempB(b->GetVaccineName());
	//make a lowercase
	for (int i = 0; i < tempA.size(); i++)
	{
		tempA[i] = tolower(tempA[i]);
	}
	//make b lowercase
	for (int i = 0; i < tempB.size(); i++)
	{
		tempB[i] = tolower(tempB[i]);
	}
	if (tempA == tempB) //if vaccinations equal
	{
		if (a->GetAge() == b->GetAge()) //if ages equal
		{
			string tempC(a->GetVaccineName());
			string tempD(b->GetVaccineName());
			//make c lowercase
			for (int i = 0; i < tempC.size(); i++)
			{
				tempC[i] = tolower(tempC[i]);
			}
			//make d lowercase
			for (int i = 0; i < tempD.size(); i++)
			{
				tempD[i] = tolower(tempD[i]);
			}
			return tempC < tempD; //ascending order
		}
		return a->GetAge() < b->GetAge(); //ascending order
	}
	return tempA < tempB; //ascending order
}

bool Manager::typeB(VaccinationData *a, VaccinationData *b)
{
	string tempA(a->GetLocationName());
	string tempB(b->GetLocationName());
	//make a lowercase
	for (int i = 0; i < tempA.size(); i++)
	{
		tempA[i] = tolower(tempA[i]);
	}
	//make b lowercase
	for (int i = 0; i < tempB.size(); i++)
	{
		tempB[i] = tolower(tempB[i]);
	}
	if (tempA == tempB) //if locations equal
	{
		if (a->GetAge() == b->GetAge()) //if ages equal
		{
			string tempC(a->GetUserName());
			string tempD(b->GetUserName());
			//make c lowercase
			for (int i = 0; i < tempC.size(); i++)
			{
				tempC[i] = tolower(tempC[i]);
			}
			//make d lowercase
			for (int i = 0; i < tempD.size(); i++)
			{
				tempD[i] = tolower(tempD[i]);
			}
			return tempC < tempD; //ascending order
		}
		return a->GetAge() > b->GetAge(); //descending order
	}
	return tempA < tempB; //ascending order
}

int Manager::FindSpace(string cmd)
{
	int count = 0;
	bool error = false;
	for (int i = 0; i < cmd.size(); i++)
	{
		if (cmd[i] == ' ')
			count++;
		if (cmd[i] == ' ' && cmd[i + 1] == ' ')
			error = true;
		if (error)
			break;
	}
	if (error)
		return -1;
	return count;
}

bool Manager::numofdata(string cmd) //when LOAD method is executed and there are not enough number of data.
{									// return false;
	int i = 0, count = 0;
	bool error = false;

	while (i < cmd.size())
	{
		if (4 == count) //if there are enough data, error is false
			error = false;
		if (cmd[i] == ' ') //if it is white stace word, increase count
		{
			error = false;
			count++;
		}

		if ((cmd[i] == ' ' && cmd[i + 1] == ' ') || 4 < count) //if there are succeeding white space words or number of space words is bigger than 4
		{													   //error is true
			error = true;
			break;
		}
		i++;
	}
	if (4 != count) //when there are not enough data, error is true
		error = true;
	return error;
}

bool Manager::FindDataError(string name, string vaccine, string age, string location)
{
	int i = 0;
	//check the name is proper
	while (i < name.size())
	{
		if ((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'))
		{
			i++;
		}
		else
			return true;
	}
	i = 0;
	//check the vaccine is proper
	while (i < vaccine.size())
	{
		if ((vaccine[i] >= 'a' && vaccine[i] <= 'z') || (vaccine[i] >= 'A' && vaccine[i] <= 'Z'))
		{
			i++;
		}
		else
			return true;
	}
	i = 0;
	//check the age data is proper
	while (i < age.size())
	{
		if ((age[i] >= '0' && age[i] <= '9'))
		{
			i++;
		}
		else
			return true;
	}
	i = 0;
	//check the location is proper
	while (i < location.size())
	{
		if ((location[i] >= 'a' && location[i] <= 'z') || (location[i] >= 'A' && vaccine[i] <= 'Z'))
		{
			i++;
		}
		else
			return true;
	}
	return false;
}
bool Manager::FindDataError(string name, string vaccine, string inj, string age, string location)
{
	int i = 0;
	//check the name data is proper
	while (i < name.size())
	{
		if ((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'))
		{
			i++;
		}
		else
			return true;
	}
	i = 0;
	//check the vaccine data is proper
	while (i < vaccine.size())
	{
		if ((vaccine[i] >= 'a' && vaccine[i] <= 'z') || (vaccine[i] >= 'A' && vaccine[i] <= 'Z'))
		{
			i++;
		}
		else
			return true;
	}
	i = 0;
	//check the injection data is proper
	while (i < inj.size())
	{
		if ((inj[i] >= '0' && inj[i] <= '9'))
		{
			i++;
		}
		else
			return true;
	}
	i = 0;
	//check the age data is proper
	while (i < age.size())
	{
		if ((age[i] >= '0' && age[i] <= '9'))
		{
			i++;
		}
		else
			return true;
	}
	i = 0;
	//check the location data is proper
	while (i < location.size())
	{
		if ((location[i] >= 'a' && location[i] <= 'z') || (location[i] >= 'A' && vaccine[i] <= 'Z'))
		{
			i++;
		}
		else
			return true;
	}
	return false;
}
