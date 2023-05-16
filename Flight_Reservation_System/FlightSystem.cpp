#include <iostream>
#include <cstring>
#include <time.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int R     =     15;
const int C     =     6;

const int NF    =     20;
int     SF      =   0;

void storePassengerIntoFile();
void loadPassengerFromFile();
void displayDestinations();
void storeRouteIntoFile();
void storeBookingIntoFile();
void loadBookingFromFile();
void loadRouteFromFile();
void displayRoutes();
void storeDestIntoFile();
void storeFSIntoFile();
void displayFlightSchedules();
bool searchAndDisplayFlightSchedules();

class Login
{

    public:
    string username;
    string password;
    void getUserNamePassword(string &un, string &pwd)
    {
        un  =   username;
        pwd =   password;
    }
    void setUserNamePassword(string un, string pwd)
    {
        username    =   un;
        password    =   pwd;
    }
};

class PassengerLogin : public Login
{
    public:

    string name;
    string CNIC;
    string passport =   "-";

    void myBookings()
    {
	}
	void reserveSeat()
	{
	}
};
class AdminLogin : public Login
{
    public:

    string name;
    void addRoutes()
    {

    }
    void restrictPassenger()
    {

    }
    void updateFlightSchedule()
    {

    }
    void updateInquiry()
    {

    }
};
vector <PassengerLogin> psgList;
vector <AdminLogin> adminList;
void passengerMenu(PassengerLogin a, int i);

class Destination
{
    public:
        string destCode;
        string airportName;
        string cityName;
        string countryName;

};
vector <Destination> destList;

class Route
{
	public:
	    string flightNo;
		Destination flightFrom;
    	Destination flightTo;
	    string flightCategory;
//	    string fn 	=	to_string(flightNo);
		string toString()
		{
			string s 	=	"";
			s	+=	"\n"+flightCategory+"flight with Flight Number: "+flightNo+"\nDeparture from "+flightFrom.airportName+" at "+flightFrom.cityName+", "+flightFrom.countryName+" -> to ";
			s	+=	flightTo.airportName+" at "+flightTo.cityName+", "+flightTo.countryName;
		}

};
class FlightSchedule
{
    public:
	Route r;
	string ID;
	char seats[R][C];
	int Seats_Available =   R * C;

    struct tm dept;
    struct tm arr;

    double flightDuration()
    {
        return difftime(mktime(&arr),mktime(&dept))/3600.0;
    }

    void initializeSeats () {
	    for (int r=0; r<R; r++) {
	    	for (int s=0; s<C; s++)
		    	seats[r][s] = 'A' + s;
	    }
    }

///// DisplaySeats Function
    void DisplaySeats () {
    	for (int r=0; r<R; r++) {
	    	for (int s=0; s<C; s++)
		    {
			    if(seats[r][s] != '-')
			        cout <<(r+1);
    			cout<< seats[r][s] << '\t';
	    	}
		    cout << endl;
    	}
    }

    string reserveSeat()
    {
    	int row;
	    int seat;
	    char cseat,answer;
	    string seatNumber =	"-";
	    DisplaySeats();
     	do
     	{
    		    if(Seats_Available == 0)
    		    {
    		        cout <<"\nNo more seats available in this flight." << endl;
                    break;
    		    }
    			cout << endl;
    			cout << Seats_Available << " seats are available: "<<endl;
    			cout << "Please enter a seat selection in the format -- Row number(Space)Seat number  (Example 5 F): " << endl;
    			cin >> row>>cseat;
    			row--;
    			seat    =   toupper(cseat);
    			seat    -=  'A';
    			if(row < 0 || row >= R || seat < 0 || seat > C-1)
    				cout << "Selected seat is not valid. Try a different seat number.." << endl;
    			else
    			{
        			if (seats[row][seat] == '-')
    					cout << "The seat you selected has already been taken. Please try another seat." <<endl;
    				else
    				{
    					seats[row][seat] = '-';
    					Seats_Available--;
    					seatNumber 	=	to_string(row+1)+(char)('A'+seat);
    				}
       			    break;
    			}
    		}while (1);
    	return 	seatNumber;
    }
};
vector <Route> routeList;
vector <FlightSchedule> fsList;

