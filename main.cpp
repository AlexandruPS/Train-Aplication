#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

int compare_info(string array1, string array2)  //Verify if 2 strings are identical(returns 0 or 1)
{
    int i;
    int response = 0;
    i = 0;

    while(array1[i] == array2[i] && response == 0 )
    {
        if(array1[i] == '\0' || array2[i] == '\0'){
            response = 1;
        }
        i++;
    }

    return response;
}

class User
{
    private:
        char username[21];
        char password[31];

    public:

        char curse[50][80];
        char rezervari[50][80];
        int i=0,j=0;

        User();
        User(char username[], char password[])
        {
            strcpy(this->username,username);
            strcpy(this->password,password);
        }

       bool loginop()     //FUNCTION FOR SIGNING IN AS AN OPERATOR
       {
           //GETTING DATA FROM OPERATORS FILE
            vector<vector<string>>content;
            vector<string>row;
            string line,word;

            fstream file("Operatori.csv", ios::in);
            if(file.is_open())
                {
                    while(getline(file,line))
                        {
                            row.clear();
                            stringstream str(line);
                            while(getline(str, word, ','))
                            row.push_back(word);
                            content.push_back(row);
                        }
                }
            else

                cout<<"Fisierul nu a putut fi deschis !"<<endl;

                //VERIFY IF PASSWORD AND USERNAME ARE CORRECT
            bool ok=0;
            for(int i = 0 ; i<content.size();i++)
                    {
                        if(compare_info(password,content[i][1])==1 && compare_info(username,content[i][0])==1)
                        {
                            ok=1;
                            return 1;
                        }
                    }
            if(ok == 0)
            {
                cout<<"Username sau parola gresita"<<endl;
                return 0;
            }

       };

       bool loginus()    //FUNCTION FOR SIGNING IN AS AN USER
       {

            vector<vector<string>>content1;
            vector<string>row1;
            string line1,word1;

            fstream file1("Utilizatori.csv", ios::in);
            if(file1.is_open())
                {
                    while(getline(file1,line1))
                        {
                            row1.clear();
                            stringstream str1(line1);
                            while(getline(str1, word1, ','))
                            row1.push_back(word1);
                            content1.push_back(row1);
                        }
                }
            else

                cout<<"Fisierul nu a putut fi deschis !"<<endl;

           bool ok=0;
            for(int i = 0 ; i<content1.size();i++)
                    {

                        if(compare_info(password,content1[i][1])==1 && compare_info(username,content1[i][0])==1)
                        {
                            ok=1;
                            return 1;
                        }


                    }
            if(ok == 0)
            {
                cout<<"Username sau parola gresita"<<endl;
                return 0;
            }

       };

       void MakeCourse( char str1[], char str2[])  //FUNCTION FOR ADDING A COURSE TO THE Curse.csv FILE AS AN OPERATOR
       {
          fstream fout;

          fout.open("Curse.csv",ios::out | ios::app);

          fout<<str1<<","<<str2<<endl;

          fout.close();

       }

       void MakeUser( char str1[], char str2[])  //FUNCTION FOR ADDING AN USER TO THE Utilizatori.csv FILE
       {
           fstream fout;
           fout.open("Utilizatori.csv",ios::out | ios::app);
           fout<<str1<<","<<str2<<endl;
           fout.close();

       }
       void DelCourse(int a)    //FUNCTION FOR DELETING A COURSE TO THE Curse.csv FILE AS AN OPERATOR
       {

         fstream fout;

         fout.open("Curse.csv");

         vector<string> lines;
         string line;

        while(getline(fout, line))
            lines.push_back(line);

        fout.close();

        ofstream write;
        write.open("Curse.csv");

        a--;
        for(int i =0 ; i<lines.size(); i++)
            if(i != a)
                write<<lines[i]<<endl;

        write.close();

       }

       void Reserve(char str[]) //FUNCTION FOR SEARCHING AND BOOKING A COURSE AS AN USER
       {
           ifstream file;
           file.open("Curse.csv");

           vector<string> lines;
           string line;

           while(getline(file, line))
            lines.push_back(line);

            cautare:
            int ok=0;
            for(int i = 0 ; i<lines.size(); i++)
                if(lines[i].find(str) != string::npos)
                    {
                        cout<<lines[i]<<endl;
                        ok++;
                    }
            if(ok==0)
                    {
                        cout<<"Ruta inexistenta ! Cautati cursa dorita :"<<endl;
                        cin>>str;
                        goto cautare;
                    }
            else

            {ora:
            char str2[6];
            cout<<"Alegeti ora dorita pentru rezervare : (xx:xx) ";
            cin>>str2;


            if(isdigit(str2[0]) && isdigit(str2[1]) && str2[2]==':' && isdigit(str2[3]) && isdigit(str2[4]))

            {
                for(int i = 0 ; i<lines.size(); i++)
                    if(lines[i].find(str) != string::npos && lines[i].find(str2) != string::npos)
                        {
                            int x;
                            cout<<"Rezervare facuta pe ruta "<<lines[i]<<endl;

                            cout<<"Cautati cursa dorita :"<<endl;
                            cin>>str;

                            Reserve(str);

                        }
                    else

                        {
                            cout<<"Calatorie inexistenta"<<endl;
                            goto ora;
                        }

            }

            else
                {
                    cout<<"Calatorie inexistenta"<<endl;
                    goto ora;
                }}

       }



};


