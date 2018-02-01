

int prefix(int k, int bit[], int N) {
    int pos = 0, pot = 0;
    while((1 << (pot+1)) <= N) pot++;
    while(pot >= 0) {
        int size = 1 << pot;
        if(bit[pos + size] <= k) {
            k -= bit[pos + size];
            pos += size;
        }
        pot--;
    }
    return pos;
}
