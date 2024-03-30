
int _resetTime = 0;
void resetTimer()
{
    _resetTime = time_now;
}

bool delayTimer(int mili_seconds)
{
    if (abs(time_now - _resetTime) > mili_seconds)
    {
        return true;
    }
    return false;
}