#include <QCoreApplication>
#include <assert.h>
#include <QDebug>

//普通版本的strcpy，实现没有检查dst和src内存重叠问题,会崩溃
char* myStrcpy(char* dst, const char* src)
{ //const约束,内容不可变
    assert(src != Q_NULLPTR && dst != Q_NULLPTR); //参数非0检验
    char* pstr = dst;
    while ((*dst++ = *src++) != '\0'){}
    return pstr;
}

//检查内存重叠
char* my1Strcpy(char* dst, const char* src)
{
    assert(src != Q_NULLPTR && dst != NULL);
    char * nsrc = const_cast<char*>(src);
    char * adest = dst;
    size_t size = strlen(src);
    if (src < dst && (src + size) > dst) {
        //内存重叠,从后向前复制
        char* bsrcp = nsrc + size - 1;
        char* bdestp = dst + size - 1;
        while ((*bdestp-- = *bsrcp--) && size-- != 0){}
    } else {
        while ((*dst++ = *nsrc++) != '\0'){}
    }
    return dst;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char dest[10] = "hello";
    qDebug() << my1Strcpy(&dest[3], dest) << endl;
    return a.exec();
}
