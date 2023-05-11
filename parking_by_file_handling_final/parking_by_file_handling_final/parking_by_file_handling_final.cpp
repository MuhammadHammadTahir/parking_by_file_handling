#include<iostream>
#include<string.h>
#include<string>
#include<iomanip>
#include<ctime>
#include<fstream>
using namespace std;
void entry(void);
int check(string col);
void exit_c(void);
void remove(void);
void park_fee(void);
void parking_stat(void);
//int check_file(void);
void read_data(void);
void write_data(void);
struct data_c
{
	long long reg;
	string name_d;
	string vehical_b;
	string vehical_m;
	string vehical_c;
	tm entry;
	tm exit;
	string time_d;
	data_c* nptr;
};
data_c* fptr = NULL;
data_c* currentptr;
int cost_t = 0, count_c = 0;
fstream file_car;
int main()
{
	read_data();
	char op;
	while (1)
	{
		cout << "\n\n\\\\-------------------WELCOME TO PIEAS PARKING SYSTEM------------------\\\\\n\n";
		cout << "\n\n1. Vehical Entry\n2. Vehical Exit\n3. Parking Fee Collected\n4. Parking Statistics\n5. Clear Screen\n6. Exit\n";
		cout << "\n\nWhich Operation Do You Want To Perform : ";
		cin >> op;
		switch (op)
		{
		case'1':
			entry();
			break;
		case'2':
			exit_c();
			break;
		case'3':
			park_fee();
			break;
		case'4':
			parking_stat();
			break;
		case'5':
			system("CLS");
			break;
		case'6':
			write_data();
			exit(0);
			break;
		default:
			cout << "\n!!!!!!!!!!!!!You Enter the Wrong Input!!!!!!!!!!!!!!\n ";
			break;
		}
	}
}
void entry(void)
{
	int res = 0;
	data_c* ptr;
	ptr = new data_c;
	if (fptr == NULL)
	{
		cout << "Enter The Vehical Registration # : ";
		cin >> ptr->reg;
		cout << "Enter The Vehical's Driver Name : ";
		cin.clear();
		cin.ignore();
		getline(cin, ptr->name_d);
		cout << "Enter The Vehical's Brand : ";
		cin >> ptr->vehical_b;
		cout << "Enter The Vehical's Model : ";
		cin >> ptr->vehical_m;
		while (res != 1)
		{
			cout << "Enter The Vehical's Colour (White,Black,Gray,Red): ";
			cin >> ptr->vehical_c;
			res = check(ptr->vehical_c);
			if (res == 0)
			{
				cout << "\n!!!!!!!!!!Invalid colour!!!!!!!!!!!!!\n\n";
			}
		}
		time_t ctt = time(0);
		localtime_s(&ptr->entry, &ctt);
		char buffer[80];
		strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &ptr->entry);
		ptr->time_d = buffer;
		cout << "\n\n^^^^^^Vehical Is Entered^^^^^^^^\n";
		ptr->nptr = NULL;       //Add First node
		fptr = ptr;
	}
	else
	{
		data_c* move = fptr;
		while (move->nptr != NULL)
		{
			move = move->nptr;
		}
		cout << "Enter The Vehical Registration # : ";
		cin >> ptr->reg;
		cout << "Enter The Vehical's Driver Name : ";
		cin.clear();
		cin.ignore();
		cin >> ptr->name_d;
		cout << "Enter The Vehical's Brand : ";
		cin >> ptr->vehical_b;
		cout << "Enter The Vehical's Model : ";

		cin >> ptr->vehical_m;
		while (res != 1)
		{
			cout << "Enter The Vehical's Colour (White,Black,Gray,Red) : ";
			cin >> ptr->vehical_c;
			res = check(ptr->vehical_c);
			if (res == 0)
			{
				cout << "\n!!!!!!!!!!Invalid colour!!!!!!!!!!!!!\n\n";
			}
		}
		time_t ctt = time(0);
		localtime_s(&ptr->entry, &ctt);
		char buffer[80];
		strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &ptr->entry);
		ptr->time_d = buffer;
		cout << "\n\n^^^^^^Vehical Is Entered^^^^^^^^\n";
		move->nptr = ptr;
		ptr->nptr = NULL;
	}
}
int check(string col)             //this function convert the input of car colour in th elower case to check the validity
{
	int i;
	string check_c, w = "white", b = "black", r = "red", g = "gray";
	for (i = 0; i < col.length(); i++)
	{
		col[i] = tolower(col[i]);
	}
	check_c = col;
	if (check_c == w || check_c == r || check_c == b || check_c == g)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void exit_c(void)
{
	int cost = 0;
	double diff = 0.0;
	int flag = 0;
	long long reg_f;
	if (fptr == NULL)
	{
		cout << "\n\n!!!!!!!!!!!!!!There Is No Vehical!!!!!!!!!!!!!!!!";
	}
	else
	{
		currentptr = fptr;
		cout << "\n\nEnter The Registration Number Of The Vehical : ";
		cin >> reg_f;
		while (currentptr != NULL)
		{
			if (currentptr->reg == reg_f)
			{
				flag = 1;
				break;
			}
			currentptr = currentptr->nptr;
		}
		if (flag == 0)
		{
			cout << "\n\n!!!!!!!!!!!!!No Vehical In The Record Of This Registeration Number!!!!!!!!!!!!\n";
		}
		else
		{
			count_c++;
			time_t t_exit = time(0);
			localtime_s(&currentptr->exit, &t_exit);
			diff = difftime(mktime(&currentptr->exit), mktime(&currentptr->entry));       // diff() return the difference of time in seconds
			int hours = (int)diff / 3600;      //calculate the hour
			int min = (diff - (int)diff / 3600) / 60;  //calcuale the minutes
			if (diff < 60)
			{
				cost = 50;
			}
			else
			{
				cost = 70;
			}
			cost_t = cost_t + cost;
			cout << "\n\nCollect " << cost << " Rupees Amount from Car Reg No. " << currentptr->reg;
			cout << "\n\n^^^^^^^^^^Vehical Is Exited^^^^^^^^^^^";
			remove();
		}
	}
}
void remove(void)
{
	int flag = 0;
	data_c* keep;
	data_c* move = fptr;
	if (currentptr == fptr)
	{
		keep = currentptr;
		fptr = keep->nptr;
		delete currentptr;
	}
	else
	{
		while (move != NULL)
		{
			if (move->nptr == currentptr)
			{
				flag = 1;
				break;
			}
			move = move->nptr;
		}
		if (flag == 1)
		{
			keep = currentptr;
			move->nptr = keep->nptr;
			delete currentptr;
		}
	}
}
void park_fee(void)
{
	cout << "\n\nTotal Parking Fee Collected From " << count_c << " Vehicals Is : " << cost_t;
}
void parking_stat(void)
{
	if (fptr == NULL)
	{
		cout << "\n\n!!!!!!!!!!!!!!!!! There Is No Car In The Parking !!!!!!!!!!!!!!!\n";
	}
	else
	{
		data_c* move = fptr;
		cout << "\n\n";
		cout << setw(25) << left << "Vehical reg No." << setw(25) << left << "Driver Name" << setw(25) << left << "Brand" << setw(25) << left << "Model" << setw(25) << left << "Colour" << setw(25) << left << "Entry Time";
		while (move != NULL)
		{
			cout << endl;
			cout << setw(25) << left << move->reg << setw(25) << left << move->name_d << setw(25) << left << move->vehical_b << setw(25) << left << move->vehical_m << setw(25) << left << move->vehical_c << setw(25) << left << move->time_d;
			move = move->nptr;
		}
	}
}
void read_data(void)
{
	file_car.open("car_file.txt", ios::in);
	if (!file_car.is_open())
	{
		cout << "\n!!!!!!!!!!!!!!!!!!!! File failed to open !!!!!!!!!!!!!!!!!!";
		return;
	}
	string read;
	int reg;
	data_c* move = fptr;
	while (getline(file_car, read))
	{
		data_c* ptr;
		ptr = new data_c;
		reg = stoi(read);
		ptr->reg = reg;
		getline(file_car, read);
		ptr->name_d = read;
		getline(file_car, read);
		ptr->vehical_b = read;
		getline(file_car, read);
		ptr->vehical_m = read;
		getline(file_car, read);
		ptr->vehical_c = read;
		getline(file_car, read);
		ptr->time_d = read;
		if (fptr == NULL)
		{
			fptr = ptr;
			ptr->nptr = NULL;
		}
		else
		{
			move->nptr = ptr;
			ptr->nptr = NULL;
		}
		move = ptr;
	}
	file_car.close();
}

void write_data(void)
{
	string reg;
	data_c* move = fptr;
	file_car.open("car_file.txt", ios::out | ios::trunc);
	file_car.close();
	file_car.open("car_file.txt", ios::out | ios::app);
	if (!file_car)
	{
		cout << "\nFile not created\n";
	}
	else
	{
		while (move != NULL)
		{
			reg = to_string(move->reg);
			file_car << reg << endl;
			file_car << move->name_d << endl;
			file_car << move->vehical_b << endl;
			file_car << move->vehical_m << endl;
			file_car << move->vehical_c << endl;
			file_car << move->time_d << endl;
			move = move->nptr;
		}
	}
	file_car.close();
}

