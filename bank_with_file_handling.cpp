//om shree ganeshay namah
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<ctime>
#include<fstream>
#include<conio.h>

using namespace std;

int index;
class error{
    char e[150];
public:
    error(){}
    error(const char *error)
    {
        strcpy(e, error);
    }
    void print()
    {
        cout<<"Error is : "<<e<<endl;
        cout<<"___________________________________________________________________________________"<<endl;
        cout<<endl;
        cout<<"press any key to continue.."<<endl;
        getch();
    }
};
void write_index()
{
    ofstream out;
    out.open("index.txt");
    out<<index;
    out.close();
}

void read_index()
{
    ifstream in;
    in.open("index.txt");
    in>>index;
    in.close();
}

void read_class();
void write_class();

class user{
protected:
    char name[100];
    int id;
    int pin;
    int status;
    float amount;
    char mobile[10];
    float record[10];
    int ri;
    time_t td[10];
};

class account : public user{
public:
    friend void display(account *a1);
    friend void write_class();
    friend void read_class(); 
    friend ostream& operator <<(ostream &, account);   
    void setdata()
    {
        read_index();
        read_class();
        int n, z=1;
        account *a1 = this;
        do{
            system("CLS");
            cout<<"======================================================================"<<endl;
            cout<<"||                WELCOME TO ACCOUNT CREATING SECTION               ||"<<endl;
            cout<<"======================================================================"<<endl;
            cout<<endl;
            cout<<"Enter 2 digit account number as your id : ";
            cin>>a1[index].id;
            for(int i=0; i<index; i++)
            {
                if(a1[i].id == a1[index].id)
                {
                    z=0;
                    break;
                }
            }
            try{
                if(z)
                {
                    cout<<"Enter your name : ";
                    scanf("\n");
                    cin.getline(a1[index].name, 100);
                    cout<<"Enter your mobile number : ";
                    cin>>a1[index].mobile;
                    cout<<"Enter your 4 digit pin : ";
                    cin>>a1[index].pin;
                    cout<<"Enter amount : ";
                    cin>>a1[index].amount;
                    a1[index].status = 1;
                    a1[index].ri = 0;
                    cout<<"Account has been created"<<endl;
                    for(int i=0; i<10; i++)
                    {
                        a1[index].record[i] = 0;
                    }
                    index++;
                }
                else {throw error("Account is already created");}
            }
            catch(error e)
            {
                e.print();
                cout<<"_______________________________________________________________"<<endl;
            }
            ofstream out;
            out.open("index.txt");
            out<<index;
            out.close();

            cout<<endl;
            cout<<"1 : Create more account"<<endl;
            cout<<"0 : Exit"<<endl;
            cin >> n;
        }while(n != 0);
        write_class();
        // write_index();
    }
    int find_account(int &cid, int gid) //cid = customer id, gid = given id.
    {
        account *a1 = this;
        int id1 = gid;
        for(int i=0; i<index; i++)
        {
            if(id1 == a1[i].id)
            {
                cid = i;
                if(a1[i].status == 1)
                {
                    return 1;
                }
                else{
                    return 2;
                }
            }
        }
        return 0;
    }
    int check_pin()
    {
        int cpin;
        for(int i=1; i<=3; i++)
        {
            cout<<"Chance : "<<i<<endl;
            cout<<"Enter Pin : ";
            cin>>cpin;
            if(cpin == pin)
            {
                return 1;
            }
        }
        cout<<"You entered wrong pin 3 times."<<endl;
        cout<<"Now your account will be block for security purpose"<<endl;
        cout<<"_______________________________________________________________"<<endl;
        status = 0;
        return 0;
    }
    void transaction()
    {
        read_index();
        read_class();
        account *a1 = this;
        int sid, spin, rid, id1, id2, i, n;
        float samount; //samount = sender amount.

        do{
            system("CLS");
            cout<<"======================================================================"<<endl;
            cout<<"||                        TRANSACTION SECTION                       ||"<<endl;
            cout<<"======================================================================"<<endl;
            cout<<endl;
            
            cout<<"Enter id of your account : ";
            cin>>id1;
            int x1 = a1[0].find_account(sid, id1);
            cout<<"Enter id of receiver account : ";
            cin>>id2;
            int x2 = a1[0].find_account(rid, id2);
            if( (x1 == 1) && (x2 == 1))
            {
                system("CLS");
                int t1 = a1[sid].check_pin();
                if(t1 == 1)
                {
                    cout<<"Enter amount of transaction : ";
                    cin>>samount;
                    try{
                        if(samount < 0)
                        {
                            throw error("Transaction is not possible due to negative amount");
                        }
                        else if(samount > a1[sid].amount)
                        {
                            throw error("Transaction is not possible due to Higher amount");
                        }
                        else{
                            a1[sid].amount -= samount;
                            a1[rid].amount += samount;
                            cout<<"transaction completed successfuly"<<endl;
                            a1[sid].amount += samount*0.01;
                            float d = samount*0.01 - samount;
                            a1[sid].record[a1[sid].ri] = d;
                            a1[rid].record[ a1[rid].ri ] = samount;
                            a1[sid].td[a1[sid].ri++] = time(0);
                            a1[rid].td[a1[rid].ri++] = time(0);

                            cout<<"1% of transaction is cashback on your account"<<endl;

                            if(a1[sid].ri == 10){ a1[sid].clear_record(); }
                            if(a1[rid].ri == 10){ a1[rid].clear_record(); }
                        }
                    }
                    catch(error e)
                    {
                        e.print();
                    }
                    
                }
            }
            else{
                try{
                    if(x1 == 0 || x2 == 0)
                    {
                        cout<<"Account not found.."<<endl;
                        cout<<"Enter correct id.."<<endl;
                        cout<<"_______________________________________________________________"<<endl;
                    }
                    else { 
                        throw error("Transaction not possible due to one or both accounts are block.");
                    }
                }
                catch(error e)
                {
                    e.print();
                }
            }

            cout<<endl;
            cout<<"1 : More transaction"<<endl;
            cout<<"0 : Exit"<<endl;
            cin>>n;
        }while( n!= 0 );
        write_class();
    }
    void clear_record()
    {
        ri = 0;
        for(int i=0; i<10; i++)
        {
            record[i] = NULL;
        }
    }
    void change_pin()
    {
        read_index();
        read_class();
        account *a1 = this;
        int cid, cpin, id1, cnpin, i, n;
        do{
            system("CLS");
            cout<<"======================================================================"<<endl;
            cout<<"||                             NET BANKING                          ||"<<endl;
            cout<<"======================================================================"<<endl;
            cout<<endl;
            
            cout<<"Enter your account id : ";
            cin>>id1;
            int x = a1[0].find_account(cid, id1);
            try{
                if(x == 1)
                {
                    int t1 = a1[cid].check_pin();
                    if(t1 == 1)
                    {
                        cout<<"Enter new pin : ";
                        cin>>cnpin;
                        a1[cid].pin = cnpin; //cnpin = customer new pin, cpin = customer pin.
                        cout<<"Pin change successfully"<<endl; 
                    }
                }
                else if(x==2){
                    error e("Account is bloc");
                }
                else{
                    throw error("Account not found");
                }
            }
            catch(error e)
            {
                e.print();
            }
            cout<<endl;
            cout<<"1 : Change another pin"<<endl;
            cout<<"0 : Exit"<<endl;
            cin>>n;
        }while( n != 0);
        write_class();
    }

