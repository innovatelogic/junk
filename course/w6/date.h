class Date
{
public:
    Date();
    Date(int year, int month, int day);
    
    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }

    int year = 0;
    int month = 0;
    int day = 0;
};