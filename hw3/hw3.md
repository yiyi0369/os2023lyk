<center><font size=10><b>操作系统</b></font></center>
<center><font size=10><b>HOMEWORK 3</b></font></center>

<center><font size=5>王一鸣</font></center>

<center><font size=5>PB21000024</font></center>

1. Q: What is race condition and how to address it?

   A:竞争情况指的是在多线程情况下多个进程相继访问共享数据并进行修改的情况下，由于可能的访问顺序不同，得到的程序执行结果可能不唯一；解决的办法是进行一定形式的进程同步，确保一段时间只能有一个进程能操作共享数据，由此可以引入临界区问题进行解决。

2. List all the three requirements of the entry and exit  implementation when solving the critical-section problem.

   临界区要求满足1）互斥性，即除该进程在临界区运行，其他进程不能运行2）前进性，如果没有临界区进程执行，从不在剩余区的进程进行挑选进入临界区，以保持等待序列一直在变化3）有限等待性，从某一进程发出进入临界区请求到进入临界区，等待时间必须是有限的，保证进程一定会被执行

3. For Peterson’s solution, prove that it satisfies the three  requirements of a solution for the critical section problem. Analyze whether strict alternation satisfies all the requirements.

   约定turn==i表示i正在执行，flag[i]表示i需要进入临界区

   1）互斥成立：由于等待条件是flag[j]&&turn\=\=j即j需要进入临界区且j在临界区的时候进行等待，假设存在同时执行的情况，则要求flag[i]\=\=1&&flag[j]==1，因为只有执行完毕程序之后flag才会被置0，且对i来说要求turn\!\=j，对j来说要求turn\!\=i才能同时进入，而这是不可能同时满足的，即互斥性得到了保证

   2）前进要求满足：假设i执行完毕后退出了临界区，j一直在等待中，此时i将flag[i]置为0，一旦i这样做了，j马上就可以停止等待，进入临界区，如果没有进程处于临界区，一旦j发出请求，马上就能进入临界区，前进要求满足

   3）有限等待要求满足：处于等待的j最多等待进程i执行完临界区一次马上就能进入临界区，故是有限等待

4. What is deadlock? List the four requirements of deadlock.

   死锁指的是多道程序环境下，多个系统竞争一定数量的资源，某个进程请求资源，如果此时资源不可用，进程就会进入等待状态。如果申请的进程被其他等待进程所占有，则该等待进程可能永远也无法改变其状态。换句话说就是，多个进程等待一个事件，但是这个事件只能由等待进程产生，导致等待一直进行下去。

   死锁的必要条件：1.互斥，某资源一次只能被一个进程使用2.占有并等待：一个进程占有资源，并等待另外的资源，而该资源被其他进程占有3.非抢占：资源只能在完成任务后自动释放4.循环等待：存在序列p0,p1,p2….pn,其中p1等p0占用的资源，p2等p1占用的资源，以此类推，p0等待pn占用的资源，导致整个集合陷入等待

5. Consider the following snapshot of a system: Using the banker’s algorithm, determine whether or not each of  the following states is unsafe. If the state is safe, illustrate the  order in which the threads may complete. Otherwise, illustrate  why the state is unsafe. a. Available = (2, 2, 2, 3) b. Available = (4, 4, 1, 1) c. Available = (3, 0, 1, 4) d. Available = (1, 5, 2, 2)

   根据银行算法，得到need矩阵

   | NEED | A    | B    | C    | D    |
   | :--: | ---- | ---- | ---- | ---- |
   |  T0  | 3    | 2    | 0    | 4    |
   |  T1  | 2    | 3    | 1    | 2    |
   |  T2  | 2    | 4    | 1    | 1    |
   |  T3  | 1    | 4    | 2    | 2    |
   |  T4  | 2    | 1    | 1    | 1    |

   | ALL  | A    | B    | C    | D    |
   | ---- | ---- | ---- | ---- | ---- |
   |      | 4    | 5    | 5    | 4    |

   a.{T4,T0,T1,T2,T3}

   b.{T2,T4,T1,T0,T3}

   c.不安全，因为任意一个进程的对B的需求都大于0，一旦对B请求资源，进程陷入等待死锁

   d.{T3,T2,T0,T1,T2}

6. What is semaphore? Explain the functionalities of semaphores.

   信号量机制指的是指定变量只能通过原子操作进行访问来改变的进程同步工具，这两种原子操作分别是signal和wait，其中，signal是信号量自增，wait当信号量非正的时候等待，等待完毕自减