    void unblock()
    {
        read_index();
        read_class();
        account * a1 = this;
        int id1, cid, n, n3;
        char pwd[11];
        
        do{
            system("CLS");
            cout<<"======================================================================"<<endl;
            cout<<"||                       WELCOME TO ADMIN PANEL                      ||"<<endl;
            cout<<"======================================================================"<<endl;
            cout<<endl;
            
        
            system("CLS");
            cout<<"1 : Unblock Account"<<endl;
            cout<<"2 : Block Account"<<endl;
            cout<<"______________________________________________________________________________"<<endl;
            cin>>n3;
            system("CLS");
            cout<<"Enter id : ";
            cin>>id1;
            int x = a1[0].find_account(cid, id1);
            
            if(x == 1 || x==2 )
            {
                if(n3 == 1)
                {
                    try{
                        if(x==2)
                        {
                            a1[cid].status = 1;
                            cout<<"Account has been activated"<<endl;
                            cout<<"_______________________________________________________________"<<endl;
                        }
                        else{
                            throw error("Account is already active.");
                        }
                    }
                    catch(error e)
                    {
                        e.print();
                    }
                }
                else{
                    try{
                        if(x==1)
                        {
                            a1[cid].status = 0;
                            cout<<"Account has been deactivated"<<endl;
                            cout<<"_______________________________________________________________"<<endl;
                        }
                        else{
                            throw error("Account is already deactivated.");
                        }
                    }
                    catch(error e)
                    {
                        e.print();
                    }
                }
            }
            else{
                cout<<"Account not found"<<endl;
                cout<<"_______________________________________________________________"<<endl;
            }
            cout<<endl;
            cout<<"1 : Unblock or Block another account"<<endl;
            cout<<"0 : Exit"<<endl;
            cin>>n;
        }while( n != 0);
        write_class();
    }

