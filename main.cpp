#include <iostream>
#include<fstream>

using namespace std;

class product
{
    int pno;
    char name[50];
    float dis,price;
public:
    void create_product();
    void show_product();
    char * retname()
    {
        return name;
    }
    float retprice()
    {
        return price;
    }
    int retpno()
    {
        return pno;
    }
    float discount()
    {
        return dis;
    }
};
void product::create_product()
{
    cout<<"\nEnter the product No. of the product : ";
    cin>>pno;
    cout<<"\nEnter the Name of the product : ";
    cin>>name;
    cout<<"\nEnter the Price of the product : ";
    cin>>price;
    cout<<"\nEnter the Discount in percentage(%) : ";
    cin>>dis;
}
void product::show_product()
{
    cout<<"\nThe Product No. of the Product : "<<pno;
    cout<<"\nThe Name of the Product : "<<name;
    cout<<"\nThe Price of the Product : "<<price;
    cout<<"\nDiscount : "<<dis<<" %";
}

product p;
fstream f;

void write_product()
{
    f.open("Mart.dat",ios::out|ios::app);
    p.create_product();
    f.write((char *) &p ,sizeof(product));
    f.close();
    cout<<"\n\n\tProduct has been created\n";
}
void display_all()
{
    cout<<"\n\n\tDISPLAY ALL RECORD !!\n\n";
    f.open("Mart.dat",ios::in);
    while(f.read((char *) &p ,sizeof(product)))
    {
        p.show_product();
        cout<<"\n-----------------------------------\n";
    }
    f.close();
}
void specific_display()
{
    int n,flag=0;
    cout<<"\nEnter Product No. of the Product to display its details : ";
    cin>>n;
    f.open("Mart.dat",ios::in);
    while(f.read((char *) &p ,sizeof(product)))
    {
        if(p.retpno()==n)
        {
            p.show_product();
            cout<<"\n-----------------------------------\n";
            flag=1;
        }
    }
    f.close();
    if(flag==0)
    {
        cout<<"\nRecord not Exist";
    }
}
void modify_record()
{
    int n,flag=0;
    cout<<"\nEnter Product No. of the Product to modify its details : ";
    cin>>n;
    f.open("Mart.dat",ios::in|ios::out);
    while(f.read((char *) &p ,sizeof(product)))
    {
        if(p.retpno()==n)
        {
            p.show_product();
            cout<<"\nPlease Enter the New details of product : \n";
            p.create_product();
            int pos = (-1)*sizeof(product);
            f.seekp(pos,ios::cur);
            f.write((char *) &p ,sizeof(product));
            cout<<"\n\n\tRECORD UPDATED\n";
            flag=1;
        }
    }
    f.close();
    if(flag==0)
    {
        cout<<"\nRecord not Exist";
    }
}
void delete_record()
{
    int n;
    cout<<"\nEnter Product No. of the Product Which you want to Delete : ";
    cin>>n;
    f.open("Mart.dat",ios::in|ios::out);
    fstream f1;
    f1.open("temp.dat",ios::out);
    f1.seekg(0,ios::beg);
    while(f.read((char *) &p ,sizeof(product)))
    {
        if(p.retpno()!=n)
        {
            f1.write((char *) &p ,sizeof(product));
        }
    }
    f1.close();
    f.close();
    remove("Mart.dat");
    rename("temp.dat","Mart.dat");
    cout<<"\n\n\tRECORD DELETED\n";
}
void menu()
{
    f.open("Mart.dat",ios::in);
    cout<<"\n\n\tProduct Menu\n";
    cout<<"\n-------------------------------------\n";
    cout<<"P.No.\t\tName\t\tPrice\n";
    cout<<"\n-------------------------------------\n";
    while(f.read((char *) &p ,sizeof(product)))
    {
        cout<<p.retpno()<<"\t\t"<<p.retname()<<"\t\t"<<p.retprice()<<endl;
    }
    f.close();
}
void place_order()
{
    int order[50],quan[50],c=0;
    float amt,dis_amt,total=0;
    char ch;
    menu();
    cout<<"\n---------------------------\n";
    cout<<"Place Your Order";
    cout<<"\n---------------------------\n";
    do
    {
        cout<<"\nEnter Product No. of the product : ";
        cin>>order[c];
        cout<<"\nEnter the Quantity in number : ";
        cin>>quan[c];
        c++;
        cout<<"\nDo You Want Any Other Product (y/n) ";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    cout<<"\nThank you for placing your order ";
    cout<<"\n\n******************************BILL*******************************\n";
    cout<<"\nP No.\tName\tQuantity\tPrice\tAmount\tAmount After Discount\n";
    for(int i=0;i<=c;i++)
    {
        f.open("Mart.dat",ios::in);
        f.read((char *)&p,sizeof(product));
        while(!f.eof())
        {
            if(p.retpno()==order[i])
            {
                amt=p.retprice()*quan[i];
                dis_amt=amt-(amt*p.discount()/100);
                cout<<"\n"<<order[i]<<"\t"<<p.retname()<<"\t"<<quan[i]<<"\t\t"
                    <<p.retprice()<<"\t"<<amt<<"\t\t"<<dis_amt<<endl;
                total += dis_amt;
            }
            f.read((char *)&p,sizeof(product));
        }
        f.close();
    }
    cout<<"\n\n\tTotal Amount to pay = "<<total<<endl;
    cout<<"\nVisit again";
}
void admin_menu()
{
    string pass,passcheck;
    pass="ecart";
    cout<<"\nEnter Password : ";
    cin>>passcheck; 
if(passcheck==pass)
{
int ch;
do
{
    cout<<"\n\n\n\tADMIN MENU";
    cout<<"\n\n1.CREATE PRODUCT";
    cout<<"\n\n2.DISPLAY ALL PRODUCTS";
    cout<<"\n\n3.DISPLAY SPECIFIC PRODUCT ";
    cout<<"\n\n4.MODIFY PRODUCT";
    cout<<"\n\n5.DELETE PRODUCT";
    cout<<"\n\n6.VIEW PRODUCT MENU";
    cout<<"\n\n7.EXIT FROM ADMIN MENU";
    cout<<"\n\nPlease Enter Your Choice : ";
    cin>>ch;
    switch(ch)
    {
    case 1:
        write_product();
        break;
    case 2:
        display_all();
        break;
    case 3:
        specific_display();
        break;
    case 4:
        modify_record();
        break;
    case 5:
        delete_record();
        break;
    case 6:
        menu();
    case 7:
        break;
    default:
        cout<<"\n";
        admin_menu();
    }
    }while(ch!=7);
}
else
{
    cout<<"\nWrong Password\n";
}
}
int main()
{
    int ch;
    cout<<"\n\n\t\tE-CART OR MALL DATABASE PROJECT\n";
    do
    {
        cout<<"\n\n\n\tMAIN MENU\n";
        cout<<"\n\n1.FOR ADMIN";
        cout<<"\n\n2.CUSTOMER";
        cout<<"\n\n3.EXIT";
        cout<<"\n\nPlease Enter your choice : ";
        cin>>ch;
        switch(ch)
        {
        case 1:
            admin_menu();
            break;
        case 2:
            place_order();
            break;
        case 3:
            break;
        default:
            cout<<"\nEnter correct choice : ";
        }
    }while(ch!=3);
    return 0;
}

