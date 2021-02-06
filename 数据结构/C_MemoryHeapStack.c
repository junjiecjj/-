/*************************************************************************
>> File Name: C_static_gloable.c
>> Author: 陈俊杰
>> Mail: 2716705056qq.com
>> Created Time: 2021年01月09日 星期六 22时54分58秒
>> 此程序的功能是：

------------------------------------------------  第一种说法--------------------------------------------------------
https://mp.weixin.qq.com/s?__biz=MzA3MTU1MzMzNQ==&mid=2247484249&idx=1&sn=04e2f75ad6b299563a14353acb46c260&chksm=9f2a9b01a85d12178aef3b2dc944e3a697f473fa5a7f01bac7eebc8baf6b4967d6e505d1157c&scene=0&xtrack=1#rd

一个由 C/C++ 编译的程序占用的内存分为以下几个部分

1、栈区（stack）：由编译器自动分配释放 ，存放函数的参数值，局部变量的值等。其
操作方式类似于数据结构中的栈。

2、堆区（heap）：一般由程序员分配释放， 若程序员不释放，程序结束时可能由 OS 回
收 。注意它与数据结构中的堆是两回事，分配方式倒是类似于链表，呵呵。

3、全局区（静态区）（static）：全局变量和静态变量的存储是放在一块的，初始化的
全局变量和静态变量在一块区域， 未初始化的全局变量和未初始化的静态变量在相邻的另
一块区域。 - 程序结束后由系统释放。

4、文字常量区：常量字符串就是放在这里的。 程序结束后由系统释放

5、程序代码区：存放函数体的二进制代码。


堆和栈的区别可以用如下的比喻来看出
使用栈就象我们去饭馆里吃饭，只管点菜（发出申请）、付钱、和吃（使用），吃饱了就走，不必理会切菜、洗菜等准备工作和洗碗、刷锅等扫尾工作，他的好处是快捷，但是自由度小。
使用堆就象是自己动手做喜欢吃的菜肴，比较麻烦，但是比较符合自己的口味，而且自由 度大。 (经典！)


申请方式
stack:
由系统自动分配。 例如，声明在函数中一个局部变量 int b;
系统自动在栈中为 b 开辟空 间

heap:
需要程序员自己申请，并指明大小，在 c 中 malloc 函数
如 p1 = (char *) malloc (10);
在 C++ 中用 new 运算符
如 p2 = new char [10];
但是注意 p1、p2 本身是在栈中的。

申请后系统的响应
栈：只要栈的剩余空间大于所申请空间，系统将为程序提供内存，否则将报异常提示栈溢 出。

堆：首先应该知道操作系统有一个记录空闲内存地址的链表，当系统收到程序的申请时， 会遍历该链表，寻找第一个空间大于所申请空间的堆结点，然后将该结点从空闲结点链表 中删除，并将该结点的空间分配给程序，另外，对于大多数系统，会在这块内存空间中的 首地址处记录本次分配的大小，这样，代码中的 delete 语句才能正确的释放本内存空间。 另外，由于找到的堆结点的大小不一定正好等于申请的大小，系统会自动的将多余的那部 分重新放入空闲链表中。

申请大小的限制
栈：在 Windows 下，栈是向低地址扩展的数据结构，是一块连续的内存的区域。这句话的意 思是栈顶的地址和栈的最大容量是系统预先规定好的，在 WINDOWS 下，栈的大小是 2M（也有 的说是 1M，总之是一个编译时就确定的常数），如果申请的空间超过栈的剩余空间时，将 提示 overflow。因此，能从栈获得的空间较小。

堆：堆是向高地址扩展的数据结构，是不连续的内存区域。这是由于系统是用链表来存储 的空闲内存地址的，自然是不连续的，而链表的遍历方向是由低地址向高地址。堆的大小 受限于计算机系统中有效的虚拟内存。由此可见，堆获得的空间比较灵活，也比较大。

申请效率的比较：
栈由系统自动分配，速度较快。但程序员是无法控制的。

堆是由 new 分配的内存，一般速度比较慢，而且容易产生内存碎片，不过用起来最方便。另外，在 WINDOWS 下，最好的方式是用 VirtualAlloc 分配内存，他不是在堆，也不是在栈是 直接在进程的地址空间中保留一块内存，虽然用起来最不方便。但是速度快，也最灵活。

堆和栈中的存储内容
栈： 在函数调用时，第一个进栈的是主函数中后的下一条指令（函数调用语句的下一条可 执行语句）的地址，然后是函数的各个参数，在大多数的 C 编译器中，参数是由右往左入栈 的，然后是函数中的局部变量。注意静态变量是不入栈的。 当本次函数调用结束后，局部变量先出栈，然后是参数，最后栈顶指针指向最开始存的地
址，也就是主函数中的下一条指令，程序由该点继续运行。

堆：一般是在堆的头部用一个字节存放堆的大小。堆中的具体内容由程序员安排。

存取效率的比较
char s1[] = "aaaaaaaaaaaaaaa";
char *s2 = "bbbbbbbbbbbbbbbbb";
aaaaaaaaaaa 是在运行时刻赋值的；
而 bbbbbbbbbbb 是在编译时就确定的；
但是，在以后的存取中，在栈上的数组比指针所指向的字符串 (例如堆) 快。
比如：
#include "stdio.h"

void main(void)
{
  char   a   =   1;
  char   c[]   =   "1234567890";
  char   *p   ="1234567890";
  a   =   c[1];
  a   =   p[1];
  return;
}
  对应的汇编代码
  10:   a   =   c[1];
  00401067   8A   4D   F1   mov   cl,byte   ptr   [ebp-0Fh]
  0040106A   88   4D   FC   mov   byte   ptr   [ebp-4],cl
  11:   a   =   p[1];
  0040106D   8B   55   EC   mov   edx,dword   ptr   [ebp-14h]
  00401070   8A   42   01   mov   al,byte   ptr   [edx+1]
  00401073   88   45   FC   mov   byte   ptr   [ebp-4],al

  第一种在读取时直接就把字符串中的元素读到寄存器 cl 中，
而第二种则要先把指针值读到 edx 中，再根据 edx 读取字符，显然慢了。
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <sys/socket.h>
#include <stddef.h>
#include <locale.h>
#include <time.h>
#include <complex.h>

int a = 0; //全局初始化区

char *p1; //   全局未初始化区
int main(int argc, char *argv[])
{
  int b;                   //   栈
  char s[] = "abc";        //   栈
  char *p2;                //   栈
  char *p3 = "123456";     //   123456/0在常量区，p3在栈上。p3是指向了了常量区的字符串，字符串位于静态存储区，它在程序生命期内恒定不变，所以字符串还在。
  static int c = 0;        //   全局（静态）初始化区
  p1 = (char *)malloc(10); //分配得来得10和20字节的区域就在堆区。
  p2 = (char *)malloc(20);

  strcpy(p1, "123456"); //   123456/0放在常量区，编译器可能会将它与
                        //p3所指向的"123456" 优化成一个地方。
}
/*
------------------------------------------------第二种说法-- ------------------------------------------------------
https://mp.weixin.qq.com/s?__biz=MzA3MTU1MzMzNQ==&mid=2247484274&idx=1&sn=fd2ba0d6de5a14e5f0a690cda23869bc&chksm=9f2a9b2aa85d123c2a3ab49d7371a6765cbfe1b94eae442f1914485685c4512c673658623987&mpshare=1&scene=1&srcid=0119yLAfvAcaPEZ4Th0y067i&sharer_sharetime=1611021090648&sharer_shareid=0d5c82ce3c8b7c8f30cc9a686416d4a8#rd

C语言内存分配的框图如下，一个正常的执行代码， 操作系统需要给他分配一段内存区域，这一大块内存区域还要分为几个小区域。



1. 文本段（Text segment）
2. 初始化数据段（Initialized data segment）
3. 未初始化数据段（Uninitialized data segment）
4. 堆栈（Stack）
5. 堆 （Heap）

、文本段：
文本段，也称为代码段，是目标文件或内存中包含可执行指令的程序的一部分。

作为存储区域，文本段可以放置在堆或堆栈下方，以防止堆和堆栈溢出覆盖它。

通常，文本段是可共享的，因此对于频繁执行的程序（例如文本编辑器，C 编译器，shell 等），只需要一个副本就可以在内存中。此外，文本段通常是只读的，以防止程序意外修改其指令。



文本段可以看做 这段代码 的 大脑，需要怎么执行，做什么，都把数据保存在这个位置了。



2、初始化数据段：
初始化数据段，通常简称为数据段。数据段是程序的虚拟地址空间的一部分，其包含由程序员初始化的全局变量和静态变量。

请注意，数据段不是只读的，因为变量的值可以在运行时更改。

该段可以进一步分类为初始化的只读区域和初始化的读写区域。

例如，C 中的 char s [] =“hello world” 定义的全局字符串，和 int debug = 1 之类的 C 语句 将存储在初始化的读写区域中。像 const char * string =“hello world” 这样的全局 C 语句 会把 字符串文字 “hello world” 存储在初始化的只读区域中，而字符指针变量字符串存储在初始化的读写区域中。

例如：static int i = 10 将存储在数据段中，global int i = 10 也将存储在数据段中

3、未初始化的数据段：

未初始化的数据段，通常称为 “bss” 段，以古代汇编运算符命名，代表 “由符号启动的块”。此段中的数据在程序启动之前由内核初始化为算术 0 执行

未初始化的数据从数据段的末尾开始，包含初始化为零或在源代码中没有显式初始化的所有全局变量和静态变量。

例如，变量声明为 static int i; 将包含在 BSS 部分中。
例如，一个声明为 int j 的全局变量； 将包含在 BSS 部分中。

4、堆栈：

我们很多时候说的堆栈，实际上就是栈（ stack ）跟堆（ heap ）是没有关系的。我们学习上经常说的 压栈，说的就是压堆栈，因为堆栈有 「先进后出的原则」，所以我们操作的是栈尾。

堆栈区域传统上与堆区域相邻并向相反方向增长； 当堆栈指针遇到堆指针时，可用内存耗尽（因为理论上这个两个家伙是不可能 相遇的） 。（使用现代大地址空间和虚拟内存技术，它们几乎可以放置在任何地方，但它们通常仍会朝着相反的方向发展。）

堆栈区域包含程序堆栈，LIFO 结构，通常位于存储器的较高部分。在标准的 PC x86 计算机体系结构上，它向零地址发展； 在其他一些架构上，它朝着相反的方向发展。“堆栈指针” 寄存器跟踪堆栈的顶部； 每次将值 “推” 到堆栈上时都会调整它。

5、堆：
堆是通常发生动态内存分配的段。

堆区域从 BSS 段的末尾开始，并从那里增长到更大的地址。堆区域由 malloc，realloc 和 free 管理，可以使用 brk 和 sbrk 系统调用来调整其大小；它们也可以使用 mmap 实现，将不连续的虚拟内存区域保留到进程的 “虚拟地址空间” 中。堆区域由进程中的所有共享库和动态加载的模块共享。

实用 size 命令可以分析生成的可执行程序每个段的大小，单位是（bytes 字节）。我们可以用这个命令验证上面的论证。

#include<stdio.h>

int main()
{
    return 0;
}
Linux@dev:~/cStudy$ gcc memory-test.c -o memory-test && size memory-test
   text    data     bss     dec     hex filename
   1099     544       8    1651     673 memory-test
Linux@dev:~/cStudy$

现在代码里面什么都没有，可以看到每个段内容的大小。
#include<stdio.h>

int g;

int main()
{
    static int i;
    return 0;
}
--------------------------------------------------
Linux@dev:~/cStudy$ gcc memory-test.c -o memory-test && size memory-test
   text    data     bss     dec     hex filename
   1099     544      16    1659     67b memory-test
Linux@dev:~/cStudy$

我们声明了一个未初始化的全局变量和一个未初始化的静态变量后，bss 段发生了变化。

再修改一下：
#include<stdio.h>

int g = 99;

int main()
{
    static int i = 100;
    return 0;
}
--------------------------------------------------
Linux@dev:~/cStudy$ gcc memory-test.c -o memory-test && size memory-test
   text    data     bss     dec     hex filename
   1099     552      8     1659     67b memory-test
Linux@dev:~/cStudy$

初始化后 bss 段变成原来 8 了， data 段多了 8 个字节。

再修改一下
#include<stdio.h>

int g = 99;

int main()
{
    static int i = 100;
    return 0;
}
--------------------------------------------------
Linux@dev:~/cStudy$ gcc memory-test.c -o memory-test && size memory-test
   text    data     bss     dec     hex filename
   1099     552      8     1659     67b memory-test
Linux@dev:~/cStudy$

这样 bss 段和 data 段都比初始值增加了 4 个字节。

------------------------------------------------第三种说法-- ------------------------------------------------------
https://mp.weixin.qq.com/s?__biz=MzIzNjgxNjA3MQ==&mid=2247484988&idx=1&sn=f366c998dd8c3b5cbe7febdadbcf74bc&chksm=e8d35594dfa4dc82302f9abc19de73f3d6f047053c700c378269ffa7ab42857dda3348be95ca&scene=0&xtrack=1#rd
因为指针本身使用的复杂性与普适性，所以考点非常多，而且也可以与其他知识相互结合，

因此我们将会使用五篇专题的篇幅来介绍指针。分析下面的程序，指出程序中的错误：

# include <stdio.h>

int main( void)

{

char a;

char *str=&a;

strcpy(str,"hello");

printf("%s ",str);

return 0;

}

本题解析

没有正确为 str 分配内存空间，将会发生异常。

问题出在将一个字符串复制进一个字符变量指针所指地址。

虽然编译的时候没有报错，但是在运行过程中，因为越界访问了未被分配的内存，而导致段错误。

相关知识点
在处理与指针相关的问题时，首先需要搞明白的就是内存，因为指针操作的就是内存。

第一个，就是内存的分区。这也是经常会被考察的一个考点。

写出内存分为几大区域

对于这个问题，有几种不不同的说法。

有的说内存分为五大分区，有的说分为四大分区，我们先来先看五个分区的说法：

认为内存分为五大分区的人，通常会这样划分：

1、BSS 段 (bss segment)
通常是指用来存放程序中未初始化的全局变量和静态变量 （这里注意一个问题：一般的

书上都会说全局变量和静态变量是会自动初始化的，那么哪来的未初始化的变量呢？变量的初始化可以分为显示初始化和隐式初始化，全局变量和静态变量如果程序员自己不初始化的话的确

也会被初始化，那就是不管什么类型都初始化为 0, 这种没有显示初始化的就是我们这里所说的未初始化。

既然都是 0 那么就没必要把每个 0 都存储起来，从而节省磁盘空间，这是 BSS 的主要作用）的一块内存区域。

BSS 是英文 Block Started by Symbol 的简称。BSS 段属于静态内存分配。

BSS 节不不包含任何数据，只是简单的维护开始和结束的地址，即总大小。

以便内存区能在运行时分配并被有效地清零。BSS 节在应用程序的二进制映象文件中并不存在，

即不占用磁盘空间而只在运行的时候占用内存空间 , 所以如果全局变量和静态变量未初始化那么其可执行文件要小很多。

2、数据段 (data segment)
通常是指用来存放程序中已经初始化的全局变量和静态变量的一块内存区域。

数据段属于静态内存分配，可以分为只读数据段和读写数据段。

字符串常量等，但一般都是放在只读数据段中。

3、代码段 (code segment/text segment)
通常是指用来存放程序执行代码的一块内存区域。

这部分区域的大小在程序运行前就已经确定，

并且内存区域通常属于只读， 某些架构也允许代码段为可写，即允许修改程序。

在代码段中，也有可能包含一些只读的常数变量，例例如字符串常量等，但一般都是放在只读数据段中 。

4、堆 (heap)
堆是用于存放进程运行中被动态分配的内存段，它的大小并不固定，可动态扩张或缩减。

当进程调用 malloc 等函数分配内存时，新分配的内存就被动态添加到堆上 (堆被扩张);

当利用 free 等函数释放内存时，被释放的内存从堆中被剔除 (堆被缩减)

5、栈 (stack)
栈又称堆栈，是用户存放程序临时创建的局部变量，也就是说我们函数括弧 “{}” 中定义

的变量 (但不不包括 static 声明的变量，static 意味着在数据段中存放变量)。

除此以外，在函数被调用时，其参数也会被压入发起调用的进程栈中，并且待到调用结束后，

函数的返回值也会被存放回栈中。由于栈的先进先出特点，所以 栈特别方便用来保存 / 恢复调用现场。

从这个意义上讲，我们可以把堆栈看成一个寄存、交换临时数据的内存区。

而四大分区的说法，则这么认为：
1、堆区：

由程序员手动申请，手动释放，若不手动释放，程序结束后由系统回收，生命周期是整个程序运

行期间。使用 malloc 或者 new 进行堆的申请，堆的总大小为机器器的虚拟内存的大小。

说明：new 操作符本质上是使用了 malloc 进行内存的申请，new 和 malloc 的区别如下：

（1）malloc 是 C 语言中的函数，而 new 是 C++ 中的操作符。

（2）malloc 申请之后返回的类型是 void*，而 new 返回的指针带有类型。

（3）malloc 只负责内存的分配而不会调用类的构造函数，而 new 不仅会分配内存，

而且会自动调用类的构造函数。

2、栈区：

由系统进行内存的管理理。主要存放函数的参数以及局部变量。

在函数完成执行，系统自行释放栈区内存，不需要用户管理。

整个程序的栈区的大小可以在编译器器中由用户自行设定，

VS 中默认的栈区大小为 1M，可通过 VS 手动更改栈的大。

64bits 的 Linux 默认栈大小为 10MB，可通过 ulimit-s 临时修改。

3、静态存储区：

静态存储区内的变量在程序编译阶段已经分配好内存空间并初始化。这块内存在程序的整个运行

期间都存在，它主要存放静态变量、全局变量和常量。

注意：（1）这里不区分初始化和未初始化的数据区，是因为静态存储区内的变量若不显示初始化，

则编译器会自动以默认的方式进行初始化，

即静态存储区内不存在未初始化的变量。

（2）静态存储区内的常量分为常变量和字符串常量，一经初始化，不可修改。

静态存储内的常变量是全局变量，与局部常变量不不同，

区别在于局部常变量存放于栈，实际可间接通过指针或者

引用进行修改，而全局常变量存放于静态常量区则不可以间接修改。

（3）字符串常量存储在静态存储区的常量区，字符串常量的名称即为它本身，属于常变量。

（4）数据区的具体划分，有利利于我们对于变量类型的理理解。

不同类型的变量存放的区域不同。后面将以实例代码说明这四种数据区中具体对应的变量。

4、代码区：
存放程序体的二进制代码。比如我们写的函数，都是在代码区的。

通过上面的不同说法，我们也可以看出，这两种说法本身没有优劣之分，

具体的内存划分也跟编译器有很大的关系，因此这两种说法都是可以接受的，

搞明白内存的分区之后，指针的使用才能够更更加的灵活

*/
