﻿#include <iostream>
#include "StringBuilderClass.h"
#include "FileManagerClass.h"
#include "ClassMenu.h"
#include "StudentDBClass.h"
#include "StudentClass.h"
#include "ClassEdit.h"
#include "list.hpp"
//#include <algorithm>
using namespace std;

List<string>::iterator mMin(List <string> *_lst) {
    List<string>::iterator pos = _lst->begin();
    List<string>::iterator mMinPos = _lst->begin();
    string tmpString = *pos;
    while (pos != _lst->end()){
        if (*pos> tmpString)
            mMinPos = pos;
        ++pos;
    }
    return mMinPos;
   // return std::max_element(_lst->begin(), _lst->end());// #include <algorithm>
   
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
    SetConsoleOutputCP(1251);
    std::cout << "Курсовая работа запущена...\n";
    StudentDBClass* sdb = new StudentDBClass();    
    StudentDBClass* sdb1 = new StudentDBClass();
    StudentDBClass* sdb2 = new StudentDBClass();
    StudentDBClass* sdb3 = new StudentDBClass();
    sdb->FileName = "DB.txt";
    sdb->loadDataFromFile();

    bool debug = false;
    if (debug) {


        //Сортировка строк
        List <string> lst = { "Яна" , "Алина Рогова", "Ксюша","Данила", "Алексей" ,"Армен" };
        //Просмотреть список
        for (auto item : lst) {
            cout << item << endl;
        }
        List <string> sortedLst;
        sortedLst.clear();
        //cout << *mMin(&lst);
        while (!lst.empty()) {
            sortedLst.push_front(*mMin(&lst));
            lst.erase(mMin(&lst));
        }
        //Просмотреть отсортированный список
        cout << endl << "------------" << endl;
        for (auto item : sortedLst) {
            cout << item<<endl;
        }
    }
    else {

    
    //cout << sdb->GetRecordCount() << endl;
    ClassMenu* mainMenu = new ClassMenu();
    mainMenu->addTitleItem("Главное меню");
    mainMenu->addItem("Просмотреть список студетов (удалить или изменить данные)"); //0
    mainMenu->addItem("Добавить данные о студенте в БД"); //1
    mainMenu->addItem("Сохранить БД студентов в файл"); //2
    mainMenu->addItem("Выполнить вариант 18"); //3
    mainMenu->addItem("Выход"); //4
    int resultSelectedItem = 0;
    int exitInt = 9;
    ClassMenu* studentsMenu = new ClassMenu();
    studentsMenu->addTitleItem("Список студентов");
    int resultStudentSelectedItem = 1;
    const int exitIntStudentMenu = 0;
    StudentNode* sn;
    StudentClass* st = new StudentClass();
    ClassMenu* delStudentsMenu = new ClassMenu();
    int curCount;
    ClassEdit* ce = new  ClassEdit();
    int startYear = 0;
    int endYear = 0;
    int year = 0;
    StringBuilderClass* sb = new StringBuilderClass();
    List<StudentNode>::iterator pos();
    List <StudentNode> printLst;
    string firstPartString;
    while (resultSelectedItem != exitInt) {
        mainMenu->run();
        resultSelectedItem = mainMenu->getSelectedItem();
        switch (resultSelectedItem) {
        case 0:
            resultStudentSelectedItem = 1;
            while (resultStudentSelectedItem != exitIntStudentMenu) {
                studentsMenu->eraseItem();
                studentsMenu->addItem("Выход");
                studentsMenu->addItem("Удалить данные о студенте");
                /*sn = sdb->getInit();*/
                for(int i=0;i<sdb->DataBase.size();i++)
                { // добавить пункты меню ФИО студентов
                    sn = &sdb->DataBase.at(i);
                    string tmpString = sn->surName + " " + sn->name + " " + sn->middleName + " " + sn->group;
                    studentsMenu->addItem(tmpString); //добавить в меню студентов
                    //sn = sn->next;
                }
                studentsMenu->run();
                resultStudentSelectedItem = studentsMenu->getSelectedItem();
                if (resultStudentSelectedItem == exitIntStudentMenu) {
                    break;
                }
                if (resultStudentSelectedItem == 1) //удаление данных о студенте
                {
                    delStudentsMenu->eraseAll();
                    delStudentsMenu->addTitleItem("Выберите студента для удаления данных");
                    delStudentsMenu->addItem("Выход");
                    int resultDel = 1;
                    const int exitDel = 0;
                    for(int i=0; i<sdb->DataBase.size();i++)
                    { // добавить пункты меню ФИО студентов
                        sn = &sdb->DataBase.at(i);
                        string tmpString = sn->surName + " " + sn->name + " " + sn->middleName + " " + sn->group;
                        delStudentsMenu->addItem(tmpString); //добавить в меню студентов
                        //sn = sn->next;
                    }
                    while (resultDel != exitDel) {
                        delStudentsMenu->run();
                        resultDel = delStudentsMenu->getSelectedItem();
                        if (resultDel == exitDel) {
                            break;
                        }
                        else {
                            int num = resultDel - 1;
                            sdb->DataBase.erase(std::next(sdb->DataBase.begin(), num));
                            break;
                        }
                    }
                }
                if (resultStudentSelectedItem>1)
                {
                    int num = resultStudentSelectedItem - 2; //!
                    sn = &sdb->DataBase.at(num);   
                    string oldRecordСardNumber = "";
                    oldRecordСardNumber = sn->recordСardNumber;
                    st->editStudent(sn);

                    if (sdb->getSameRecordСardNumber(sn->recordСardNumber)>1)
                    {
                        sn->recordСardNumber = oldRecordСardNumber;
                        cout << "Ошибка введен номер зачетной книжки который уже есть в БД";
                        _getch();
                    }
                }
            }
            //resultSelectedItem = exitInt;
            break;
        case 1:
            sn = new StudentNode();
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 10; j++)
                    sn->examsRecordsData[i][j].isEmpty = true;
            st->editStudent(sn);
            if (sdb->getSameRecordСardNumber(sn->recordСardNumber)>=1)
            {
                cout << "Ошибка введен номер зачетной книжки который уже есть в БД";
                _getch();
            }
            else
            {
                sdb->DataBase.push_front(*sn);
            }
            break;        
        case 2: //Сохранить в файл
            sdb->saveDataToFile(sdb->FileName);
            //sdb->saveDataToFile("d:\\db1.txt");
            break;
        case 3:
            /*Вариант 18 Разбить группу на 3 части:
            1) отличников;
            2) хорошистов;
            3) троечников
            по сессии, вводимой по желанию пользователя за все время обучения.*/
            system("cls");
            sdb->getRangeSem();
            cout << "Полный список студентов" << endl;
            sdb->updateCountMarks543();  //Перерасчитать поле средний балл 
            sdb->printAllSurName_Name_MName_bYaear_Marks543();
            cout << "\nОтличники" << endl;
            sdb1->DataBase.clear();
            for (auto item : sdb->DataBase) {
                if (item.countMarks5 >= 1) {
                    sdb1->DataBase.push_front(item);
                }
            }
            sdb1->printAllSurName_Name_MName_bYaear_Marks543();
            cout << "\nХорошисты" << endl;
            sdb1->DataBase.clear();
            for (auto item : sdb->DataBase) {
                if ((item.countMarks3 == 0) and (item.countMarks4 != 0)) {
                    sdb1->DataBase.push_front(item);
                }
            }
            sdb1->printAllSurName_Name_MName_bYaear_Marks543();
            cout << "\nТроишники" << endl;
            sdb1->DataBase.clear();
            for (auto item : sdb->DataBase) {
                if (item.countMarks3 > 0) {
                    sdb1->DataBase.push_front(item);
                }
            }
            sdb1->printAllSurName_Name_MName_bYaear_Marks543();
            _getch();
            break;
        case 4:
            resultSelectedItem = exitInt;
            break;
        default:
            break;
        }
    }
    //_getch();
    }
}

