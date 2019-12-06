template <typename T>
void sortShell(T *begin, T *end)
{
	int size = end-begin+1;
	for(int step = size/2; step > 0; step/=2)
		for (int i = step ; i < size; i++)
		{
			int j;
			T tmp = *(begin+i);
			for (j = i; j>=step && cmp<T>(*(begin + j - step),tmp); j -= step)
				*(begin+j) = *(begin + j - step);
			*(begin+j) = tmp;
		}
}

template <typename T>
bool cmp(T a, T b)
{
	return a>b;
}

template <>
bool cmp<char *>(char *a, char *b)
{
	for(;*a==*b;++a,++b)
		if(*b == '\0')
			return false;
	return *a>*b;
}
