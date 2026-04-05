#include<iostream>       //Ιωάννης Τέρπος Α.Μ:18390208
#include<cstdlib>
#include<string>
#include<cstring>
#include<fstream>
#define N 50
using namespace std;
// create classes item,environment and Player.
class item
{
  private:
  	string code;
  	string name;
  	string situation;
  public:
  	item();
  	void set_values(string cd,string nm);
  	void set_situation(string st);
  	string getname();
  	string getcode();
  	string getsituation();
  	item operator+(const item &right);
  	item& operator=(const item &right);
  	friend ostream& operator <<(ostream &left, const item &right);
};

class environment{
	private:
	item *things;
	int position;
	public:
	environment();
	void additem(item& a);
	void setposition(int ps);
	void removeitem(item& b);
	friend ostream& operator<< (ostream& left,const environment& right);
	void printEnvironment();
	int getposition();
	item searching(string name);
	item& getthings(int index);
};

class Player
{
  private:
    item *bag;
    int pos;
  public:
    Player();
    void addItem(item& a);
    void setposition(int ps);
    void removeItem(item& b);
    void dropItem(item& a,environment& era);
    item& getbag(int index);
    void pickitem(item& a,environment& era);
    friend ostream& operator<<(ostream& left,const Player& right);
    void printbag();
    void crafting(item& a,item& b,Player& p);
    item searching(string name);
    int getpos();
};

//Default Constructor, accessors and methods of class item.

item::item(){
	code="N/A";
	name="N/A";
	situation="N/A";
}

string item::getcode(){
	return code;
}

void item::set_values(string cd,string nm){
	code=cd;
	name=nm;
}

void item::set_situation(string st){
	situation=st;
}

string item::getname(){
	return name;
}

string item::getsituation(){
	return situation;
}

item item::operator+(const item &right){
   item result;
   string str1,str2,str3;
   ifstream ifile;
   ifile.open("rules.txt",ios::in);
   if(ifile.is_open())
   {
   	 while(!ifile.eof())
   	 {
   	   getline(ifile,str1,'+');
	   getline(ifile,str2,'=');
	   getline(ifile,str3,'\n');
	   if((name==str1 && right.name==str2) || (right.name==str1 && name==str2))
	   {
	     result.name=str3;
	     result.situation="inventory";
		 ifstream file;
		 file.open("items.txt");
		 if(file.is_open())
		 {
		   while(!file.eof())
		   {
		   	 getline(file,str1,',');
		   	 getline(file,str2,',');
		   	 getline(file,str3,'\n');
		   	 if(result.name==str2)
		   	 {
		   	   result.code=str1;	
			 }
		   }
		 }
		 file.close();
		 ifile.close();
		 return result;
	   }	
     }
   }
   ifile.close();
   cout<<"Δεν υπάρχει συνδυασμός "<<name<<" και "<<right.name<<endl;
}

item& item::operator=(const item &right){
	if(this==&right)
	  return *this;
    code=right.code;
    name=right.name;
    situation=right.situation;
    return *this;
}

ostream& operator <<(ostream& left,const item& right){
	left<<right.code<<","<<right.name<<","<<right.situation<<endl;
	return left;
}

//Default Constructor, accessors and methods of class environment.

environment::environment(){
  things=new item[100];
}

void environment::additem(item& a){
  if(position<100)
  {
	things[position]=a;
	things[position].set_situation("environment");
	position++;
  }
  else
    cout<<"Δεν υπάρχει διάθεσιμος χώρος στο περιβάλλον"<<endl;
}

int environment::getposition(){
	return position;
}

void environment::setposition(int ps){
	position=ps;
}

ostream& operator<< (ostream& left,const environment& right){
   for(int k=0;k<right.position;k++)
   {
   	  left<<right.things[k]<<endl;
   }
   return left;
}

item& environment::getthings(int index){
	return things[index];
}

void environment::removeitem(item& b){
	int i,j;
	bool flag=false;
	for(i=0;i<position;i++)
	{
	  if(things[i].getname()==b.getname())
	  {
	  	flag=true;
	  	if(i!=position-1)
	  	{
		  for(j=i;j<position-1;j++)
		  {
		  	things[j]=things[j+1];
		  }
        }
        else
        {
          things[i].getcode()=" ";
          things[i].getname()=" ";
		}
		position--;
		break;
	  }
	}
	if(!flag)
	{
	  cout<<"Αυτό το αντικείμενο δεν υπάρχει στο περιβάλλον\n";	
	}
}

void environment::printEnvironment(){
   for(int i=0;i<position;i++)
   {
   	 cout<<things[i]<<endl;
   }
}

item environment::searching(string name){
	for(int i=0;i<position;i++)
	{
		if(things[i].getname()==name)
		   return things[i];
	}
}

//Default Constructor, accessors and methods of class Player.

