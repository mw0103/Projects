#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <string>

#define header_size_1 2
#define header_size_2 1
#define dont_print_line 0
#define print_line 1
#define use_day 1
#define dont_use_day 0

using namespace std;

int row_count = 0;
float temp_max;
float temp_min;
float precip_total_day;
float precip_total_range;

int parse_line(string x) {
    if(x.compare(96,4,"-999") == 0){
        return dont_print_line;
    }
    if(x.compare(123,4,"-999") == 0){
        return dont_print_line;
    }
    if(x.compare(132,4,"-999") == 0){
        return dont_print_line;
    }
    return print_line;
}

int check_day(string row, string day){
    if(row.compare(59,2,day) == 0){
        return use_day;
    }
    return dont_use_day;
}

    float new_temp_max(string row){
    string temp = "";
    for(int i = 123; i < 125; i++) {
        temp += row[i];
    }
    temp_max = ((stof(temp)/10) * 9/5) + 32;
    return temp_max;
}

float new_temp_min(string row) {
    string temp = "";
    for(int i = 132; i < 134; i++) {
        temp += row[i];
    }
    temp_min = ((stof(temp)/10) * 9/5) + 32;
    return temp_min;
}

float highest_temp(string row) {
    float high_temp;
    string temp = "";
    for(int i = 67; i < 75; i ++) {
        temp += row[i];
    }
    high_temp = stof(temp);
    return high_temp;
}

float lowest_temp(string row) {
    float low_temp;
    string temp = "";
    for(int i = 77; i < 85; i ++) {
        temp += row[i];
    }
    low_temp = stof(temp);
    return low_temp;
}

string new_row1(string x){
    string row = "";
    for(int i = 18; i < 77; i++){
        row += x[i];
    }
    for(int i = 95; i < 104; i++){
        row += x[i];
    }
    for(int i = 122; i < 141; i++){
        row += x[i];
    }
    return row;
}

string new_row2(string x, float y, float z) {
    string row = "";
    for(int i = 18; i < 77; i++){
        row += x[i];
        if((i == 72) || (i == 74)){
            row += " ";
        }
    }
    for(int i = 95; i < 101; i++){
        row += x[i];
    }
    setprecision(2);
    row.append(to_string(y));
    row.append(" ");
    row.append(to_string(z));
    return row;
}

float precip_total_for_day(string data){
    string precip_temp_string;
    float precip_temp_float;
    for(int i = 62; i < 67; i++){
        precip_temp_string+= data[i];
    }
    precip_temp_float = stof(precip_temp_string);
    return precip_temp_float;
}
float precip_range(string row, int start_date, int end_date){
    int day;
    string temp_day;
    float precip;
    string temp_precip;
    for(int i = 59; i < 63; i ++){
        temp_day += row[i];
    }
    day = stoi(temp_day);
    for(int i = 62; i < 67; i++){
        temp_precip += row[i];
    }
    if((day >= start_date) && (day <= end_date)){
        precip = stof(temp_precip);
    }
    return precip;
}

void over_range(string name, int start, int end){
    ifstream st_in;
    st_in.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station_reduced.txt");
    string buff;
    //cout << "Enter a station to retrieve the max temp, min temp, average high and average low temperatures of the entire month of the station" << endl;
// getline(cin, station_name);
    int npos1, npos2;
    double k = 0;
    int count = 0;
    double temp1, temp2;
    double temp_min = 55.32, temp_max = 0.0;
    string max_temp, min_temp, avghigh, avglow;
    double sum_high = 0, sum_low = 0;
    getline(st_in, buff);//Getting the first two lines
    getline(st_in, buff);
    getline(st_in, buff);
    npos1 = buff.find("46.759998");
    npos2 = buff.find("41.540001");
    int position = buff.find("01 ");
    st_in.seekg(0, ios::beg);

    while (!st_in.eof()) {
        getline(st_in, buff);
        if ((buff.find(name) != string::npos) && (stoi(buff.substr(position, 2)) <= end) && (stoi(buff.substr(position, 2)) >= start)) {
            temp1 = stod(buff.substr(npos1, 9));
            temp2 = stod(buff.substr(npos2, 9));
            if(temp_max < stod(buff.substr(npos1, 9))) {
                temp_max = stod(buff.substr(npos1, 9));
            }
            if(temp_min > stod(buff.substr(npos2, 9))) {
                temp_min = stod(buff.substr(npos2, 9));
            }
            sum_high += temp1;
            sum_low += temp2;
            k++;
        }
    }
    cout << "The average high temp is " << sum_high/(k) << " F" << endl;
    cout << "The average low temp is " << sum_low/(k) << " F" << endl;
    cout << "The maximum temperature is " << temp_max << " F" << endl;
    cout << "The minimum temperature is " << temp_min << " F"  << endl;
    st_in.close();

}
void precip_by_name(string name){
    ifstream st_in;
    st_in.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station_reduced.txt");
    st_in.seekg(0, ios::beg);
    string buff;
    //cout << "Enter a station to retrieve the total precipitation for the entire month of the station" << endl;
    //cin >> name;
    int npos;
    string prcp;
    float prcp_value;
    float sum = 0;
    getline(st_in, buff);//Getting the first two lines
    getline(st_in, buff);
    getline(st_in, buff);
    npos = buff.find("0.15");
    st_in.seekg(0, ios::beg);
    while (!st_in.eof()) {
        getline(st_in, buff);
        if (buff.find(name) != string::npos) {
            prcp = buff.substr(npos, 4);
            prcp_value = stof(prcp);
            sum = sum + prcp_value;
        }
    }
    cout << "The total precipitation is " << sum << " inches" << endl;
    st_in.close();
}
void max_min_avg(string name){
    ifstream st_in;
    st_in.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station_reduced.txt");
    string buff;
    int npos1, npos2;
    double k = 0;
    int count = 0;
    double temp1, temp2;
    double temp_min = 55.32, temp_max = 0.0;
    string max_temp, min_temp, avghigh, avglow;
    double sum_high = 0, sum_low = 0;
    getline(st_in, buff);//Getting the first two lines
    getline(st_in, buff);
    getline(st_in, buff);
    npos1 = buff.find("46.759998");
    npos2 = buff.find("41.540001");
    st_in.seekg(0, ios::beg);

    while (!st_in.eof()) {
        getline(st_in, buff);
        if (buff.find(name) != string::npos) {
            temp1 = stod(buff.substr(npos1, 9));
            temp2 = stod(buff.substr(npos2, 9));
            if(temp_max < stod(buff.substr(npos1, 9))) {
                temp_max = stod(buff.substr(npos1, 9));
            }
            if(temp_min > stod(buff.substr(npos2, 9))) {
                temp_min = stod(buff.substr(npos2, 9));
            }
            sum_high += temp1;
            sum_low += temp2;
            k++;
        }
    }
    cout << "The average high temp is " << sum_high/(k) << " F" << endl;
    cout << "The average low temp is " << sum_low/(k) << " F" << endl;
    cout << "The maximum temperature is " << temp_max << " F" << endl;
    cout << "The minimum temperature is " << temp_min << " F"  << endl;
    st_in.close();

}