class Payment
{
	public:
	double amount;
	string paymentType;
};
class Booking
{
	public:
	string flightID;
	string CNIC;
	string seatNumber;
	string visaNumber 	=	"";
	Payment p;
	void searchAndManageResearvtion(string cnic)
	{
		string frn;
		char mode;
		bool match;
		int i;
		system("CLS");
	    cout<<"************************************************************************************\n\n";
	    cout<<"\t\t\t\tWelcome to Our Booking System\n";
	    cout<<"\n************************************************************************************\n\n";
		match = searchAndDisplayFlightSchedules();
		if(!match)
			return;
		REDOB:
		cout<<"\nPlease enter the Flight Reference Number to book: ";
		cin>>frn;
		if(frn == "Q" || frn == "q")
			return;
		for(i=0;i<fsList.size();i++)
		{
			if(fsList[i].ID == frn)
				break;
		}
		if(i==fsList.size())
		{
			cout<<"Invalid Flight Reference Number Entered.. Please try again of press Q/q to exit: ";
			goto REDOB;
		}
		seatNumber 	=	fsList[i].reserveSeat();
		flightID 	=	frn;
		CNIC 		=	cnic;
		double rate,taxrate = 0.05;
		Route r;
		if(fsList[i].r.flightCategory == "International")
		{
			cout<<"\nPlease enter your visa number for "<<fsList[i].r.flightTo.countryName<<" as it is mandatory requirement: ";
			cin>>visaNumber;
			rate 	=	20000;
			taxrate =	0.1;
		}
		else
			rate 	=	10000;
		cout<<"\nThe flight duration: "<<fsList[i].flightDuration();
		p.amount 	=	rate * fsList[i].flightDuration();
		cout<<"\nTicket Price: "<<p.amount;
		cout<<"\nTaxes: \t"<<p.amount*taxrate;
		p.amount+=p.amount*taxrate;
		cout<<"\nFor confirming reservation, payment due: "<<p.amount;
		cout<<"\nPlease select your mode of payment:\n1.\t Credit Card\n2.\tCash\n";
		cin>>mode;
		switch(mode)
		{
			case '1':
				p.paymentType 	=	"Credit Card";
				break;
			case '2':
				p.paymentType 	=	"Cash";
				break;
			default:
				cout<<"Invalid Option Selected.. try again...";
		}
	}

	void manageResearvtion(string cnic)
	{
		string frn;
		char mode;
		int i;
		system("CLS");
	    cout<<"************************************************************************************\n\n";
	    cout<<"\t\t\t\tWelcome to Our Booking System\n";
	    cout<<"\n************************************************************************************\n\n";
		displayFlightSchedules();
		REDOB:
		cout<<"\nPlease enter the Flight Reference Number to book: ";
		cin>>frn;
		if(frn == "Q" || frn == "q")
			return;
		for(i=0;i<fsList.size();i++)
		{
			if(fsList[i].ID == frn)
				break;
		}
		if(i==fsList.size())
		{
			cout<<"Invalid Flight Reference Number Entered.. Please try again of press Q/q to exit: ";
			goto REDOB;
		}
		seatNumber 	=	fsList[i].reserveSeat();
		flightID 	=	frn;
		CNIC 		=	cnic;
		double rate,taxrate = 0.05;
		Route r;
		if(fsList[i].r.flightCategory == "International")
		{
			cout<<"\nPlease enter your visa number for "<<fsList[i].r.flightTo.countryName<<" as it is mandatory requirement: ";
			cin>>visaNumber;
			rate 	=	20000;
			taxrate =	0.1;
		}
		else
			rate 	=	10000;
		cout<<"\nThe flight duration: "<<fsList[i].flightDuration();
		p.amount 	=	rate * fsList[i].flightDuration();
		cout<<"\nTicket Price: "<<p.amount;
		cout<<"\nTaxes: \t"<<p.amount*taxrate;
		p.amount+=p.amount*taxrate;
		cout<<"\nFor confirming reservation, payment due: "<<p.amount;
		cout<<"\nPlease select your mode of payment:\n1.\t Credit Card\n2.\tCash\n";
		cin>>mode;
		switch(mode)
		{
			case '1':
				p.paymentType 	=	"Credit Card";
				break;
			case '2':
				p.paymentType 	=	"Cash";
				break;
			default:
				cout<<"Invalid Option Selected.. try again...";
		}
	}
};
vector <Booking> bList;

