/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Winter 2023
 * Author: Tran Huy
 * Date: 07.11.2023
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef awakened_h
#define awakened_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
struct Coordinate
{
    int x, y;
    char letter = '0';
    void print_coordinate()
    {
        //cout << "(" << x << "," << y << "): " << letter << '\n';
    }
};
struct Tile
{
    char letter;
    int time_stand = 0;
    //int i, j;
};
void print_array(Tile arr[10][10]);
struct State
{
    Coordinate current, next;
    Tile arr[10][10];
    void PrintState()
    {
        print_array(arr);
        // cout << "moveStyle: " << moveStyle << '\n'
        //      << "potion: " << potion << '\n'
        //      << "counter: " << counter << '\n';
        cout << "current: ";
        current.print_coordinate();
        cout << "next: ";
        next.print_coordinate();
    }
};
struct ShipRecord
{
    string departure_day, departure_month, departure_hour, departure_minute, return_day, return_month, return_hour, return_minute, ship_name, isValid;
    void Print()
    {
        // cout << ship_name << " " << departure_day << " " << departure_month << " " << departure_hour << " " << departure_minute << " " << return_day << " " << return_month << " " << return_hour << " " << return_minute;
    }
};

bool isNumber(string s)
{ // check if the string is right for the term 000 (number)
    for (int i = 0; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}
int readSchedule(const string &schedule, ifstream &myfile)
{
    string s;
    if (!myfile.is_open())
    {
        return -1;
    }
    myfile >> s >> s >> s >> s;
    if (isNumber(s) == false)
        return -1;
    return stoi(s);
}
int check_valid_date(string departure_day, string departure_month)
{
    int day_upper_bound, day_lower_bound;
    day_lower_bound = 1;

    if (departure_month == "01" || departure_month == "03" || departure_month == "05" || departure_month == "07" || departure_month == "08" || departure_month == "10" || departure_month == "12" || departure_month == "?0" || departure_month == "?1" || departure_month == "?2" || departure_month == "?3" || departure_month == "?5" || departure_month == "?7" || departure_month == "?8" || departure_month == "??" || departure_month == "0?" || departure_month == "1?")
    {
        day_upper_bound = 31;
    }
    else if (departure_month == "04" || departure_month == "06" || departure_month == "09" || departure_month == "11" || departure_month == "?2" || departure_month == "?4" || departure_month == "?6" || departure_month == "?9")
    {
        day_upper_bound = 30;
    }
    else if (departure_month == "02")
    {
        day_upper_bound = 29;
    }
    else
        return 0;

    // cout << "valid month\n";

    if (departure_day[0] == '?' && departure_day[1] != '?')
    {
        if (departure_day[1] - '0' < 10)
        {
            // cout << "valid date" << endl;
            return 1;
        }
    }
    if (departure_day[0] != '?' && departure_day[1] == '?')
    {
        if (departure_day[0] - '0' <= day_upper_bound / 10)
        {
            // cout << "valid date" << endl;
            return 1;
        }
    }
    if (departure_day[0] != '?' && departure_day[1] != '?')
    {
        return stoi(departure_day) >= day_lower_bound && stoi(departure_day) <= day_upper_bound;
    }
    if (departure_day[0] == '?' && departure_day[1] == '?')
    {
        // cout << "valid date" << endl;
        return 1;
    }

    // cout << "invalid date" << endl;
    return 0;
}

int check_valid_time(string return_hour, string minute)
{
    if (return_hour[0] != '?' && return_hour[1] != '?')
    {
        if (return_hour[0] - '0' >= 3 || return_hour[1] - '0' >= 10)
        {
            return 0;
        }
        if (return_hour[0] - '0' == 2)
        {
            if (return_hour[1] - '0' >= 4)
                return 0;
        }
    }
    if (return_hour[0] == '?' && return_hour[1] != '?')
    {
        if (return_hour[1] - '0' >= 10)
        {
            return 0;
        }
    }
    if (return_hour[0] != '?' && return_hour[1] == '?')
    {
        if (return_hour[0] - '0' >= 3)
        {
            return 0;
        }
    }
    // cout << "valid hour" << endl;
    if (minute[0] == '?' && minute[1] != '?')
    {
        if (minute[1] - '0' >= 10)
        {
            return 0;
        }
    }
    if (minute[0] != '?' && minute[1] == '?')
    {
        if (minute[0] - '0' > 5)
        {
            return 0;
        }
    }
    if (minute[0] != '?' && minute[1] != '?')
    {
        if (minute[0] - '0' >= 6 || minute[1] - '0' >= 10)
        {
            return 0;
        }
    }
    // cout << "valid time" << endl;
    return 1;
}

ShipRecord divide(string s)
{
    ShipRecord ship;
    string ship_name, departure_date, departure_time, return_date, return_time, dash;
    dash = ' ';
    stringstream read(s);
    read >> ship_name >> departure_date >> departure_time >> dash >> return_date >> return_time;
    // cout << ship_name << " " << departure_date << " " << departure_time << " " << dash << " " << return_date << " " << return_time << endl;
    string return_hour = return_time.substr(0, 2);
    string return_minute = return_time.substr(3, 2);
    string return_day = return_date.substr(0, 2);
    string return_month = return_date.substr(3, 2);
    string departure_hour = departure_time.substr(0, 2);
    string departure_minute = departure_time.substr(3, 2);
    string departure_day = departure_date.substr(0, 2);
    string departure_month = departure_date.substr(3, 2);
    ship.departure_day = departure_day;
    ship.departure_month = departure_month;
    ship.departure_hour = departure_hour;
    ship.departure_minute = departure_minute;
    ship.return_day = return_day;
    ship.return_month = return_month;
    ship.return_hour = return_hour;
    ship.return_minute = return_minute;
    ship.ship_name = ship_name;
    return ship;
}
int check_ship(ShipRecord s)
{

    if (check_valid_date(s.departure_day, s.departure_month) && check_valid_time(s.departure_hour, s.departure_minute) && check_valid_date(s.return_day, s.return_month) && check_valid_time(s.return_hour, s.return_minute))
    {
        // cout << "valid ship" << endl;
        return 1;
    }
    else
        return 0;
}

int invalidTime(const string &schedule)
{
    // Complete this function to gain point
    ShipRecord ship_obj;
    int n, departure_day, departure_minute, return_day, return_minute, count, departure_month, return_month;
    count = 0;
    string ship_name, s;
    string none = " ";
    ifstream myfile(schedule);
    n = readSchedule(schedule, myfile);
    if (n == -1)
    {
        return 0;
    }
    // cout << "n:" << n << endl;
    getline(myfile, s);
    for (int i = 0; i < n; i++)
    {
        getline(myfile, s);
        ship_obj = divide(s);
        count += check_ship(ship_obj);
    }
    if (count == 0)
    {
        return -1;
    }
    else
        return count;
    return true;
}

void check_min_departure(ShipRecord &ship_obj)
{
    if (ship_obj.departure_day[0] == '?' && ship_obj.departure_day[1] == '?')
    {
        ship_obj.departure_day[0] = '0';
        ship_obj.departure_day[1] = '1';
    }
    if (ship_obj.departure_day[0] == '?' && ship_obj.departure_day[1] - '0' >= 1)
    {
        ship_obj.departure_day[0] = '0';
    }
    if (ship_obj.departure_day[1] == '?' && ship_obj.departure_day[0] - '0' >= 1)
    {
        ship_obj.departure_day[1] = '0';
    }
    if (ship_obj.departure_day[0] == '?' && ship_obj.departure_day[1] - '0' == 0)
    {
        ship_obj.departure_day[0] = '1';
    }
    if (ship_obj.departure_day[1] == '?' && ship_obj.departure_day[0] - '0' == 0)
    {
        ship_obj.departure_day[1] = '1';
    }
    if (ship_obj.departure_month[0] == '?' && ship_obj.departure_month[1] == '?')
    {
        ship_obj.departure_month[0] = '0';
        ship_obj.departure_month[1] = '1';
    }
    if (ship_obj.departure_month[0] == '?' && ship_obj.departure_month[1] - '0' == 0)
    {
        ship_obj.departure_month[0] = '1';
    }
    if (ship_obj.departure_month[1] == '?' && ship_obj.departure_month[0] - '0' == 0)
    {
        ship_obj.departure_month[1] = '1';
    }
    if (ship_obj.departure_month[0] == '?' && ship_obj.departure_month[1] - '0' >= 1)
    {
        ship_obj.departure_month[0] = '0';
    }
    if (ship_obj.departure_month[1] == '?' && ship_obj.departure_month[0] - '0' >= 1)
    {
        ship_obj.departure_month[1] = '0';
    }
    if (ship_obj.departure_hour[1] == '?' && ship_obj.departure_hour[0] == '?')
    {
        ship_obj.departure_hour[0] = '0';
        ship_obj.departure_hour[1] = '0';
    }
    if (ship_obj.departure_hour[0] == '?' && ship_obj.departure_hour[1] - '0' == 0)
    {
        ship_obj.departure_hour[0] = '0';
    }
    if (ship_obj.departure_hour[1] == '?' && ship_obj.departure_hour[0] - '0' == 0)
    {
        ship_obj.departure_hour[1] = '0';
    }
    if (ship_obj.departure_hour[0] == '?' && ship_obj.departure_hour[1] - '0' >= 1)
    {
        ship_obj.departure_hour[0] = '0';
    }
    if (ship_obj.departure_hour[1] == '?' && ship_obj.departure_hour[0] - '0' >= 1)
    {
        ship_obj.departure_hour[1] = '0';
    }
    if (ship_obj.departure_minute[0] == '?' && ship_obj.departure_minute[1] == '?')
    {
        ship_obj.departure_minute[0] = '0';
        ship_obj.departure_minute[1] = '0';
    }
    if (ship_obj.departure_minute[0] == '?' && ship_obj.departure_minute[1] - '0' == 0)
    {
        ship_obj.departure_minute[0] = '0';
    }
    if (ship_obj.departure_minute[1] == '?' && ship_obj.departure_minute[0] - '0' == 0)
    {
        ship_obj.departure_minute[1] = '0';
    }
    if (ship_obj.departure_minute[0] == '?' && ship_obj.departure_minute[1] - '0' >= 1)
    {
        ship_obj.departure_minute[0] = '0';
    }
    if (ship_obj.departure_minute[1] == '?' && ship_obj.departure_minute[0] - '0' >= 1)
    {
        ship_obj.departure_minute[1] = '0';
    }
}
void check_max_return(ShipRecord &ship_obj)
{
    if (ship_obj.return_day == "31")
    {
        if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 1)
        {
            ship_obj.return_month[0] = '0';
        }
        if (ship_obj.return_month[0] - '0' == 0 && ship_obj.return_month[1] == '?')
        {
            ship_obj.return_month[1] = '8';
        }
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 0)
    {
        ship_obj.return_month[0] = '1';
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] == '?')
    {
        ship_obj.return_month[0] = '1';
        ship_obj.return_month[1] = '2';
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 1)
    {
        ship_obj.return_month[0] = '1';
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 2)
    {
        ship_obj.return_month[0] = '1';
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 3)
    {
        ship_obj.return_month[0] = '0';
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 4)
    {
        ship_obj.return_month[0] = '0';
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 5)
    {
        ship_obj.return_month[0] = '0';
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 6)
    {
        ship_obj.return_month[0] = '0';
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 7)
    {
        ship_obj.return_month[0] = '0';
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 8)
    {
        ship_obj.return_month[0] = '0';
    }
    if (ship_obj.return_month[0] == '?' && ship_obj.return_month[1] - '0' == 9)
    {
        ship_obj.return_month[0] = '0';
    }
    if (ship_obj.return_month[1] == '?' && ship_obj.return_month[0] - '0' == 0)
    {
        ship_obj.return_month[1] = '9';
    }
    if (ship_obj.return_month[1] == '?' && ship_obj.return_month[0] - '0' == 1)
    {
        ship_obj.return_month[1] = '2';
    }

    if (ship_obj.return_month == "02")
    {
        if (ship_obj.return_day[0] == '?' && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[0] = '2';
            ship_obj.return_day[1] = '9';
        }
        if (ship_obj.return_day[0] - '0' == 0 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '9';
        }
        if (ship_obj.return_day[0] - '0' == 1 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '9';
        }
        if (ship_obj.return_day[0] - '0' == 2 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '9';
        }
        if (ship_obj.return_day[0] == '?' && ship_obj.return_day[1] - '0' >= 0)
        {
            ship_obj.return_day[0] = '2';
        }
    }
    if (ship_obj.return_month == "01" || ship_obj.return_month == "03" || ship_obj.return_month == "05" || ship_obj.return_month == "07" || ship_obj.return_month == "08" || ship_obj.return_month == "10" || ship_obj.return_month == "12")
    {
        if (ship_obj.return_day[0] == '?' && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[0] = '3';
            ship_obj.return_day[1] = '1';
        }
        if (ship_obj.return_day[0] - '0' == 0 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '9';
        }
        if (ship_obj.return_day[0] - '0' == 1 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '9';
        }
        if (ship_obj.return_day[0] - '0' == 2 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '9';
        }
        if (ship_obj.return_day[0] - '0' == 3 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '1';
        }
        if (ship_obj.return_day[0] == '?' && ship_obj.return_day[1] - '0' == 0)
        {
            ship_obj.return_day[0] = '3';
        }
        if (ship_obj.return_day[0] == '?' && ship_obj.return_day[1] - '0' == 1)
        {
            ship_obj.return_day[0] = '3';
        }
        if (ship_obj.return_day[0] == '?' && ship_obj.return_day[1] - '0' > 1)
        {
            ship_obj.return_day[0] = '2';
        }
    }

    if (ship_obj.return_month == "04" || ship_obj.return_month == "06" || ship_obj.return_month == "09" || ship_obj.return_month == "11")
    {
        if (ship_obj.return_day[0] == '?' && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[0] = '3';
            ship_obj.return_day[1] = '0';
        }
        if (ship_obj.return_day[0] - '0' == 0 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '9';
        }
        if (ship_obj.return_day[0] - '0' == 1 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '9';
        }
        if (ship_obj.return_day[0] - '0' == 2 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '9';
        }
        if (ship_obj.return_day[0] - '0' == 3 && ship_obj.return_day[1] == '?')
        {
            ship_obj.return_day[1] = '0';
        }
        if (ship_obj.return_day[0] == '?' && ship_obj.return_day[1] - '0' == 0)
        {
            ship_obj.return_day[0] = '3';
        }
        if (ship_obj.return_day[0] == '?' && ship_obj.return_day[1] - '0' >= 1)
        {
            ship_obj.return_day[0] = '2';
        }
    }
    if (ship_obj.return_hour[0] == '?' && ship_obj.return_hour[1] == '?')
    {
        ship_obj.return_hour[0] = '2';
        ship_obj.return_hour[1] = '3';
    }
    if (ship_obj.return_hour[0] == '?' && ship_obj.return_hour[1] - '0' >= 0 && ship_obj.return_hour[1] - '0' <= 3)
    {
        ship_obj.return_hour[0] = '2';
    }
    if (ship_obj.return_hour[0] == '?' && ship_obj.return_hour[1] - '0' >= 4)
    {
        ship_obj.return_hour[0] = '1';
    }
    if (ship_obj.return_hour[0] - '0' == 0 && ship_obj.return_hour[1] == '?')
    {
        ship_obj.return_hour[1] = '9';
    }
    if (ship_obj.return_hour[0] - '0' == 1 && ship_obj.return_hour[1] == '?')
    {
        ship_obj.return_hour[1] = '9';
    }
    if (ship_obj.return_hour[0] - '0' == 2 && ship_obj.return_hour[1] == '?')
    {
        ship_obj.return_hour[1] = '3';
    }
    if (ship_obj.return_minute[0] == '?' && ship_obj.return_minute[1] == '?')
    {
        ship_obj.return_minute[0] = '5';
        ship_obj.return_minute[1] = '9';
    }
    if (ship_obj.return_minute[0] == '?' && ship_obj.return_minute[1] - '0' >= 0)
    {
        ship_obj.return_minute[0] = '5';
    }
    if (ship_obj.return_minute[0] - '0' >= 0 && ship_obj.return_minute[1] == '?')
    {
        ship_obj.return_minute[1] = '9';
    }
}

