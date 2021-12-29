typedef unsigned int Index;


/*
 * 关键字是字符串；在这种情况下，散列函数需要仔细地选择。
 * 一种选择方法是把字符串的 ASCII 码值加起来。
  
 */
Index Hash_Code( const char *Key, int TableSize )
{
    unsigned int HashVal = 0;

    while (*Key != '\0')
    {
        HashVal += *Key++;
    }
    return HashVal % TableSize;
}

/*
 * 另一种散列函数假设 Key 至少有两个字符外加 NULL 结束符。
 * 值 27 表示英文字母表的字母个数外加一个空格， 而 729 = 27 * 27。
 * 该函数只考查前三个字符，但是，假如它们是随机的，而标的大小像前面那样还是 10007，那么我们就会得到一个合理的均衡分配
 * 虽然很容易计算，但是当散列表足够大的时候这个函数还是不合适的。
*/

Index Hash_3Code( const char *Key, int TableSize )
{
    return (Key[0] + 27 * Key[1] + 729 * Key[2]) % TableSize ;
}

/*
 * Horner 法则
 * 计算 hk = k1 + 27*k2 + 27*27*k3 的另一种方式
 * hk = ((k3) * 27 + k2) * 27 + k1
*/

Index Hash_Horner( const char *Key, int TableSize )
{
    unsigned int HashVal = 0;

    while (*Key != '\0')
    {
        HashVal = (HashVal << 5) + *Key++;
    }

    return HashVal % TableSize;
}