void addDestination()
{
	Destination d;
	cin.ignore(1);
	cout<<"\nPlease enter the Airport Name: ";
	getline(cin,d.airportName);
	cout<<"\nPlease enter the City Name: ";
	getline(cin,d.cityName);
	cout<<"\nPlease enter the Country Name: ";
	getline(cin,d.countryName);

	destList.push_back(d);
	storeDestIntoFile();

}
void addRoute()
{
	Route r;
	int i,j;
	cout<<"\nPlease enter the flight number: ";
	cin>>r.flightNo;
	displayDestinations();
	REDO:
	cout<<"\nSelect Destination Number from above list to identify the Departure Airport: ";
	cin>>i;
	cout<<"\nSelect Destination Number from above list to identify the Arrival Airport: ";
	cin>>j;

	if(i==j)
	{
		cout<<"Departure and Arrival Airports can not be same.. Please try again..";
		goto REDO;
	}
	r.flightFrom	=	destList[i-1];
	r.flightTo		=	destList[j-1];
	if(r.flightFrom.countryName == r.flightTo.countryName)
		r.flightCategory	=	"Domestic";
	else
		r.flightCategory	=	"International";

	routeList.push_back(r);
	storeRouteIntoFile();
}
void addFlightSchedule()
{
	FlightSchedule fs;
	string flightNo;
	int i,j;
	REDO:
	displayRoutes();
	cout<<"\n\nPlease enter the Route number: ";
	cin>>flightNo;

	if(flightNo == "Q" || flightNo == "q")
		return;
	for(i=0;i<routeList.size();i++)
	{
		if(flightNo == routeList[i].flightNo)
			break;
	}
/*	REDO:
	cout<<"\nSelect Destination Number from above list to identify the Departure Airport: ";
	cin>>i;
	cout<<"\nSelect Destination Number from above list to identify the Arrival Airport: ";
	cin>>j;

	if(i==j)
	{
		cout<<"Departure and Arrival Airports can not be same.. Please try again..";
		goto REDO;
	}
*/
	if(i==routeList.size())
	{
		cout<<"\nInvalid Flight No. entered... Please try again or enter 'Q' to return to main menu..";
		goto REDO;
	}
	fs.r 			=	routeList[i];
	cout<<"\nPlease specify the departure time in the format (DD MM YYYY HH MM)";
	cin>>fs.dept.tm_mday>>fs.dept.tm_mon>>fs.dept.tm_year>>fs.dept.tm_hour>>fs.dept.tm_min;
	cout<<"\nPlease specify the arrival time in the format (DD MM YYYY HH MM)";
	cin>>fs.arr.tm_mday>>fs.arr.tm_mon>>fs.arr.tm_year>>fs.arr.tm_hour>>fs.arr.tm_min;
	fs.ID	=	fs.r.flightNo+to_string(fs.dept.tm_year)+to_string(fs.dept.tm_mon)+to_string(fs.dept.tm_mday);
	fs.initializeSeats();
	fs.dept.tm_year-=1900;
	fs.arr.tm_year-=1900;

	cout<<"\nPlease enter the number of available seats (Maximum seats: "<<R*C<<"): ";
	cin>>fs.Seats_Available;
	fsList.push_back(fs);
	storeFSIntoFile();
}
void adminMenu(AdminLogin a, int i);

///// InitializeSeats Function
FlightSchedule f[NF];

string timeToString(struct tm dept)
{
	string s 	=	"";
	s	=	to_string(dept.tm_hour)+":"+to_string(dept.tm_min)+"\t"+to_string(dept.tm_mday)+"/"+to_string(dept.tm_mon)+"/"+to_string(dept.tm_year+1900);
	return s;
}
string readpwd(int i)
{
   	pwdREDO:
	string pwd ="";
	bool lc 	=	false,uc	=	false, dc	=	false, sc 	=	false;;
   	char c;
   	if(i==1)
   		cout << "\nPlease enter your password: ";
   	else
   		cout << "\nPlease re-enter your password.. Make sure it is exactly the same as your previous entry..: ";
	c = _getch();
   	while(c != 13){//character 13 is enter
    	pwd.push_back(c);
		cout<<'*';
    	if(c>=65 && c<=90)
			uc 	=	true;
    	if(c>=97 && c<=122)
			lc 	=	true;
    	if(c>=48 && c<=57)
			dc 	=	true;
		if(!(c>=65 && c<=90) && !(c>=97 && c<=122) && !(c>=48 && c<=57))
			sc 	=	true;
    	c = _getch();

   	}
   	if(i==1)
   	{
		if(uc && lc && dc && sc && pwd.size()>=8)
   			return pwd;
   		else
		{
			cout<<"\nPassword doesnt meet minimum security requirements... please try again\nPlease ";
			goto pwdREDO;
		}
	}
	else
		return pwd;
}