void HandleShiprecord(ShipRecord &ship_obj, int &max, string &return_ship_name)
{
    check_max_return(ship_obj);
    check_min_departure(ship_obj);
    int monthDays[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day1, day2, month1, month2, hour1, hour2, minute1, minute2;
    day1 = stoi(ship_obj.departure_day);
    month1 = stoi(ship_obj.departure_month);
    hour1 = stoi(ship_obj.departure_hour);
    minute1 = stoi(ship_obj.departure_minute);
    day2 = stoi(ship_obj.return_day);
    hour2 = stoi(ship_obj.return_hour);
    minute2 = stoi(ship_obj.return_minute);
    month2 = stoi(ship_obj.return_month);
    int n1 = (day1 - 1) * 24 * 60 + hour1 * 60 + minute1;
    int n2 = (day2 - 1) * 24 * 60 + hour2 * 60 + minute2;
    for (int i = 0; i < month1 - 1; i++)
    {
        n1 += monthDays[i] * 24 * 60;
    }

    for (int i = 0; i < month2 - 1; i++)
    {
        n2 += monthDays[i] * 24 * 60;
    }

    if ((n2 - n1) >= max)
    {
        max = (n2 - n1);
        return_ship_name = ship_obj.ship_name;
        ship_obj.Print();
        // cout << " " << (n2 - n1) << endl;
    }
}

string longestDuration(const string &schedule)
{
    ShipRecord ship_obj;
    int n, departure_day, departure_minute, return_day, return_minute, max;
    max = 0;
    string max_stay, s;
    ifstream myfile(schedule);
    n = readSchedule(schedule, myfile);
    if (n == -1)
    {
        return "";
    }
    // cout << "n:" << n << endl;
    getline(myfile, s);
    for (int i = 0; i < n; i++)
    {
        getline(myfile, s);
        ship_obj = divide(s);
        if (check_ship(ship_obj))
        {
            HandleShiprecord(ship_obj, max, max_stay);
        }
    }
    max_stay = max_stay.substr(0, max_stay.length() - 1);
    return max_stay;
}
void print_array(Tile arr[10][10])
{
    cout << "\n  | ";
    for (int j = 0; j < 10; j++)
    {
        cout << j << ' ';
    }
    cout << "\n--|---------------------\n";
    for (int i = 0; i < 10; i++)
    {
        cout << i << " | ";
        for (int j = 0; j < 10; j++)
        {
            cout << arr[i][j].letter << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
void map_adventure(const string &map, Tile arr[10][10])
{
    string s;
    ifstream myfile(map);
    for (int i = 0; i < 10; i++)
    {
        getline(myfile, s);
        for (int j = 0; j < 10; j++)
        {
            arr[i][j].letter = s[j * 2];
        }
    }
}
void update_array(Tile arr[10][10], Coordinate &current, Coordinate &next, string &outPath)
{
    string str2 = ";";
    arr[next.x][next.y].letter = 'S';
    arr[current.x][current.y].letter = current.letter;

    current = next;
    outPath += to_string(current.x) + "," + to_string(current.y) + ";";
}
void stamina_check(int &counter, int &stamina, bool potion)
{
    counter--;
    if (counter == 0)
    {
        if (potion == true)
        {
            counter = 2;
            stamina -= 1;
        }
        else
        {
            counter = 1;
            stamina -= 1;
        }
    }
}
int letter_case(string &movestyle, int &stamina, State &checkpoint, State &present, string &outPath, bool &potion, int &counter)
{
    if (present.arr[present.next.x][present.next.y].letter == 'A') // gap ban tho
    {
        update_array(present.arr, present.current, present.next, outPath);
        stamina_check(counter, stamina, potion);
        present.arr[present.current.x][present.current.y].time_stand += 1;
        // cout << "A is ban tho";
        return 1;
    }
    if (present.arr[present.next.x][present.next.y].letter == 'M') // gap quai vat
    {
        update_array(present.arr, present.current, present.next, outPath);
        stamina_check(counter, stamina, potion);
        present.arr[present.current.x][present.current.y].time_stand += 1;
        // cout << "M la quai vat";
        return -1;
    }
    if (present.arr[present.next.x][present.next.y].letter == 'T')
    {
        update_array(present.arr, present.current, present.next, outPath);
        stamina_check(counter, stamina, potion);
        for (int y = 0; y < 10; y++)
        {
            for (int u = 0; u < 10; u++)
            {
                if (present.arr[y][u].letter == 'T' && (y != present.next.x || u != present.next.y))
                {
                    present.next.x = y;
                    present.next.y = u;
                    present.next.letter = present.arr[y][u].letter;
                    present.arr[present.next.x][present.next.y].letter = 'S';
                    present.arr[present.current.x][present.current.y].letter = present.current.letter;
                    present.current = present.next;
                    present.arr[present.current.x][present.current.y].time_stand += 1;
                    return 0;
                }
            }
        }
    }
    if (present.arr[present.next.x][present.next.y].letter == '0')
    {
        update_array(present.arr, present.current, present.next, outPath);
        stamina_check(counter, stamina, potion);
        present.arr[present.current.x][present.current.y].time_stand += 1;
    }
    if (present.arr[present.next.x][present.next.y].letter == 'X')
    {
        stamina_check(counter, stamina, potion);
        present.arr[present.next.x][present.next.y].time_stand+=1;
        if (present.arr[present.next.x][present.next.y].time_stand>3){
            return -1;
        }
    }
    if (present.arr[present.next.x][present.next.y].letter == 'R')
    {
        update_array(present.arr, present.current, present.next, outPath);
        stamina_check(counter, stamina, potion);
        for (int q = 0; q < movestyle.length() / 2; q++)
        {
            swap(movestyle[q], movestyle[movestyle.length() - 1 - q]);
        }
        present.arr[present.current.x][present.current.y].time_stand += 1;
    }
    if (present.arr[present.next.x][present.next.y].letter == 'C')
    {
        update_array(present.arr, present.current, present.next, outPath);
        stamina_check(counter, stamina, potion);
        for (int h = 0; h < 10; h++)
        {
            for (int g = 0; g < 5; g++)
            {
                swap(present.arr[h][g], present.arr[9 - h][9 - g]);
            }
        }
        // present.current.x = 9 - present.current.x;
        // present.current.y = 9 - present.current.y;
        present.arr[9-present.current.x][9-present.current.y].letter=present.current.letter;
        present.current.letter=present.arr[present.current.x][present.current.y].letter;
        //present.arr[present.current.x][present.current.y].time_stand += 1;
        present.arr[present.current.x][present.current.y].letter='S';

    }
    if (present.arr[present.next.x][present.next.y].letter == 'L')
    {
        update_array(present.arr, present.current, present.next, outPath);
        stamina_check(counter, stamina, potion);
        present.arr[present.current.x][present.current.y].time_stand += 1;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (present.arr[i][j].letter == 'X')
                {
                    if (present.arr[min(i+1, 9)][j].letter == 'A')
                    {
                        return 1;
                    }
                    if (present.arr[max(i-1, 0)][j].letter == 'A')
                    {
                        return 1;
                    }
                    if (present.arr[i][min(j+1, 9)].letter == 'A')
                    {
                        return 1;
                    }
                    if (present.arr[i][max(j-1, 0)].letter == 'A')
                    {
                        return 1;
                    }
                    if (present.arr[max(i-1, 0)][max(j-1, 0)].letter == 'A')
                    {
                        return 1;
                    }
                    if (present.arr[min(i+1, 9)][max(j-1, 0)].letter == 'A')
                    {
                        return 1;
                    }
                    if (present.arr[max(i-1, 0)][min(j+1, 9)].letter == 'A')
                    {
                        return 1;
                    }
                    if (present.arr[min(i+1, 9)][min(j+1, 9)].letter == 'A')
                    {
                        return 1;
                    }
                }
            }
        }
    }
    if (present.arr[present.next.x][present.next.y].letter == 'P')
    {
        potion = true;
        update_array(present.arr, present.current, present.next, outPath);
        stamina_check(counter, stamina, potion);
        present.arr[present.current.x][present.current.y].time_stand += 1;
    }
    if (present.arr[present.next.x][present.next.y].letter == 'H')
    {
        stamina_check(counter, stamina, potion);
        // update_array(present.arr, present.current, present.next, outPath);
        present = checkpoint;
        outPath += to_string(present.current.x) + "," + to_string(present.current.y) + ";";
    }
    return 0;
}

bool investigateTemple(const string &map, const string &moveStyle, int stamina, int &outTime, string &outPath)
{
    // Complete this function to gain point
    bool saved = false;
    int counter = 1;
    bool potion = false;
    Tile check_time;
    outTime = 0;
    int res;
    State present, checkpoint;
    string strCopy = moveStyle;
    bool end = false;
    int k = 0;
    map_adventure(map, present.arr);
    // print_array(present.arr);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (present.arr[i][j].letter == 'S')
            {
                present.current.x = i;
                present.current.y = j;
            }
        }
    }
    checkpoint = present;
    const int check_stamina = stamina;
    while (!end)
    {
        if (strCopy[k % strCopy.length()] == 'R')
        {
            if (present.current.y == 9)
            {
                present.next.x = present.current.x;
                present.next.y = 0;
            }
            else
            {
                present.next.x = present.current.x;
                present.next.y = present.current.y + 1;
            }
        }
        if (strCopy[k % strCopy.length()] == 'L')
        {
            if (present.current.y == 0)
            {
                present.next.x = present.current.x;
                present.next.y = 9;
            }
            else
            {
                present.next.x = present.current.x;
                present.next.y = present.current.y - 1;
            }
        }
        if (strCopy[k % strCopy.length()] == 'U')
        {
            if (present.current.x == 0)
            {
                present.next.x = 9;
                present.next.y = present.current.y;
            }
            else
            {
                present.next.x = present.current.x - 1;
                present.next.y = present.current.y;
            }
        }
        if (strCopy[k % strCopy.length()] == 'D')
        {
            if (present.current.x == 9)
            {
                present.next.x = 0;
                present.next.y = present.current.y;
            }
            else
            {
                present.next.x = present.current.x + 1;
                present.next.y = present.current.y;
            }
        }
        present.next.letter = present.arr[present.next.x][present.next.y].letter;
        res = letter_case(strCopy, stamina, checkpoint, present, outPath, potion, counter);
        outTime++;

        /*if (res == 1)
        {
            //cout << "stamina" << stamina << endl;
            outPath = outPath.substr(0, outPath.length() - 1);
            return true;
        }
        if (res == -1)
        {
            //cout << "stamina la" << stamina << endl;
            outPath = outPath.substr(0, outPath.length() - 1);
            return false;
        }
        if (stamina <= 0)
        {
            outPath = outPath.substr(0, outPath.length() - 1);
            return false;
        }
        if (check_stamina - stamina == check_stamina / 3)
        {
            checkpoint = present;
        }
        present.arr[present.current.x][present.current.y].time_stand+=1;
        if (present.arr[present.current.x][present.current.y].time_stand>3){
            outPath = outPath.substr(0, outPath.length() - 1);
            return false;
        }*/
         //cout<<endl;
         //print_array(present.arr);
        k++;
        /*cout << "\n--------------------------------------------------------\n";
        cout << "Time: " << k << '\n'
             << "Current move: " << strCopy[(k - 1) % strCopy.length()] << '\n';
        cout << "moveStyle: " << strCopy << '\n'
             << "potion: " << potion << '\n'
             << "counter: " << counter << '\n';
        present.PrintState();
        cout << "outPath: " << outPath << '\n'
             << "stamina: " << stamina << '\n'
             << "Consumed stamina: " << (check_stamina - stamina) << '\n'
             << "1/3 of originalStamina: " << (check_stamina / 3) << '\n';*/
        if (res == 1)
        {
            // cout << "stamina" << stamina << endl;
            outPath = outPath.substr(0, outPath.length() - 1);
            return true;
        }
        if (res == -1)
        {
            // cout << "stamina la" << stamina << endl;
            outPath = outPath.substr(0, outPath.length() - 1);
            return false;
        }
        if (stamina <= 0)
        {
            //outTime=0;
            outPath = outPath.substr(0, outPath.length() - 1);
            return false;
        }
        if (((check_stamina - stamina) >=1+ ((check_stamina-1) / 3)) && !saved)
        {
            saved = true;
            checkpoint = present;
        }
        // present.arr[present.current.x][present.current.y].time_stand += 1;
        if (present.arr[present.current.x][present.current.y].time_stand > 3)
        {
            outPath = outPath.substr(0, outPath.length() - 1);
            return false;
        }
    }
}

int solveCrate(int *arr, int size, int k)
{
    // Complete this function to gain point
    long long sum = 0;
    if (size < 1 || k > size || size > 50 || k <= 0)
    {
        return -1;
    }

    for (int i = 1; i < k; i++)
    {
        size--;
        for (int j = 0; j <= size - 1; j++)
        {
            arr[j] = arr[j] + arr[j + 1];
        }
    }
    for (int i = 0; i < size; i++)
    {
        sum += *arr;
        arr++;
    }
    return sum % 1000;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* awakened_h */