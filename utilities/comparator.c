long double strongMax(long double n1, long double n2){return n1 > n2 ? n1 : n2;}
long double strongMin(long double n1, long double n2){return n1 < n2 ? n1 : n2;}
long double weakMax(long double n1, long double n2){return n1 >= n2 ? n1 : n2;}
long double weakMin(long double n1, long double n2){return n1 <= n2 ? n1 : n2;}

int strongMaxComparison(long double n1, long double n2){return n1 > n2 ? 1 : -1;}
int strongMinComparison(long double n1, long double n2){return n1 < n2 ? 1 : -1;}
int weakMaxComparison(long double n1, long double n2){return n1 >= n2 ? 1 : -1;}
int weakMinComparison(long double n1, long double n2){return n1 <= n2 ? 1 : -1;}