string doubleVerifiedPwd()
{
	string pwd1,pwd2;
   	while(1)
    {
	    pwd1 	=	readpwd(1);
	    pwd2 	=	readpwd(2);
	    if(pwd1 == pwd2)
	    {
		   	cout<<"\nPassword Matched..";
		   	break;
	    }else
	    	cout<<"\nPasswords Mismatched... please reenter the passwords: ";
	}
	return pwd1;
}

void loginPassenger()
{
	string un,pwd;
	cout<<"\n\nPlease enter your username: ";
	cin>>un;
	pwd	 	=	readpwd(1);
//	cout<<"\n\nPlease enter your password: ";
//	cin>>pwd;

	for(int i=0;i<psgList.size();i++)
	{
		if(psgList[i].username == un && psgList[i].password == pwd)
		{
			passengerMenu(psgList[i],i);
			return;
		}
	}
	cout<<"\nInvalid Username OR Password...\n";
}

void loginAdmin()
{
	string un,pwd;
	cout<<"\n\nPlease enter your username: ";
	cin>>un;
	pwd 	=	readpwd(1);
//	cout<<"\n"<<adminList.size()<<" adminsitrators in database ";
	for(int i=0;i<adminList.size();i++)
	{
//		cout<<adminList[i].username<<"\t"<<adminList[i].password<<"\n";
		if(adminList[i].username == un && adminList[i].password == pwd)
		{
			adminMenu(adminList[i],i);
			return;
		}
	}
	cout<<"\nInvalid Username OR Password...\n";
	system("PAUSE");
}
void signinPassenger()
{
    PassengerLogin p;
    system("CLS");
    string un,pwd;
    cout<<"*******************************************************************************\n\n";
    cout<<"\t\t\t\tWelcome to New-Pak Airline Flight System\n";
    cout<<"\n*******************************************************************************\n\n";
    cout<<"*********************************PASSENGER SIGNIN************************************\n\n";
    CNICREDO:
	cout<<"Please enter your CNIC without '-':";
    cin>>p.CNIC;
    if(p.CNIC.size() != 13)
    {
    	cout<<"\nInvalid CNIC entered. CNIC shall contain 13 digits. Try again.";
    	goto CNICREDO;
	}
    cin.ignore(1);
    cout<<"Please enter your name:";
    getline(cin,p.name);
    cout<<"Please enter your passport number:";
    cin>>p.passport;
    cout<<"Please enter your username:";
    cin>>un;
 	pwd 	=	doubleVerifiedPwd();
    p.setUserNamePassword(un,pwd);
    psgList.push_back(p);
    storePassengerIntoFile();
	system("PAUSE");
}
void loadPassengerFromFile()
{
    ifstream pf("Passenger.txt");
    PassengerLogin p;
    if (pf.is_open())
    {
        string line;
        while( getline(pf,line) )
        {
            stringstream ss(line);

            getline(ss,p.CNIC,',');
            getline(ss,p.username,',');
            getline(ss,p.password,',');
            getline(ss,p.passport,',');
            getline(ss,p.name,',');
            psgList.push_back(p);
        }
    }

}
void loadDestFromFile()
{
    ifstream pf("Destinations.txt");
    Destination d;
    if (pf.is_open())
    {
        string line;
        while( getline(pf,line) )
        {
            stringstream ss(line);

            getline(ss,d.airportName,',');
            getline(ss,d.cityName,',');
            getline(ss,d.countryName,',');
            destList.push_back(d);
        }
    }
}
void storeDestIntoFile()
{
   	ofstream pf("Destinations.txt");
    Destination d;
    if (pf.is_open())
    {
    	for(int i=0;i<destList.size();i++)
    	{
			d 	=	destList[i];
		    pf<<d.airportName<<","<<d.cityName<<","<<d.countryName<<"\n";
		}
    }
}
void loadRoutesFromFile()
{
    ifstream pf("Routes.txt");
    Route r;
    if (pf.is_open())
    {
        string line;
        while( getline(pf,line) )
        {
//        	cout<<"\n"<<line;
            stringstream ss(line);

            getline(ss,r.flightNo,',');
            getline(ss,r.flightCategory,',');
            getline(ss,r.flightFrom.airportName,',');
            getline(ss,r.flightFrom.cityName,',');
            getline(ss,r.flightFrom.countryName,',');
            getline(ss,r.flightTo.airportName,',');
            getline(ss,r.flightTo.cityName,',');
            getline(ss,r.flightTo.countryName,',');
           routeList.push_back(r);
        }
    }
    system("PAUSE");
}
void storeRouteIntoFile()
{
   	ofstream pf("Routes.txt");
    Route r;
    if (pf.is_open())
    {
    	for(int i=0;i<routeList.size();i++)
    	{
			r 	=	routeList[i];
		    pf<<r.flightNo <<"," <<r.flightCategory<<","<<r.flightFrom.airportName<<","<<r.flightFrom.cityName<<","<<r.flightFrom.countryName<<","<<r.flightTo.airportName<<","<<r.flightTo.cityName<<","<<r.flightTo.countryName<<"\n";
		}
    }
}
void loadBookingFromFile()
{
    ifstream pf("Bookings.txt");
    string s;
    Booking b;
    if (pf.is_open())
    {
        string line;
        cout<<line<<"\n";
        while( getline(pf,line) )
        {
            stringstream ss(line);

            getline(ss,b.CNIC,',');
            getline(ss,b.flightID,',');
            getline(ss,b.seatNumber,',');
            getline(ss,s,',');
			b.p.amount 	=	stod(s);
            getline(ss,b.p.paymentType,',');
            getline(ss,b.visaNumber,',');
            bList.push_back(b);
        }
    }
}
void storeBookingIntoFile()
{
   	ofstream pf("Bookings.txt");
    Booking b;
    if (pf.is_open())
    {
    	for(int i=0;i<bList.size();i++)
    	{
			b 	=	bList[i];
		    pf<<b.CNIC <<"," <<b.flightID<<","<<b.seatNumber<<","<<b.p.amount<<","<<b.p.paymentType<<","<<b.visaNumber<<"\n";
		}
    }
}
void storeFSIntoFile()
{
   	ofstream pf("FlightSchedules.txt");
    FlightSchedule fs;
    if (pf.is_open())
    {
    	for(int i=0;i<fsList.size();i++)
    	{
			fs 	=	fsList[i];
		    pf<<fs.ID <<"," <<fs.r.flightNo<<","<<fs.Seats_Available<<","<<fs.dept.tm_year<<","<<fs.dept.tm_mon<<","<<fs.dept.tm_mday<<","<<fs.dept.tm_hour<<","<<fs.dept.tm_min
				<<","<<fs.arr.tm_year<<","<<fs.arr.tm_mon<<","<<fs.arr.tm_mday<<","<<fs.arr.tm_hour<<","<<fs.arr.tm_min;
			for(int j=0;j<R;j++)
			{
				for(int k=0;k<C;k++)
				{
					pf<<","<<fs.seats[j][k];
				}
			}
			pf<<"\n";
		}
    }
}
void loadFSFromFile()
{
	string flightNo;
	string t;
	time_t now1;
	time_t now2;

   	ifstream pf("FlightSchedules.txt");
    if (pf.is_open())
    {
        string line;
        while( getline(pf,line) )
        {
//        	cout<<"\n"<<line;
            stringstream ss(line);
		    FlightSchedule fs;

            getline(ss,fs.ID,',');
            getline(ss,flightNo,',');
            getline(ss,t,',');
            fs.Seats_Available 	=	stoi(t);
           for(int x=0;x<routeList.size();x++)
            	if(routeList[x].flightNo == flightNo)
            		fs.r 	=	routeList[x];
            getline(ss,t,',');
		  	time(&now1);  /* get current time; same as: now = time(NULL)  */
  			time(&now2);  /* get current time; same as: now = time(NULL)  */

            fs.dept 			=	*localtime(&now1);
            fs.dept.tm_year 	=	stoi(t);
            getline(ss,t,',');
            fs.dept.tm_mon		=	stoi(t);
            getline(ss,t,',');
            fs.dept.tm_mday		=	stoi(t);
            getline(ss,t,',');
            fs.dept.tm_hour		=	stoi(t);
            getline(ss,t,',');
            fs.dept.tm_min		=	stoi(t);
            getline(ss,t,',');
            fs.arr	 			=	*localtime(&now2);
            fs.arr.tm_year 		=	stoi(t);
            getline(ss,t,',');
            fs.arr.tm_mon		=	stoi(t);
            getline(ss,t,',');
            fs.arr.tm_mday		=	stoi(t);
            getline(ss,t,',');
            fs.arr.tm_hour		=	stoi(t);
            getline(ss,t,',');
            fs.arr.tm_min		=	stoi(t);
			for(int j=0;j<R;j++)
			{
				for(int k=0;k<C;k++)
				{
					getline(ss,t,',');
					fs.seats[j][k] 	=	t[0];
				}
			}
//			cout<<"\n"<<fs.ID<<"\t"<<fs.flightDuration();
		    fsList.push_back(fs);
        }
    }
}
void displayFlightSchedules()
{
	FlightSchedule fs;
	cout<<setw(17)<<"Flight Ref."<<setw(12)<<"Flight No."<<setw(15)<<"Domes / Intl. "<<setw(40)<<"DEAPRTURE AIRPORT"<<setw(50)<<"Arrival AIRPORT"<<setw(20)<<"Departure Time\n";
	cout<<"_______________________________________________________________________________________________________________________________________________________________________________________________________________\n";
	for(int i=0;i<fsList.size();i++)
	{
		fs	=	fsList[i];
    	cout<<setw(17)<<fs.ID <<setw(12)<<fs.r.flightNo <<setw(15)<<fs.r.flightCategory<<setw(40)<<(fs.r.flightFrom.airportName+", "+fs.r.flightFrom.cityName+", "+fs.r.flightFrom.countryName)<<setw(50)<<(fs.r.flightTo.airportName+", "+fs.r.flightTo.cityName+", "+fs.r.flightTo.countryName)<<setw(20)<<timeToString(fs.dept)<<"\n";
	}
}
bool searchAndDisplayFlightSchedules()
{
	string deptcity,arrcity;
	bool match 	=	false;
	cout<<"\nPlease enter your city of departure: ";
	cin>>deptcity;
	cout<<"\nPlease enter your city of arrival: ";
	cin>>arrcity;

	FlightSchedule fs;

	for(int i=0;i<fsList.size();i++)
	{
		fs	=	fsList[i];
    	if(fs.r.flightFrom.cityName == deptcity && fs.r.flightTo.cityName == arrcity)
		{
			match = true;
		}
	}
	if(!match)
	{
		cout<<"\nNo flight scheduled as per your search....";
		return match;
	}
	cout<<setw(17)<<"Flight Ref."<<setw(12)<<"Flight No."<<setw(15)<<"Domes / Intl. "<<setw(40)<<"DEAPRTURE AIRPORT"<<setw(50)<<"Arrival AIRPORT"<<setw(20)<<"Departure Time\n";
	cout<<"_______________________________________________________________________________________________________________________________________________________________________________________________________________\n";
	for(int i=0;i<fsList.size();i++)
	{
		fs	=	fsList[i];
    	if(fs.r.flightFrom.cityName == deptcity && fs.r.flightTo.cityName == arrcity)
		{
		   	cout<<setw(17)<<fs.ID <<setw(12)<<fs.r.flightNo <<setw(15)<<fs.r.flightCategory<<setw(40)<<(fs.r.flightFrom.airportName+", "+fs.r.flightFrom.cityName+", "+fs.r.flightFrom.countryName)<<setw(50)<<(fs.r.flightTo.airportName+", "+fs.r.flightTo.cityName+", "+fs.r.flightTo.countryName)<<setw(20)<<timeToString(fs.dept)<<"\n";
		}
	}
	return match;
}
void bookFlight(string CNIC)
{
	string seatNum;
	double pay 	=	0.00;
	char mode;

	Booking	b;
	b.manageResearvtion(CNIC);
	if(b.seatNumber == "-")
		return;
	bList.push_back(b);
	storeBookingIntoFile();
	storeFSIntoFile();
}
void searchAndBookFlight(string CNIC)
{
	string seatNum;
	double pay 	=	0.00;
	char mode;

	Booking	b;
	b.searchAndManageResearvtion(CNIC);
	if(b.seatNumber == "-")
		return;
	bList.push_back(b);
	storeBookingIntoFile();
	storeFSIntoFile();
}

