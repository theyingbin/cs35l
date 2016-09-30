For this homework, I had to parallelize the ray tracer code so it supports multithreading. To do this, I split up the work amongst the threads by creating partitions for the pixels for each thread
to work on. One problem I faced was figuring out why when I multithread the process, it would have some differences in the ppm folder while the picture still looked the same. After a closer
inspection of the picture made from gimp, I realized that there was a black row on the bottom missing. This was because I forgot to assign a thread to work on the last couple rows of pixels
since the partition is created through integer division. I resolved this by just assigning that piece of work to the last thread.

Another problem I faced was learning to use the API for pthread_create. It took me a while to wrap my head around how the function works and what I'm supposed to give in for arguments.

My implementation of SRT improves its performance roughly linearly dependent on the number of threads there are. It's only roughly linear since the last thread gets the most work, thus
the last thread is the bottleneck of the program. This can be seen from the runtimes of the program with varying amounts of threads as shown below:

time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m52.054s
user    0m52.013s
sys     0m0.005s

time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m26.772s
user    0m52.184s
sys     0m0.002s

time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m18.464s
user    0m54.131s
sys     0m0.003s

time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m12.030s
user    0m56.230s
sys     0m0.001s

As we can see, the runtime is roughly linear, but as more threads are used, we can see that the linearity is compromised by the last thread which has extra work. 
