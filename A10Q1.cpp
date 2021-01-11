/*
Elizabeth Shim
December 3rd, 2020
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

class Park
{
	private:
		string name;
		double longitude, latitude;
		int visit;
	
	public:
		Park ()
		{
			name = " ";
			longitude = 0;
			latitude = 0;
			visit = 0;
		}
		
		Park (string parkName, double parkLongitude,
				double parkLatitude, int addToTrip)
		{
			name = parkName;
			longitude = parkLongitude;
			latitude = parkLatitude;
			visit = addToTrip;
		}
		
	string getName () const
	{
		return name;
	}
	
	double getLatitude () const
	{
		return latitude;
	}
	
	double getLongitude () const
	{
		return longitude;
	}
	
	int getVisit () const
	{
		return visit;
	}
	
	void setName (string parkName)
	{
		name = parkName;
	}
	
	void setLatitude (double parkLatitude)
	{
		longitude = parkLatitude;
	}
	
	void setLongitude (double parkLongitude)
	{
		latitude = parkLongitude;
	}
	
	void setVisit (int parkVisit)
	{
		visit = parkVisit;
	}
	
	friend istream& operator>>(istream & fileIn, Park & nextPark);
	
	double distance (Park const & nextPark) const
	{
		const int CONVERSION = 111;
		const double RADIAN = M_PI / 180;
		double distX = 0, distY = 0;
		double other_distX = 0, other_distY = 0;
		
		distX = CONVERSION * (*this).longitude * cos((*this).latitude * RADIAN);
		distY = CONVERSION * (*this).latitude;
		
		other_distX = CONVERSION * nextPark.longitude
								 * cos(nextPark.latitude * RADIAN);
		other_distY = CONVERSION * nextPark.latitude;
		
		return sqrt(pow(distX - other_distX, 2) + pow(distY - other_distY, 2));
	}
};

istream & operator>>(istream & fileIn, Park & nextPark)
{
	return fileIn >> nextPark.name >> nextPark.latitude >> nextPark.longitude
				  >> nextPark.visit;
}

int main()
{
	const int MAX = 20;
	
	ifstream fileIn ("park.txt");

	Park parkArray [MAX];
	
	if (!fileIn)
		return EXIT_FAILURE;
		
	int parkCount = 0;
	
	for (int count = 0; count < MAX; count++)
	{
		fileIn >> parkArray [count];
		if (parkArray[count].getVisit() == 1)
			parkCount++;
	}

	Park currentPark = parkArray[0];
	
	for (int arrayCount = 0; arrayCount < parkCount; arrayCount++)
	{
		double shortestDistance = 1e99;
		int shortestCount = 0;
		
		for (int count = 0; count < MAX; count++)
		{
			if (parkArray[count].getVisit() == 1)
			{
				if (currentPark.distance(parkArray[count]) < shortestDistance)
				{
					shortestDistance = currentPark.distance(parkArray[count]);
					shortestCount = count;
				}			
			}
		}
		
		parkArray[shortestCount].setVisit(0);
		
		currentPark = parkArray[shortestCount];
		cout << currentPark.getName() << endl;
	}
	
	fileIn.close();
	system ("PAUSE");
	return EXIT_SUCCESS;
}

/*
Waterton_Lakes_AB
Yoho_BC
Banff_AB
Jasper_AB
Grasslands_SK
Riding_Mountain_MB
Nahanni_NT
Wapusk_MB
Forillon_QC
Cape_Breton_Highlands_NS
Prince_Edward_Island_PE
Fundy_NB
Gros_Morne_NL
Auyuittuq_NU
Press any key to continue . . .

*/