void displayRoutes()
{
	Route r;
	cout<<setw(12)<<"Flight No."<<setw(15)<<"Domes / Intl. "<<setw(70)<<"DEAPRTURE AIRPORT"<<setw(70)<<"Arrival AIRPORT\n";
	cout<<"_______________________________________________________________________________________________________________________________________________________________________________\n";
	for(int i=0;i<routeList.size();i++)
	{
		r	=	routeList[i];
    	cout<<setw(12)<<r.flightNo <<setw(15)<<r.flightCategory<<setw(70)<<(r.flightFrom.airportName+", "+r.flightFrom.cityName+", "+r.flightFrom.countryName)<<setw(70)<<(r.flightTo.airportName+", "+r.flightTo.cityName+", "+r.flightTo.countryName)<<"\n";
	}
}
void displayDestinations()
{
	cout<<setw(6)<<"Sr.#"<<setw(50)<<"AIRPORT NAME"<<setw(30)<<"CITY NAME"<<setw(30)<<"COUNTRY NAME\n";
	cout<<"_____________________________________________________________________________________________________________________\n";
	for(int i=0;i<destList.size();i++)
		cout<<setw(6)<<i+1<<setw(50)<<destList[i].airportName<<setw(30)<<destList[i].cityName<<setw(30)<<destList[i].countryName<<"\n";
	cout<<"\n";
}
void displayMyBookings(string CNIC)
{
	Booking b;

	cout<<setw(6)<<"Sr.#"<<setw(20)<<"CNIC"<<setw(15)<<"Flight ID"<<setw(20)<<"Seat Number"<<setw(20)<<"Payment Made"<<setw(20)<<"Payment Mode\n";
	cout<<"____________________________________________________________________________________________________________________________\n";
	for(int i=0;i<bList.size();i++)
	{
		if(bList[i].CNIC == CNIC)
			cout<<setw(6)<<i+1<<setw(20)<<bList[i].CNIC<<setw(15)<<bList[i].flightID<<setw(20)<<bList[i].seatNumber<<setw(20)<<bList[i].p.amount<<setw(20)<<bList[i].p.paymentType<<"\n";
	}
	cout<<"\n";
}
void loadAdminFromFile()
{
    ifstream pf("Administrator.txt");
    AdminLogin p;
    if (pf.is_open())
    {
        string line;
        while( getline(pf,line) )
        {
            stringstream ss(line);

            getline(ss,p.username,',');
            getline(ss,p.password,',');
            getline(ss,p.name,',');
            adminList.push_back(p);
        }
    }

}
void storePassengerIntoFile()
{
   ofstream pf("Passenger.txt");
    PassengerLogin p;
    if (pf.is_open())
    {

    	for(int i=0;i<psgList.size();i++)
    	{
			p 	=	psgList[i];
		    pf<<p.CNIC<<","<<p.username<<","<<p.password<<","<<p.passport<<","<<p.name<<"\n";
		}
    }
}
void storeAdminIntoFile()
{
    ofstream pf("Administrator.txt");
    AdminLogin p;
    if (pf.is_open())
    {
    	for(int i=0;i<adminList.size();i++)
    	{
			p 	=	adminList[i];
		    pf<<p.username<<","<<p.password<<","<<p.name<<"\n";
		}
    }

}
void displayAllPassengers()
{
	PassengerLogin p;
    cout<<"*******************************************************************************\n\n";
    cout<<"\t\t\t\tList of Passengers\n";
    cout<<"\n*******************************************************************************\n\n";
	string un,pwd;
	for(int i=0;i<psgList.size();i++)
	{
		p 	=	psgList[i];
		//p.getUserNamePassword(un,pwd);
		cout<<p.name<<"\t"<<p.CNIC<<"\t"<<p.passport<<"\n";
	}
}

