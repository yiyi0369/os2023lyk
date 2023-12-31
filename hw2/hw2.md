# os hw2

## 王一鸣 PB21000024

1. 求出子进程的个数

   以i值计数

   i=0时只有一个父进程

   i=1时父进程生成一个子进程，共两个进程

   i=2时两个进程各自生成2个进程，共四个进程，以此类推

   i=4时共16个进程，其中15个是子进程

2. 解释在何种情况会到达某行，同时解释wait的作用

   子进程会到达该行，因为fork函数对子进程的返回值是0；

   wait的作用是使得父进程被挂起等待子进程结束然后继续执行

3. 给出ABCD处pid的值

   A pid=0

   B pid1=603

   C pid=603

   D pid1=600

4. 解释X,Y处的输出

   X处:

   CHILD: 0 CHILD: -1 CHILD: -4 CHILD:-9 CHILD: -16

   Y处:

   PARENT: 0 PARENT: 1 PARENT: 2 PARENT: 3 PARENT: 4

5. Y是否会被执行

   Y不会被执行，因为执行了execl系统调用，后续的代码被执行/bin/ls的程序替换

6. 解释一下什么数据会被放在用户空间和内核空间

   当进程运行在操作系统中时，它需要访问用户空间和内核空间内存。

   用户空间内存是进程分配的一部分内存，可以被用户级别代码访问。这包括进程的可执行代码、数据、堆栈和堆。换句话说，用户空间内存是应用程序的数据和代码所在的位置。

   内核空间内存是保护的内存区域，用于操作系统和其内核级别代码。用户级别代码无法直接访问此内存，并且它包含内核的代码、数据结构和设备驱动程序。操作系统还使用内核空间内存来管理系统级资源，例如进程调度、进程间通信和内存管理。

   在进程执行期间，同时使用用户空间和内核空间内存。进程的代码和数据加载到用户空间内存中，内核通过访问内核空间内存与进程交互。例如，当进程需要执行系统调用时，它从用户空间转换到内核空间，然后内核访问其内存以执行请求的操作。

   用户空间内存存储运行进程的数据和代码，而内核空间内存存储操作系统的代码、数据结构和设备驱动程序。在进程执行期间，两种类型的内存都被使用，内核访问其内存来管理进程并向用户级别代码提供服务。

7. 解释为什么终止状态是必要的

   进程的终止状态是必要的，因为它指定了进程何时终止。在完成每个步骤后，进程使用所有资源，内存变得空闲。进程控制块包含有关进程的信息，包括其状态。当进程终止时，它进入终止状态。在此状态下，操作系统释放分配给进程的资源。

   这对于操作系统来说非常重要，因为它可以知道该进程已经完成了它的任务，并且可以释放分配给该进程的所有资源。这样，操作系统就可以确保其他进程可以使用这些资源，并且可以避免出现资源泄漏等问题。

8. 解释僵尸进程是什么，如何限制僵尸进程

   僵尸进程是指已经完成执行的进程，但是其父进程还没有调用wait()或waitpid()来获取其终止状态，因此该进程的进程描述符仍然存在于系统中。僵尸进程会占用系统资源，如果系统中存在大量的僵尸进程，会导致系统资源的浪费。

   为了避免僵尸进程，可以让父进程通过wait和waitpid等函数等待子进程结束，这会导致父进程挂起。在子进程结束后，父进程会收到该信号，可以在handler中调用wait回收。

9. 解释exec和普通函数的区别

   普通函数经过调用跳至函数代码段，进行计算并返回调用处，不改变调用函数的原进程的代码段

   exec直接将后续代码段替换为指定的程序代码，并非简单的函数调用

10. 多线程是什么，哪些是被共享的

    多线程是指在同一时间内，多个线程在单个CPU上运行。多线程的好处在于可以提高程序的执行效率，因为多个线程可以同时执行不同的任务，从而减少了CPU的空闲时间。此外，多线程还可以提高程序的响应速度，因为当一个线程被阻塞时，其他线程可以继续执行。

    共享：堆和全局变量被共享，寄存器和栈被每个线程独占

11. a.几个进程被创建

    创建了5个子进程，共6个进程

    第一个fork创建了一个子进程，父进程在底部fork又创建一个子进程，第一个子进程在条件判断分支创建一个进程，然后分别在底部创建一个进程

    b.几个线程

    创建了4个线程

    在条件判断分支两个子进程分别创建了两个线程

    然后在底部fork调用将进程复制了各一次，则有4各被创建出来的新线程

12. 求C和P处的输出

    C:CHILD: value = 5

    P:PARENT: value =5

    这是由于child进程创建线程之后执行了join调用必须等待线程执行完毕，同时PARENT进程执行了WAIT调用必须等待CHILD进程结束，故值已经改变

13. ipc两种模型的好坏

    消息传递：消息传递指的是以操作系统内核为中介，进程将信息发给位于操作系统的信箱并从信箱获取信息

    pros：实现简单，易于提升并发性

    cons：通信速率低，需要系统调用帮助消息传递

    共享内存：在用户空间单独划定一块内存供两个进程读写

    pros：通信速度快，直接访问内存，不需要第三方

    cons：实现复杂，并发低，需要人为控制

14. 普通管道vs命名管道

    通信对象：

    普通管道只能用于兄弟、父子进程之间的通信

    命名管道可以用于非亲属之间的通信

    位置：

    普通管道放于内存，使用完毕后消失

    命名管道存放于文件系统中，使用完毕后不会消失

    可见性：

    普通管道在系统中没有实名，无法在文件系统中看到该管道，只是系统使用的临时资源

    命名管道是可见的，以特殊方式作为文件进行写入读出	