    void show(int i)
    {
        account *a1 = this;
        system("CLS");
        cout<<"======================================================================"<<endl;
        cout<<"||                      ACCOUNT DETAILS SECTION                     ||"<<endl;
        cout<<"======================================================================"<<endl;
        cout<<endl;
            
        cout<<"Name           : "<<a1[i].name<<endl;
        cout<<"Mobile         : "<<a1[i].mobile<<endl;
        cout<<"Balance        : "<<a1[i].amount<<endl;
        cout<<"Account status : "<<a1[i].status<<endl;
        cout<<"Account id     : "<<a1[i].id<<endl;
        cout<<"Security pin   : "<<a1[i].pin<<endl;
    }

    void view_record()
    {
        read_index();
        read_class();
        account * a1 = this;
        int id1, cid, n;
        do{
            system("CLS");
            cout<<"======================================================================"<<endl;
            cout<<"||                        TRANSACTION HISTORY                       ||"<<endl;
            cout<<"======================================================================"<<endl;
            cout<<endl;
            
            cout<<"Enter id of your account"<<endl;
            cin>>id1;
            int x = a1[0].find_account(cid, id1);

            try{
                if(x == 1)
                {
                    for(int i=0; i< a1[cid].ri; i++)
                    {
                        char *dt = ctime( &td[i] );
                        cout<<dt;
                        cout<<"Transaction Amount : "<<a1[cid].record[i]<<endl;
                        cout<<endl;
                    }
                }
                else{
                    throw error("Account not found.");
                }
            }
            catch(error e)
            {
                e.print();
            }
            cout<<endl;
            cout<<"1 : View record"<<endl;
            cout<<"0 : Exit"<<endl;
            cin>>n;
        }while(n != 0);
    }

};

ostream& operator<<(ostream& out, account a1)
{
    read_index();
    out<<"Name   : "<<a1.name<<endl;
    out<<"Id     : "<<a1.id<<endl;
    out<<"Pin    : "<<rand()<<endl;
    out<<"Status : "<<a1.status<<endl;
    out<<"Amount : "<<a1.amount<<endl;
    out<<"Mobile : "<<a1.mobile<<endl;

    out<<"Record Of Transaction : "<<endl;
    out<<"______________________________________________________________________"<<endl;
    char *dt;
    for(int i=0; i<a1.ri; i++)
    {
        out<<"Transaction Amount : "<<a1.record[i]<<" Time : ";
        dt = ctime( &a1.td[i] );
        out<<dt;
    }
    out<<"============================================================================";
    out<<endl<<endl;;
    return out;
}