void adminMenu(AdminLogin a, int i)
{
	string pwd;
	while(1)
	{
		char opt;
	    system("CLS");
	    cout<<"********************************************************************************************************\n\n";
	    cout<<"\t\t\t\tWelcome "<<a.name<<" to New-Pak Airline Flight System\n";
	    cout<<"\n********************************************************************************************************\n\n";
	    cout<<"**********************************ADMIN MENU OPTIONS**********************************************************\n\n";
	    cout<<"1.\tAdd Flight Schedule\n";
	    cout<<"--------------------------------\n";
	    cout<<"2.\tAdd New Routes\n";
	    cout<<"--------------------------------\n";
	    cout<<"3.\tAdd New Destination\n";
	    cout<<"--------------------------------\n";
	    cout<<"4.\tDisplay All Scheduled Flights\n";
	    cout<<"--------------------------------\n";
	    cout<<"5.\tDisplay All Routes\n";
	    cout<<"--------------------------------\n";
	    cout<<"6.\tDisplay All Destinations\n";
	    cout<<"--------------------------------\n";
	    cout<<"7.\tChange Password\n";
	    cout<<"--------------------------------\n";
	    cout<<"8.\tReturn to Main Menu\n";
	    cout<<"--------------------------------\n";
	    cin>>opt;


	    switch(opt)
	    {
	    	case '1':
				addFlightSchedule();
				break;
			case '2':
				addRoute();
				system("pause");
				break;
			case '3':
				addDestination();
				system("pause");
				break;
			case '4':
				displayFlightSchedules();
				system("pause");
				break;
			case '5':
				displayRoutes();
				system("pause");
				break;
			case '6':
				displayDestinations();
				system("pause");
				break;
			case '7':
				pwd 	=	doubleVerifiedPwd();
				adminList[i].password	=	pwd;
				storeAdminIntoFile();
				system("pause");
				break;
			case '8':
				return;
			default:
				cout<<"Invalid Option Selected, please try again... ";
				system("pause");
		}
	}
}