7. Please use semaphore to provide a deadlock-free solution to  address the dining philosopher problem.

   ```c
   semaphore chopsticks[i];
   void eat(int i)//哲学家i吃饭
   {
       if(i%2==0)
       {
           wait(chopsticks[i%5]);
           wait(chopsticks[(i+1)%5]);
           //eat
           signal(chopstick[i%5]);
           signal(chopsticks[(i+1)%5]);
       }
       else{
           wait(chopsticks[(i+1)%5]);
           wait(chopsticks[i%5]);
           //eat
           signal(chopstick[i%5]);
           signal(chopsticks[(i+1)%5]);
       }
   }
   ```

   偶数哲学家先拿左手筷子，奇数哲学家先拿右手筷子，这样相邻的哲学家如果产生等待，那么等待的一方一定两只筷子都没有拿起，从而避免了一人拿一只筷子然后死锁的情况

8. Consider the following set of processes, with the length of the  CPU burst time given in milliseconds: The processes are assumed to have arrived in the order P1, P2,  P3, P4, P5, all at time 0. a) Draw four Gantt charts that illustrate the execution of these  processes using the following scheduling algorithms: FCFS,  SJF (nonpreemptive), nonpreemptive priority (a smaller  priority number implies a higher priority), and RR (quantum  = 1). b) What is the turnaround time of each process for each of the  scheduling algorithms in part a)? c) What is the waiting time of each process for each of these  scheduling algorithms? d) Which of the algorithms results in the minimum average  waiting time (over all processes)? e) Illustrate the pros and cons of the algorithms: FCFS, SJF,  priority scheduling and RR.

   ![img](file:///D:\qqdata\1484706473\1484706473\Image\Group2\]V\R8\]VR8QBYV4JLN3JJ7J]U7XUE_tmb.jpg)

   ![img](file:///D:\qqdata\1484706473\1484706473\Image\Group2\$O\%N\$O%N6UX3E5@1RX2H~%Q9XMV_tmb.jpg)

   d)SJF算法最短，总和为16

   e)pros and cons

   FCFS:

   优点：代码简单，容易理解和实现

   缺点：等待时间可能比较长，先来的长进程使得短进程阻塞很久，对于i/o密集型进程，cpu空闲比较严重

   SJF：

   优点：最短的等待时间，可以使得进程等待时间总和最短

   缺点：难于估计进程的运行时间，所以一般用于长期调度，对于短期调度，容易错误的估计进程时间导致额外的开销

   优先级调度：

   优点：能应对外部程序的需求，外部信息告诉操作系统什么是紧要的，什么不那么重要，使得重要的任务等待时间更短

   缺点：无穷阻塞，优先级太低的进程可能反复被优先级高的进程挤到队列后面，导致永远无法执行

   RR：

   优点：对于分时系统有着较好的性能，响应时间短，能立即提供输出

   缺点：等待时间长，频繁的进程切换会引入额外的开销，导致效率降低

9. illustarte the key ideas of rate-monotonic scheduling and earliestdeadline-first scheduling. Give an example to illustrate under  what circumstances rate-monotonic scheduling is inferior to  earliest-deadline-first scheduling in meeting the deadlines  associated with processes? 

   速率单调调度和最早截止时间优先调度是实时系统中常用的调度算法。

   速率单调调度:一种静态优先级调度算法，它基于任务的周期性和执行时间来分配优先级。根据速率单调调度算法，执行时间较短的任务具有较高的优先级，而执行时间较长的任务具有较低的优先级。这意味着任务的优先级是固定的，不会根据运行时的情况进行调整。速率单调调度的主要思想是在满足任务的截止时间要求的前提下，尽可能提高系统的利用率。

   最早截止时间优先调度:一种动态优先级调度算法，它基于任务的截止时间来分配优先级。根据最早截止时间优先调度算法，截止时间较早的任务具有较高的优先级，而截止时间较晚的任务具有较低的优先级。这意味着任务的优先级是根据任务的截止时间进行动态调整的。最早截止时间优先调度的主要思想是在保证任务的截止时间的前提下，尽可能提高任务的响应时间。

   在某些情况下，速率单调调度算法可能会优先级较高的任务错过其截止时间，而最早截止时间优先调度算法可以满足任务的截止时间要求。这种情况发生在任务的周期较短且执行时间较长的情况下。例如，假设有两个任务，任务A的周期为10毫秒，执行时间为8毫秒，任务B的周期为20毫秒，执行时间为15毫秒。根据速率单调调度算法，任务A的优先级较高，任务B的优先级较低。然而，由于任务A的执行时间较长，当任务A执行时，任务B的截止时间可能已经到达，导致任务B错过了截止时间。而最早截止时间优先调度算法可以动态地将任务B的优先级提高，以确保其在截止时间前完成。

   速率单调调度算法适用于执行时间较短的任务，而最早截止时间优先调度算法适用于需要满足严格截止时间要求的任务。在某些情况下，速率单调调度算法可能无法满足任务的截止时间要求，而最早截止时间优先调度算法可以更好地满足这些要求。