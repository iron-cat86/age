#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <vector>

struct BirthDate
{
    char name[10]="Today";
    int day=0;
    int month=0;
    int year=0;
    int hour=0;
    int minute=0;
    bool vys=false;
    bool prev_vys=false;
};

using namespace std;

int this_max_day[]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int prev_max_day[]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int birth_max_day[]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int ageDetect(BirthDate dateToday)
{
    BirthDate birth;
    std::fstream dataArrayFile;
    dataArrayFile.open("data.txt", ios_base::in);
    vector<BirthDate> data;

    if(dataArrayFile.is_open())
    {
        cout<<"File is open\n";
        int countStr=0;
        int countP=0;
        BirthDate curDate;
        char strFromFile[10];
        
        while(!dataArrayFile.eof())
        {
            dataArrayFile >> strFromFile;

            if(countStr==0)
            {
                for(int j=0; j<10; ++j)
                    curDate.name[j]=strFromFile[j];
            }
            else if(countStr==1)
                curDate.day=atoi(strFromFile);
            else if(countStr==2)
                curDate.month=atoi(strFromFile);
            else if(countStr==3)
                curDate.year=atoi(strFromFile);
            else if(countStr==4)
                curDate.hour=atoi(strFromFile);
            else if(countStr==5)
                curDate.minute=atoi(strFromFile);
            else if(countStr==6)
                curDate.vys=(bool)atoi(strFromFile);
            else if(countStr==7)
                curDate.prev_vys=(bool)atoi(strFromFile);
            ++countStr;
            ++countP;
            if(countStr>7)
            {
                data.push_back(curDate);
                countStr=0;
            }
        }

        if(data.empty())
            cout<<"File is empty\n";
        else
        {
            cout<<data.size()<<" data are reed\n";

            for(unsigned int j=0; j<data.size(); ++j)
                cout<<"name["<<j<<"]="<<data[j].name<<"\n";
        }
    }
    char name[10];
    cout<<"Enter the name: \n";
    cin >> name;
    unsigned int i=0;

    while(i<data.size()&&
          !(name[0]==data[i].name[0]&&name[1]==data[i].name[1]&&name[2]==data[i].name[2]&&name[3]==data[i].name[3]
            &&name[4]==data[i].name[4]&&name[5]==data[i].name[5]&&name[6]==data[i].name[6]&&name[7]==data[i].name[7]
            &&name[8]==data[i].name[8]&&name[9]==data[i].name[9]))
        ++i;
    char ans='n';

    if(i<data.size())
    {
        cout<<"Is it right data?\n \n";
        cout<<data[i].name<<"\n ================ \n";
        cout<<"day: "<<data[i].day<<"\n";
        cout<<"month: "<<data[i].month<<"\n";
        cout<<"year: "<<data[i].year<<"\n";
        cout<<"hour: "<<data[i].hour<<"\n";
        cout<<"minute: "<<data[i].minute<<"\n";
        cout<<"vys: "<<data[i].vys<<"\n";
        cout<<"prev_vys: "<<data[i].prev_vys<<"\n ==================== \n";
        cin    >> ans;
    }

    if(ans=='y'&&i<data.size())
    {
        for(int j=0; j<10; ++j)
            birth.name[j]=data[i].name[j];
        birth.day=data[i].day;
        birth.month=data[i].month;
        birth.year=data[i].year;
        birth.hour=data[i].hour;
        birth.minute=data[i].minute;
        birth.vys=data[i].vys;
        birth.prev_vys=data[i].prev_vys;
    }
    else
    {
        auto kur=dataArrayFile.tellg();
        dataArrayFile.close();
        dataArrayFile.open("data.txt", std::ios::app);
        //dataArrayFile.seekp(dataArrayFile.end, ios::beg);
        for(int j=0; j<10; ++j)
            birth.name[j]=name[j];
        dataArrayFile<<birth.name<<"\n";
        cout << "Enter yore birth day: \n" << endl;
        cin  >> birth.day;
        dataArrayFile<<birth.day<<"\n";
        cout << "Enter yore birth month: \n" << endl;
        cin  >> birth.month;
        dataArrayFile<<birth.month<<"\n";
        cout << "Enter yore birth year: \n" << endl;
        cin  >> birth.year;
        dataArrayFile<<birth.year<<"\n";
        cout << "Enter yore birth hour: \n" << endl;
        cin  >> birth.hour;
        dataArrayFile<<birth.hour<<"\n";
        cout << "Enter yore birth minute: \n" << endl;
        cin  >> birth.minute;
        dataArrayFile<<birth.minute<<"\n";
        birth.vys=!(
                    (
                        birth.year>=2016+4&&
                        (birth.year-2016)%4>0
                    )||
                    (2024-birth.year)%4>0
                );
        dataArrayFile<<birth.vys<<"\n";
        birth.prev_vys=false;
        dataArrayFile<<birth.prev_vys<<"\n";

        if(!birth.vys)
            birth_max_day[1]=28;

        if(birth.month<1||birth.month>12)
        {
            cout<<"Wrong birth month!\n";
            return 1;
        }

        if(
                birth.day<1||
                birth.day>31||
                birth.day>birth_max_day[birth.month-1]
            )
        {
            cout<<"Wrong birth day!\n";
            return 2;
        }

        if(birth.year<0||birth.year>dateToday.year)
        {
            cout<<"Don't trynd, pleas!\n";
            return 3;
        }

        if(birth.hour<0||birth.hour>=24)
        {
            cout<<"Wrong birth hour!\n";
            return 4;
        }

        if(birth.minute<0||birth.minute>=60)
        {
            cout<<"Wrong birth minute!\n";
            return 5;
        }
        dataArrayFile.close();
    }

    int amount_years=dateToday.year-birth.year-1;
    bool pass_birthd=(dateToday.month>=birth.month&&dateToday.day>=birth.day&&dateToday.hour>=birth.hour&&dateToday.minute>=birth.minute);

    if(pass_birthd)
        ++amount_years;
    int amount_months=12*amount_years;
    int dop_months=0;

    if(pass_birthd)
        dop_months=dateToday.month-birth.month;
    else
    {
        dop_months=12-birth.month+dateToday.month-1;

        if(dateToday.day>birth.day)
            ++dop_months;
        else if(dateToday.day==birth.day)
        {
            if(dateToday.hour>birth.hour)
                ++dop_months;
            else if(dateToday.hour==birth.hour)
            {
                if(dateToday.minute>=birth.minute)
                    ++dop_months;
            }
        }
    }
    amount_months+=dop_months;

    int amount_day=365*amount_years;
    int vis_years=amount_years/4;
    amount_day+=vis_years;
    int dop_day_for_y=0;
    int dop_day=0;

    if(pass_birthd)
    {
        dop_day_for_y=this_max_day[birth.month-1]-birth.day;

        if(dateToday.month>birth.month)
        {
            int c_month=birth.month;

            while(c_month<dateToday.month-1)
            {
                dop_day_for_y+=this_max_day[c_month];
                ++c_month;
            }
            dop_day_for_y+=birth.day;
        }
        dop_day=dateToday.day-birth.day;
    }
    else
    {
        int c_month=birth.month-1;

        while(c_month<11)
        {
            dop_day_for_y+=prev_max_day[c_month];
            ++c_month;
        }
        dop_day_for_y+=prev_max_day[11]-birth.day;

        c_month=0;

        while(c_month<dateToday.month-1)
        {
            dop_day_for_y+=this_max_day[c_month];
            ++c_month;
        }
        dop_day_for_y+=dateToday.day-1;

        if(dateToday.day>=birth.day)
            dop_day=dateToday.day-birth.day-1;
        else
            dop_day=(dateToday.month>1?this_max_day[dateToday.month-2]:prev_max_day[11])-birth.day+dateToday.day-1;

        if(dateToday.hour>birth.hour||(dateToday.hour==birth.hour&&dateToday.minute>=birth.minute))
        {
            ++dop_day_for_y;
            ++dop_day;
        }
    }
    amount_day+=dop_day_for_y;

    int amount_week=amount_day/7;
    int dop_week_days=amount_day%7-1;

    if(dateToday.hour>birth.hour||(dateToday.hour==birth.hour&&dateToday.minute>=birth.minute))
        ++dop_week_days;

    if(dop_week_days<0)
        dop_week_days=0;

    int amount_hour=amount_day*24;
    int dop_hour=0;

    if(dateToday.hour>=birth.hour)
        dop_hour=dateToday.hour-birth.hour-1;
    else
        dop_hour=24-birth.hour+dateToday.hour-1;

    if(dateToday.minute>=birth.minute)
        ++dop_hour;
    if(dop_hour<0)
        dop_hour=23;
    amount_hour+=dop_hour;

    int amount_minute=amount_hour*60;
    int dop_minute=0;

    if(dateToday.minute>=birth.minute)
        dop_minute=dateToday.minute-birth.minute;
    else
        dop_minute=60-birth.minute+dateToday.minute;
    amount_minute+=dop_minute;
    double accur_years=amount_years+(((double)dop_day_for_y)/(dateToday.vys?366.:365.))
            +(((double)dop_hour)/(24.*(dateToday.vys?366.:365.)))
            +(((double)dop_minute)/(60.*24*(dateToday.vys?366.:365.)));
    double accur_months=amount_months+(((double)dop_day)/((double)this_max_day[dateToday.month-1]))
            +(((double)dop_hour)/(24.*((double)this_max_day[dateToday.month-1])))
            +(((double)dop_minute)/(60.*24*((double)this_max_day[dateToday.month-1])));
    double accur_weeks=amount_week+((double)dop_week_days)/7.
            +(((double)dop_hour)/(24.*7.))
            +(((double)dop_minute)/(60.*24.*7.));
    double accur_days=amount_day+(((double)dop_hour)/24.)
            +(((double)dop_minute)/(60.*24.));
    double accur_hours=amount_hour+(((double)dop_minute)/60.);
    cout<<"Your birth year was "<<(birth.vys?"vys":"standart")<<", prev year was "<<(dateToday.prev_vys?"vys":"standart")
        <<", now "<<(dateToday.vys?"vys":"standart")<<" year.\n";
    cout<<"Your full age: "<<accur_years<<" years, or "<<amount_years<<" years and "<<dop_day_for_y<<" days, "
        <<dop_hour<<" hours, "<<dop_minute<<"minutes.\n";
    cout<<"Or "<<amount_years<<" years, "<<dop_months<<" months, "<<dop_day<<" days, "<<dop_hour<<" hours, "
        <<dop_minute<<" minutes.\n";
    cout<<"Or "<<accur_months<<" months, or "<<amount_months<<" months and "<<dop_day<<" days, "<<dop_hour<<" hours, "
        <<dop_minute<<" minutes.\n";
    cout<<"Or "<<accur_days<<" days, or "<<amount_day<<" days, "<<dop_hour<<" hours, "<<dop_minute<<" minutes.\n";
    cout<<"Or "<<accur_weeks<<" weeks, or "<<amount_week<<" weeks and "<<dop_week_days<<" days, "<<dop_hour<<" hours, "
       <<dop_minute<<" minutes.\n";
    cout<<"Or "<<accur_hours<<" hours, or "<<amount_hour<<" hours and "<<dop_minute<<" minutes.\n";
    cout<<"Or "<<amount_minute<<" minutes.\n";
    return 0;
}