Player::Player(){
   bag=new item[N];
}

void Player::addItem(item& a){
 if(pos<N) 
 {
   bag[pos]=a;
   bag[pos].set_situation("inventory");
   pos++;	
 }
 else
   cout<<"Το σακίδιο του παίκτη είναι γεμάτο.Ρίξτε ή διαγράψτε κάποιο αντικείμενο."<<endl;
}

item& Player::getbag(int index){
	return bag[index];
}

int Player::getpos(){
	return pos;
}

void Player::pickitem(item& a,environment& era){
	int i,j;
	bool flag=false;
	for(i=0;i<era.getposition();i++)
	{
	   if(era.getthings(i).getname()==a.getname())
	   {
	   	 flag=true;
	   	 addItem(a);
	   	 if(i!=era.getposition()-1)
	   	 {
		   for(j=i;j<era.getposition();j++)
		   {
		     era.getthings(j)=era.getthings(j+1);	
		   }	
		 }
		 else
		 {
		 	era.getthings(i).getcode()=" ";
		 	era.getthings(i).getname()=" ";
		 }
		 int ps=era.getposition()-1;
		 era.setposition(ps);
		 break;
	   }
	}
	if(!flag)
	  cout<<"Δεν υπάρχει αυτό το αντικείμενο στο περιβάλλον\n";
}

void Player::setposition(int ps){
	pos=ps;
}

void Player::removeItem(item& b){
	int i,j;
	bool flag=false;
	for(i=0;i<pos;i++)
	{
	  if(bag[i].getname()==b.getname())
	  {
	  	flag=true;
	  	if(i!=pos-1)
	  	{
		  for(j=i;j<pos-1;j++)
		  {
		  	bag[j]=bag[j+1];
		  }
        }
        else
        {
          bag[i].getcode()=" ";
          bag[i].getname()=" ";
		}
		pos--;
		break;
	  }
	}
	if(!flag)
	{
	  cout<<"Αυτό το αντικείμενο δεν υπάρχει στο σακίδιο του παίκτη\n";	
	}
}

void Player::printbag(){
  for(int i=0;i<pos;i++)
    cout<<bag[i]<<endl;
}

ostream& operator<<(ostream& left,const Player& right){
	for(int k=0;k<right.pos;k++)
	  left<<right.bag[k]<<endl;
	return left;
}

void Player::dropItem(item& a,environment& era){
	int k,j;
	bool flag=false;
	for(k=0;k<pos;k++)
	{
	  if(bag[k].getname()==a.getname())
	  {
	  	flag=true;
	  	era.additem(a);
	  	if(k!=pos-1)
	  	{
	  	  for(j=k;j<pos-1;j++)
		  {
		    bag[j]=bag[j+1];	  
		  }	
		}
		else
		{
		  bag[k].getname()=" ";
		  bag[k].getcode()=" ";
		}
		pos--;
		break;
	  }
	}
}

void Player::crafting(item& a,item& b,Player& p){
	item result;
	char ans;
	if(pos>1)
	{
	  if(a.getsituation()=="inventory" && b.getsituation()=="inventory")
	  {
	  	 result=a+b;
	  	 if(result.getname()!=" ")
	  	 {
	  	   	p.removeItem(a);
	  	   	p.removeItem(b);
	  	   	p.addItem(result);
		 }
		  cout<<"Επιτυχής συνδυασμός αντικειμένων!Φτιάξατε "<<result.getname()<<".\n";
		  if(result.getname()=="pickaxe")
		  {
		  	cout<<"Συγχαρητήρια!Κερδίσατε.\nΘέλετε να συνεχίσετε?\n";
		  	cin>>ans;
		  	if(ans=='N' || ans=='n')
		  	  exit(1);
		  }
	  }
	  else
	    cout<<"Δεν υπάρχει/ουν κάποιο/α από τα αντικείμενα στο σακίδιο σας.\n";
	}
}

item Player::searching(string name){
	for(int i=0;i<pos;i++)
	{
		if(bag[i].getname()==name)
		   return bag[i];
	}
}

