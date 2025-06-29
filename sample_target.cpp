        FILETIME ftNow;
        ::SystemTimeToFileTime(&stNow, &ftNow);
        utcGetTickOffset = ConvertFileTime2Ms(&ftNow) - msDiff1970;
        utcGetTickOffset -= dwNowTick;

        bCached = true;
    }

    // Just add the tick count to the pre-calculated offset
    utc = utcGetTickOffset + dwNowTick;

    utc *= 1000;
#else
	struct timeval  tp;
	gettimeofday(&tp, NULL);
	utc = tp.tv_sec;
	utc *= 1000000;
	utc += tp.tv_usec;
#endif // WIN32

	return utc;
}

char* getTimeStamp(bool bEnableMicrosecond)
{
	// dump timestamp format : [12/31/2012|22:18:48.926]
	static char strTimeStamp[50] = "";

#if defined(WIN32) || defined(WINCE)
    SYSTEMTIME st;
    GetSystemTime(&st);
	sprintf(strTimeStamp, "[%02d/%02d/%04d|%02d:%02d:%02d.%03d]", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
	struct timeval tv;
	struct tm *ptm;
	gettimeofday(&tv, NULL);
	ptm = localtime(&tv.tv_sec);

	strTimeStamp[0] = '[';
	strftime(strTimeStamp+1, 50, "%m/%d/%Y|%T", ptm);
	if(bEnableMicrosecond)
	{
		sprintf(strTimeStamp + strlen(strTimeStamp), ".%03d-%03d]", (int)tv.tv_usec/1000, (int)tv.tv_usec%1000);
	}
	else
	{
		sprintf(strTimeStamp + strlen(strTimeStamp), ".%03d]", (int)tv.tv_usec/1000);
	}
#endif // WIN32

	return strTimeStamp;
}

char* getTimeStamp(rm_u64_t uUtcTime, bool bEnableMicrosecond)
{
	// dump timestamp format : [12/31/2012|22:18:48.926]
	static char strTimeStamp[50] = "";

	strTimeStamp[0] = 0;

	if(uUtcTime != 0)
	{
#if defined(WIN32) || defined(WINCE)
		SYSTEMTIME st;
		GetSystemTime(&st);
		sprintf(strTimeStamp, "[%02d/%02d/%04d|%02d:%02d:%02d.%03d]", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
		struct timeval tv;
		struct tm *ptm;
		tv.tv_usec = uUtcTime % 1000000;
		tv.tv_sec = uUtcTime / 1000000;
		ptm = localtime(&tv.tv_sec);

		strTimeStamp[0] = '[';
		strftime(strTimeStamp+1, 50, "%m/%d/%Y|%T", ptm);
		if(bEnableMicrosecond)
		{
			sprintf(strTimeStamp + strlen(strTimeStamp), ".%03d-%03d]", (int)tv.tv_usec/1000, (int)tv.tv_usec%1000);
		}
		else
		{
			sprintf(strTimeStamp + strlen(strTimeStamp), ".%03d]", (int)tv.tv_usec/1000);
		}
#endif // WIN32
	}

	return strTimeStamp;
}