int main() {
    ifstream file1;
    ofstream file2_parsed;
    ifstream file3;
    ofstream file4;
    string x;
    string y;
    string z;
    string day;
    float high_temp;
    float low_temp;
    float number1;
    float number2 = 9999;
    int start_day;
    int end_day;
    int user_input;
    string name;
    char buff;

    file2_parsed.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station_parsed.txt");
    file1.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station.txt");
    while(getline(file1,x)) {
        row_count++;
        if(parse_line(x) == print_line){
            file2_parsed << x << '\n';
            //cout << x << '\n';
        }
    }
    file1.close();
    file2_parsed.close();

    row_count = 0;
    file3.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station_parsed.txt");
    file4.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station_reduced.txt");
    while(getline(file3,x)) {
        row_count++;
        if(row_count > header_size_1){
            y = new_row2(x,new_temp_max(x),new_temp_min(x));
            file4 << y << '\n';
        }
        else{
            y = new_row1(x);
            file4 << y << '\n';
        }
    }
    file3.close();
    file4.close();

    row_count = 0;
    file1.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station_reduced.txt");




    while(getline(file1,x)) {
        row_count++;
        if (row_count > header_size_1) {
            high_temp = highest_temp(x);
            low_temp = lowest_temp(x);
            if (high_temp > number1) {
                number1 = high_temp;
                y = x;
            }
            if (low_temp < number2) {
                number2 = low_temp;
                z = x;
            }
        }
    }
    cout << "Highest temperature city: " << y << '\n';
    cout << "Lowest temperature city: " << z << '\n';
    row_count = 0;
    file1.close();
    file1.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station_reduced.txt");

    while(true){
        cout << "Pick a number 1 through 6. \n" << "Pick 1 to Find the total precipitation among all stations on a single day.\n";
        cout << "Pick 2 to find the total precipitation among all stations over a range of days.\n";
        cout << "Pick 3 to the total precipitation for a single station.\n";
        cout << "Pick 4 to find the max temp the min temp and the average temp for a staion.\n";
        cout << "Pick 5 to find the max temp the min temp and the average low temp over a range of dates for a station.\n";
        cout << "Pick 6 to exit.\n";
        cin >> user_input;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');


        if(user_input == 1){
            cout << "Pick a day between 01 and 31 (be sure if your day is bellow 10 to include 0 in front of your number e.g. 01): ";
            getline(cin, day);
            while(day.size() != 2) {
                cout << "Whoops it looks like you made a mistake while inputting the day! \nMake sure you use two numbers when inputting your day: ";
                getline(cin, day);
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
            while(getline(file1,x)){
                row_count ++;
                if(row_count > header_size_1) {
                    if(check_day(x,day) == use_day){
                        precip_total_day += precip_total_for_day(x);
                    }
                }
            }
            cout << "Total precipitation for March " << day << " was: " << precip_total_day << "\n";
            file1.close();
            file1.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station_reduced.txt");
            row_count = 0;
        }
        else if(user_input == 2){
            cout << "Pick a starting day to check for precipitation: ";
            cin >> start_day;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Pick an end day to check for precipitation: ";
            cin >> end_day;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            while(getline(file1,x)){
                row_count ++;
                if(row_count > header_size_1) {
                    precip_total_range += precip_range(x,start_day,end_day);
                }
            }
            cout << "The preciptation over the range was: " << precip_total_range << "\n";
            file1.close();
            file1.open("/Users/treymclemore/CLionProjects/untitled4/AL_Weather_Station_reduced.txt");
            row_count = 0;
            precip_total_range = 0;
        }
        else if(user_input == 3){
            cout << "Enter a station to retrieve the max temp, min temp, average high and average low temperatures of the entire month of the station" << endl;
            getline(cin,name);
            precip_by_name(name);
        }
        else if(user_input == 4){
            cout << "Enter a station to retrieve the max temp, min temp, average high and average low temperatures of the entire month of the station" << endl;
            getline(cin,name);
            max_min_avg(name);
        }
        else if(user_input == 5){
            cout << "Enter the station name you would like to check: ";
            getline(cin,name);
            cout << "Pick a starting day: ";
            cin >> start_day;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Pick an end day: ";
            cin >> end_day;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            over_range(name,start_day,end_day);
        }
        else if(user_input == 6){
            break;
        }
    }
    return 0;
}