int main()
{
  system("chcp 1253");
  system("cls");
  ifstream infile;
  ofstream outfile;
  string code,name,place;
  item obj;
  environment game;
  Player petros;
  game.setposition(0);
  petros.setposition(0);
  int ch;
  char ans;
  infile.open("items.txt");
  // Load data from items.txt.
  if(infile.is_open())
  {
    while(!infile.eof())
    {
  	 getline(infile,code,',');
  	 getline(infile,name,',');
  	 getline(infile,place,'\n');
  	 obj.set_values(code,name);
  	 obj.set_situation(place);
  	 if(place=="environment")
  	 {
  	   game.additem(obj);
	 }
	 else
	 {
	   petros.addItem(obj);
	 }
    }
  }
  infile.close();
  // Menu, which refers to actions of user for the game.
  while(1)
  {
    cout<<"+------------------------------------------------------------------+"<<endl;
	cout<<"|                        Adventure Game                            |"<<endl;
    cout<<"+------------------------------------------------------------------+"<<endl;
    cout<<"|1)Προβολή σακιδίου παίκτη                                         |"<<endl;
    cout<<"|2)Προβολή αντικειμένων περιβάλλοντος                              |"<<endl;
    cout<<"|3)Eπιλογή αντικειμένου από περιβάλλον                             |"<<endl;
    cout<<"|4)Πέταξε αντικείμενο στο περιβάλλον                               |"<<endl;
    cout<<"|5)Συνδύασε 2 αντικείμενα για να φτιάξεις ένα καινούριο αντικείμενο|"<<endl;
    cout<<"|6)Aποθήκευση παιχνιδιού                                           |"<<endl;
    cout<<"|7)Επανεκκίνηση παιχνιδιού                                         |"<<endl;
    cout<<"|8)Έξοδος παιχνιδιού                                               |"<<endl;
    cout<<"+------------------------------------------------------------------+"<<endl;
    cout<<"Επιλέξτε μία από τις παραπάνω επιλογές: "<<endl;
    cin>>ch;
    switch(ch)
    {
      case 1:
      {
	    petros.printbag();
      }
	  break;
	  case 2:
	  {
	  	game.printEnvironment();
	  }
	  break;
	  case 3:
	  {
	   cout<<"Πληκτρολογήστε το όνομα του αντικειμένου περιβάλλοντος: ";
	   cin>>name;
	   obj=game.searching(name);
	   petros.pickitem(obj,game);
      }
	  break;
	  case 4:
	  {
	    cout<<"Ποιο αντικείμενο επιθυμείτε να πετάξετε;\n";
	    cin>>name;
	    obj=petros.searching(name);
	    petros.dropItem(obj,game);
	  }
	  break;
	  case 5:
	  {
	    string name1,name2;
	    cout<<"Δώστε ονόματα δύο αντικειμένων:";
	    cin>>name1;
	    cin>>name2;
	    item obj1=petros.searching(name1);
	    item obj2=petros.searching(name2);
	    petros.crafting(obj1,obj2,petros);
      }
	  break;
	  case 6:
	  {
	   char *filename=new char[1024];
	   cout<<"Δώστε όνομα αρχείου: ";
	   cin>>filename;
	   outfile.open(filename,ios::out);
	   outfile<<"  Αντικείμενα στο περιβάλλον  "<<endl;
	   outfile<<"------------------------------"<<endl;
	   for(int i=0;i<game.getposition();i++)
	   {
	  	 outfile<<game.getthings(i)<<endl;
	   }
	   outfile<<"   Σακίδιο του παίκτη    "<<endl;
	   outfile<<"-------------------------"<<endl;
	   for(int j=0;j<petros.getpos();j++)
	      outfile<<petros.getbag(j)<<endl;
	   outfile.close();
      }
	  break;
	  case 7:
	  {
	   cout<<"Είσαι σίγουρος ότι θέλεις να επανεκκινήσεις το παιχνίδι;(Θα χάθει η πρόοδος του παιχνιδιού)"<<endl;
	   cin>>ans;
	   if(ans=='Y' || ans=='y')
	   {
	   ifstream infile1;
	   game.setposition(0);
	   petros.setposition(0);
	   for(int i=0;i<N;i++)
	   {
	   	 petros.getbag(i).getname()=" ";
	   	 petros.getbag(i).getcode()=" ";
	   }
	   for(int j=0;j<100;j++)
	   {
	   	 game.getthings(j).getname()=" ";
	   	 game.getthings(j).getcode()=" ";
	   }
	   infile1.open("items.txt");
	   if(infile1.is_open())
	   {
	    	while(!infile1.eof())
	  	    {
	          getline(infile1,code,',');
			  getline(infile1,name,',');
			  getline(infile1,place,'\n');
			  obj.set_values(code,name);
			  obj.set_situation(place);
			  if(place=="environment")
  	          {
  	              game.additem(obj);
	          }
	          else
	          {
	              petros.addItem(obj);
	          }
	     	}
	   }
      }
	 }
	  break;
	  case 8:
	  {
	  	cout<<"Είσαι σίγουρος ότι θέλεις να φύγεις από το παιχνίδι;(Θα χαθεί η πρόοδος του παιχνιδιού)"<<endl;
	  	cin>>ans;
	  	if(ans=='Y' || ans=='y')
	  	{
	  	  exit(1);	
		}  
	  }
	  break;
	  default:
	  	cout<<"Δεν υπάρχει η επιλογή "<<ch<<".Δοκιμάστε άλλη επιλογή"<<endl;
	}
  }
  return 0;
}