void passengerMenu(PassengerLogin a, int i)
{
	string pwd;
	while(1)
	{
		char opt;
	    system("CLS");
	    cout<<"********************************************************************************************************\n\n";
	    cout<<"\t\t\t\tWelcome "<<a.name<<"("<<a.CNIC<<") to New-Pak Airline Flight System\n";
	    cout<<"\n********************************************************************************************************\n\n";
	    cout<<"**********************************PASSENGER MENU OPTIONS****************************************************\n\n";
	    cout<<"1.\tBook Flight\n";
	    cout<<"--------------------------------\n";
	    cout<<"2.\tDisplay All Scheduled Flights\n";
	    cout<<"--------------------------------\n";
	    cout<<"3.\tDisplay All Routes\n";
	    cout<<"--------------------------------\n";
	    cout<<"4.\tDisplay All Destinations\n";
	    cout<<"--------------------------------\n";
	    cout<<"5.\tDisplay My Bookings\n";
	    cout<<"--------------------------------\n";
	    cout<<"6.\tSearch and Book Flights\n";
	    cout<<"--------------------------------\n";
	    cout<<"7.\tChange Password\n";
	    cout<<"--------------------------------\n";
	    cout<<"8.\tReturn to Main Menu\n";
	    cout<<"--------------------------------\n";
	    cout<<"--------------------------------\n\n";
	    cout<<"Please Select your option: "; cin>>opt;


	    switch(opt)
	    {
	    	case '1':
				bookFlight(a.CNIC);
				break;
			case '2':
				displayFlightSchedules();
				system("pause");
				break;
			case '3':
				displayRoutes();
				system("pause");
				break;
			case '4':
				displayDestinations();
				system("pause");
				break;
			case '5':
				displayMyBookings(a.CNIC);
				system("pause");
				break;
			case '6':
				searchAndBookFlight(a.CNIC);
				system("pause");
				break;
			case '7':
				pwd 	=	doubleVerifiedPwd();
				psgList[i].password	=	pwd;
				storePassengerIntoFile();
				system("pause");
				break;
			case '8':
				return;
			default:
				cout<<"Invalid Option Selected, please try again... ";
				system("pause");
		}
	}
}