int main()
{   char user[21],parola[31];
    int A;

    cout<<"Enter 1 pentru Operator si 2 pentru Utilizator ";

    cin>>A;

    switch(A)

            {

            case 1:
                    {
                        autentificare:
                        cout<<"Introduceti username-ul: ";
                        cin>>user;
                        cout<<"Introduceti parola: ";
                        cin>>parola;

                        User human(user,parola);

                        if(human.loginop() == 1)
                        {
                                int a;

                                cout<<"Autentificare reusita"<<endl;


                            repeta:
                                cout<<"Doriti sa adaugati sau sa stergeti o cursa? "<<endl;
                                cout<<"Adauga o cursa - 1"<<endl;
                                cout<<"Sterge o cursa - 2"<<endl;

                                cin>>a;

                            switch (a)

                            {
                                case 1 :

                                {
                                    char sir1[40],sir2[40],sir[81];

                                    cout<<"Alegeti un traseu: (CITY->CITY) "<<endl<<endl;

                                    traseu:

                                    cin>>sir1;

                                    if(strstr(sir1,"->"))

                                        {

                                            interval:
                                            cout<<"Alegeti un interval pentru "<<sir1<<" (xx:xx->xx:xx)"<<endl;


                                            cin>>sir2;

                                            if(isdigit(sir2[0]) && isdigit(sir2[1]) && sir2[2]==':' && isdigit(sir2[3]) && isdigit(sir2[4])
                                            && sir2[5]=='-' && sir2[6]=='>'
                                            && isdigit(sir2[7]) && isdigit(sir2[8]) && sir2[9]==':' && isdigit(sir2[10]) && isdigit(sir2[11]))

                                                {
                                                    human.MakeCourse(sir1,sir2);
                                                    goto repeta;
                                                }
                                                else
                                                {
                                                    cout<<"Format Incorect de alegere a Intervalului (xx:xx->xx:xx)"<<endl;
                                                    goto interval;
                                                }

                                        }
                                        else
                                        {
                                            cout<<"Format Incorect de alegere a traseului (CITY->CITY)"<<endl;
                                            goto traseu;
                                        }

                                }

                                case 2 :
                                {
                                        int a;
                                        cout<<"Alegeti numarul cursei pe care doriti sa o stergeti: "<<endl;
                                        cin>>a;

                                        human.DelCourse(a);

                                        goto repeta;


                                }


                            }

                        }
                        else
                            goto autentificare;

                    }

                break;

                case 2:

                    {   int B;
                        cout<<"Apasati 1 pentru autentificare si 2 pentru creare cont: ";
                        cin>>B;

                        switch(B)
                        {
                            case 1:
                            {
                                autentificare2:
                                cout<<"Introduceti username-ul: "<<endl;
                                cin>>user;
                                cout<<"Introduceti parola: "<<endl;
                                cin>>parola;

                                User human(user,parola);

                                if(human.loginus() == 1)
                                {
                                    char sir1[40];

                                    cout<<"Autentificare reusita "<<endl;

                                    Cautare:

                                    cout<<"Cautati cursa dorita (City->City) "<<endl;

                                    cin>>sir1;

                                    if(strstr(sir1,"->"))

                                        human.Reserve(sir1);
                                    else
                                    {
                                        cout<<"Format cursa incorect!"<<endl;
                                        goto Cautare;
                                    }





                                }

                                else

                                {
                                        goto autentificare2;
                                        cout<<"Username sau parola gresita";
                                }


                            }
                            case 2:
                            {
                                char email[35],parola1[31];
                                cout<<"Introduceti email: "<<endl;
                                cin>>email;
                                cout<<"Introduceti username-ul dorit: "<<endl;
                                cin>>user;
                                cout<<"Introduceti parola: "<<endl;
                                cin>>parola;
                                parola:
                                cout<<"Confirmati parola: "<<endl;
                                cin>>parola1;

                                if(strcmp(parola,parola1)!=0)
                                {
                                     cout<<"Nu ati confirmat corect parola!"<<endl;
                                    goto parola;
                                }

                                User human(user,parola);

                                human.MakeUser(user,parola);

                                cout<<"Cont creat cu succes"<<endl;

                                return 0;


                            }
                        }


                break;

                default:

                    return 0;

            }
            }



    return 0;
}
