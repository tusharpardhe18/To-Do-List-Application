#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
using namespace std;

struct todolist{
    int id;
    string task;   
};

int ID;

void banner(){
    cout << "\t************************************" << endl;
    cout << "\t*                                   *" << endl;
    cout << "\t*                                   *" << endl;
    cout << "\t*                                   *" << endl;
    cout << "\t*                                   *" << endl;
    cout << "\t*           My ToDo List            *" << endl;
    cout << "\t*                                   *" << endl;
    cout << "\t*                                   *" << endl;
    cout << "\t*                                   *" << endl;
    cout << "\t*                                   *" << endl;
    cout << "\t************************************" << endl;

}

void addTask(){
    system("cls");
    banner();
    todolist todo;
    cout << "Enter new task : " << endl;
    cin.get();
    getline(cin , todo.task);
    char save;
    cout << "Do you want to save this task ? (y/n) : " << endl;
    cin >> save;
    if(save == 'y' || save == 'Y'){
        ID++;
        //cout << "Task saved successfully" << endl;
        ofstream fout;
        fout.open("todo.txt", ios::app);
        fout << "\n" << ID;
        fout << "\n" << todo.task;
        fout.close();

        char more;
        cout << "Add more task? (y/n) : ";
        cin >> more;

        if(more == 'y' || more == 'Y'){
            addTask();
        }
        else{
            system("cls");
            cout << "\tAdded successfully!!!" << endl;
            return;
        }
    }
    system("cls");
}

void showTask(){
    system("cls");
    banner();
    todolist todo;
    ifstream fin;
    fin.open("todo.txt");
    cout << "Task : " << endl;
    while(!fin.eof()){
        fin >> todo.id;
        fin.ignore();
        getline(fin , todo.task);
        if(todo.task != ""){
            cout << "\t" << todo.id << " : " << todo.task << endl;
        }   
        else{
            cout << "\tEmpty!" << endl;
        }
    }
    fin.close();
    char exit;
    cout << "Exit? (y/n) : " ;
    cin >> exit;
    if(exit != 'y'){
        showTask();
    }
    system("cls");
}

int searchTask(){
    system("cls");
    banner();
    todolist todo;
    int id;
    cout << "Enter the task id : ";
    cin >> id;
    ifstream fin;
    fin.open("todo.txt");
    while(!fin.eof()){
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if(todo.id == id){
            system("cls");
            cout<< "\t" << todo.id << ": " << todo.task <<endl;
            return 0;
        }
    }
    system("cls");
    cout << "\tTask not found!" << endl;
    return 0;
}

void deleteTask(){
    system("cls");
    int idnum = searchTask();
    if( idnum != 0){
        char del;
        cout << "\tDelete? (y/n) : ";
        cin >> del;
        if( del == 'y' ){
            todolist todo;
            ofstream tempFile;
            tempFile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");
            int index = 1;
            while(!fin.eof()){
        		fin >> todo.id;
        		fin.ignore();
        		getline(fin, todo.task);
        		if(todo.id != idnum){
            		tempFile << "\n" << index;
                    tempFile << "\n" << todo.task;
                    index++;
                    ID--;
        		}
    		}
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt","todo.txt");
    		system("cls");
            cout << "\n\tDeleted Successfully!!!" << endl;
    		return;
        }
        else{
            system("cls");
            cout << "Not Deleted!!!" << endl;
            
        }
    }
    system("cls");
    return;
}
//void editTask();

int main(){
    system("cls");
    while(true){
        banner();
        cout<<"\n\t1. Add Task"<<endl;
        cout<<"\n\t2. Show Task"<<endl;
        cout<<"\n\t3. Search Task"<<endl;
        cout<<"\n\t4. Delete Task"<<endl;

        int choice;
        cout<<"\n\tEnter Choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                addTask();
                break;
            case 2:
                showTask();
                break;
            case 3:
                searchTask();
                break;
            case 4:
                deleteTask();
                break;
            default:
                break;  
        }
    }
    return 0;
}