void display(account *a1)
{
    read_index();
    read_class();
    int id1, cid, cpin, n, i;
    do{
        system("CLS");
        cout<<"Enter id of your account : "<<endl;
        cin>>id1;
        int x = a1[0].find_account(cid, id1);
        try{
            if(x == 1 || x == 2)
            {
                int t1 = a1[cid].check_pin();
                if(t1 == 1)
                {
                    a1[0].show(cid);
                    cout<<endl;
                    cout<<"_______________________________________________________________"<<endl;
                }
            }
            else{
                throw error("Account not found.");
            }
        }
        catch(error e)
        {
            e.print();
        }
        write_class();
        cout<<endl;
        cout<<"1 : For find another account"<<endl;
        cout<<"0 : Exit"<<endl;
        cin>>n;
    }while(n != 0);
}

account a1[10];

void write_class()
{
    ofstream out;
    out.open("data.bin", ios :: binary);
    out.write((char *)&a1, index*sizeof(a1));
    out.close();
    out.open("classdata.txt");
    for(int i=0; i<index; i++)
    {
        out<<a1[i];
    }
}

void read_class()
{
    ifstream in;
    in.open("data.bin", ios :: binary);
    in.read((char *)&a1, index*sizeof(a1));
    in.close();
}

int main()
{
    system("CLS");
    int n, n1;
    cout<<"======================================================================"<<endl;
    cout<<"||                      WELCOME TO NET BANKING                      ||"<<endl;
    cout<<"======================================================================"<<endl;
    cout<<endl;
            
    cout<<"1 : Admin"<<endl;
    cout<<"2 : User"<<endl;
    cout<<"______________________________________________________________________"<<endl;
    cin>>n1;
    if(n1 == 2)
    {
        do{
            // try{}catch{}
            system("CLS");
            cout<<"======================================================================"<<endl;
            cout<<"||                      WELCOME TO NET BANKING                      ||"<<endl;
            cout<<"======================================================================"<<endl;
            cout<<endl;
            cout<<"1 : Create account"<<endl;
            cout<<"2 : Change pin"<<endl;
            cout<<"3 : Transaction"<<endl;
            cout<<"4 : Account details"<<endl;
            cout<<"5 : View transaction record"<<endl;
            cout<<"0 : Exit"<<endl;
            cout<<"_______________________________________________________________________"<<endl;
            cin >> n;
            switch (n)
            {
            case 1:
                a1[0].setdata();
                break;
            case 2:
                a1[0].change_pin();
                break;
            case 3:
                a1[0].transaction();
                break;
            case 4:
                display(a1);
                break;
            case 5:
                a1[0].view_record();
                break;
            case 0:
                system("CLS");
                cout<<endl;
                cout<<"===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X==="<<endl;
                cout<<"||                                         Thank You                                         ||"<<endl;
                cout<<"===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X==="<<endl;
                cout<<endl;
                break;
            default:
                cout<<"enter correct number"<<endl;
                break;
            }
        }while(n != 0);
    }
    else{
        system("CLS");
        char pwd[11];
        cout<<"Enter Password : ";
        cin>>pwd;
        int a = strcmp(pwd, "ABCD@@1234");
        try{
            if(a == 0)
            {
                a1[0].unblock();
                system("CLS");
            }
            else{
                throw error("Wrong Password.");
                system("CLS");
            }
        }
        catch(error e)
        {
            e.print();
        }
        cout<<endl;
        cout<<"===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X==="<<endl;
        cout<<"||                                         Thank You                                         ||"<<endl;
        cout<<"===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X===X==="<<endl;
        cout<<endl;
    }
    read_index();
    read_class();
    ofstream out("classdata.txt");
    for(int i=0; i<index; i++)
    {
        out<<a1[i];
    }
    out.close();
    return 0;
}