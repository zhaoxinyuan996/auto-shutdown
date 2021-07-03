struct Time{
    int day;
    int hour;
    int min;
    int sec;
};
struct Time time;

int timeToSecond(struct Time *p){
    int second;
    second = p->day * 86400 + p->hour * 3600 + p->min * 60 + p->sec;
    return second;
}

void SecondToTime(int second){
    if (second == 0){return;}
    time.day = second / 86400;
    second = second % 86400;

    if (second == 0){return;}
    time.hour = second / 3600;
    second = second % 3600;

    if (second == 0){return;}
    time.min = second / 60;
    second = second % 60;

    time.sec = second;
}