int main(int argc, char *argv[])
{
    const time_t t_m = time(nullptr);
    tm *gmtm = gmtime(&t_m);
    char c_time[64];
    strftime(c_time, sizeof(c_time), "%d.%m.%Y", localtime(&t_m));
    cout << c_time << endl;
    char char_month[3]={c_time[3], c_time[4], NULL};
    char char_date[3]={c_time[0], c_time[1], NULL};
    char char_year[5]={c_time[6],c_time[7], c_time[8], c_time[9], NULL};
    BirthDate today;
    today.day=atoi(char_date);
    today.month=atoi(char_month);
    today.year=atoi(char_year);
    today.hour=gmtm->tm_hour;
    today.minute=gmtm->tm_min;
    today.vys=false;
    today.prev_vys=false;
    cout<<"month="<<today.month<<", date="<<today.day<<", Year="<<today.year<<", hour="<<today.hour<<", minute="<<today.minute<<"\n";
    today.vys=!(
                (today.year-2016)%4>0
            );
    today.prev_vys=!(
                (today.year-1-2016)%4>0
            );

    if(!today.vys)
        this_max_day[1]=28;

    if(!today.prev_vys)
        prev_max_day[1]=28;
    char ans='y';

    while(ans=='y')
    {
        int tyred=ageDetect(today);
        cout<<"Cycle is over with "<<tyred<<". Repeat?\n";
        cin >> ans;
    }
    return 0;
}