void mainMenu()
{
	char opt;
    system("CLS");
    cout<<"*******************************************************************************\n\n";
    cout<<"\t\t\t\tWelcome to New-Pak Airline Flight System\n";
    cout<<"\n*******************************************************************************\n\n";
    cout<<"**********************************MENU OPTIONS***********************************\n\n";
    cout<<"1.\tLogin as Passenger\n";
    cout<<"--------------------------------\n";
    cout<<"2.\tSignin as New Passenger\n";
    cout<<"--------------------------------\n";
    cout<<"3.\tLogin as Administrator\n";
    cout<<"--------------------------------\n";
    cout<<"4.\tExit\n";
    cout<<"--------------------------------\n";
    cin>>opt;


    switch(opt)
    {
    	case '1':
			loginPassenger();
			break;
		case '2':
			signinPassenger();
			break;
		case '3':
			loginAdmin();
			break;
		case '4':
			cout<<"\nThank you for using our Airline Researvation System, See you soon... BYE!!!";
			exit(0);
		default:
			cout<<"Invalid Option Selected, please try again... ";
			system("pause");
	}
}

int main()
{
	loadPassengerFromFile();
	loadAdminFromFile();
	loadDestFromFile();
	loadRoutesFromFile();
	loadFSFromFile();
	loadBookingFromFile();

//	displayAllPassengers();

/*    FlightSchedule f[NF];
    f[0].flightNo   =   1045;
    f[0].initializeSeats();
    f[0].reserveSeat();
    f[1].flightNo   =   1100;
    f[1].initializeSeats();
    f[1].reserveSeat();
    f[0].reserveSeat();

    cout<<"Hello World";
    system("clear");
*/    while(1)
		mainMenu();

	return 0;
}





