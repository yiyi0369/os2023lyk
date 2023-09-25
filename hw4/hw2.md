# os hw4

## 王一鸣 PB21000024

## 1

段错误：访问的地址是非法的,当程序访问某段的数据的时候，给出的偏移量超出了读取段的范围，此时访问的内容是非法的，这种情况就叫段错误。

tlb快表：快表是支持高速读写的一组存储单元，用来记录最近访问过的页表的内容，当程序提供虚拟地址的时候，先在快表中检查是否有对应的物理页号，即tlb是否命中，若不命中则从内存中的慢表中读出项并写入到快表中。

页错误：进程的内容按虚拟地址寻址，分页存储，当程序获取某一页的内容的时候，先查找页表valid位，若invalid，表示当前虚拟页不在内存中而存在辅存中，需要从辅存中调入，这种在内存中找不到所需页的情况就叫做页错误。

## 2

thrashing

在多道程序中，程序的大多数时间都在进行页面在内存和辅存中的换入换出操作，频繁的产生页错误就叫thrashing

thrashing产生的原因：

- 多道程序程度过高导致频繁的程序切换导致页面换入换出
- 物理页面少于程序所需要的页面数

## 3

100ns，需要访问两次内存，一次是找到页表项得到物理地址，一次是访问物理地址对应的内容

64ns cpu同时访问tlb和页表，则0.75（2+50）+0.25（50+50）=64ns

64.5ns不能同时访问tlb和页表，则0.75（2+50）+0.25（2+50+50）=64.5ns

## 4

计算缺页率
$$
\alpha (0.7*20*10^{6}+0.3*8*10^{6})+100=200
$$

$$
\alpha = 6*10^{-6}
$$

方程含义：第一项考虑页错误且写回的情况，第二项考虑页错误但不需写回的额外时间，第三项是正常访问所需时间

## 5

lru 18

栈情况：

- 7
- 27
- 327
- 132
- 213
- 521
- 352
- 435
- 643
- 764
- 764
- 176
- 017
- 501
- 450
- 643
- 264
- 326
- 032
- 103

共计18次

fifo 17

- 7
- 27
- 327
- 132
- 132
- 513
- 513
- 451
- 645
- 764
- 764
- 176
- 017
- 501
- 450
- 645
- 264
- 326
- 023
- 103

共计17次

optimal 13

- 7
- 72
- 723
- 123
- 123
- 153
- 153
- 154
- 156
- 157
- 157
- 157
- 150
- 150
- 140
- 160
- 120
- 130
- 130
- 130

共计13次、，每次替换未来最远使用的item即可

## 6

belady异常

某些页替换算法的页错误率随着分配的帧数增加而增加的现象称为belady异常

栈算法指的是用栈的数据结构实现的页置换算法，每当引用一个页的时候就将其置于栈顶，这样栈顶的页总是最新使用的页，栈底的页总是最早使用的页，每次换出的时候换出栈底的页。当分配帧增加的时候，原有的栈内元素总是新栈的子集，所以新栈集合总是比旧栈大，每次检查页是否在栈中，不在的可能性一定小于旧栈，即不存在belady异常。

## 7

fcfs 12011
$$
|2150-2069|+|2069-1212|+|1212-2296|+|2296-2800|+|2800-544|
$$

$$
+|1618-356|+|356-1523|+|1523-4965|+|4965-3681|=12011
$$



sstf 7589
$$
|2150-2069|+|2069-2296|+|2296-2800|+|2800-3681|+|3681-4965|
$$

$$
+|4965-1618|+|1618-1523|+|1523-1212|+|1212-544|+|544-356|=7589
$$



scan 9492
$$
5999-2150+5999-356=9492
$$


look 7434
$$
4965-2150+4965-356=7434
$$


c scan 11917
$$
5999-2150+5999+2069=11917
$$


c look 9849
$$
4965-2150+4965+2069=9849
$$


## 8

没有缓冲 7

先读根目录，找到a的entrey，然后读a的inode，读取a的数据；找到b的entry，读取b的inode，读取b的数据；找到c的inode，读取c的数据，共读取7次

缓冲 4

以上环节省去读取inode的三次操作，即可得到4次。

## 9

hard link直接指向该文件的inode，同时该inode的link count要计算hard link 的值

symbolic link重新分配了一个inode，其inode链接数据块的部分用来装入对应文件的路径名称，不改变原有的文件的link count



## 10


数据日志和元数据日志是两种不同的日志记录方法，用于数据管理和数据恢复。

数据日志是一种将数据的实际修改操作记录在日志中的方法。当对数据进行修改时，相应的修改操作将首先记录在日志中，然后再将修改应用到实际的数据存储位置。这种方法可以确保数据的完整性和一致性。如果系统发生故障或意外情况，可以通过读取日志来重新应用修改操作，从而恢复数据到故障发生之前的状态。数据日志记录的是对数据本身的修改，比如插入、更新或删除记录。

元数据日志则是一种记录文件系统元数据修改操作的方法。文件系统元数据包括文件和目录的属性信息，如文件名、大小、创建时间等。当对文件系统进行修改时，相应的操作也会被记录在日志中。与数据日志不同，元数据日志只记录对文件系统元数据的修改，不记录数据本身。

操作序列：

数据日志：先进行对日志的修改，依次提交txb，元数据，数据，txe，然后修改数据，元数据，最后提交

若系统在对日志修改时崩溃，则文件系统没有受到影响，跳过，若在修改数据时崩溃，则根据日志重新恢复即可

元数据日志：先进行对日志的修改，依次提交txb，元数据，txe，然后修改数据，元数据，最后提交

流程与数据日志相同。

元数据日志相较于数据日志，写入日志的数据量要小得多，节省了开销。