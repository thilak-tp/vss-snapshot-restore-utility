![screenshot](resources/gitbanner_cut.png)
## Fast Block-Based VSS Snapshot restore utility
![screenshot](resources/run.png)

## Testing

### Sinlge Threaded VSS Restoration Benchmark
#### Test Setup:
- VSS Snapshot Used of :  E:\ Drive of 10GBs (NTFS) with file.bin binary file of 2.53GB and a folder called folder with the same binary file.
- Files and Folders : E:\file.bin
                      E:\folder\file.bin
                      Total Size: 5.07 GB
- Drive Used: NVMe SSD Samsung
- Target Drive:  F:\ Drive of 10GBs (NTFS) Empty
#### Benchmark for various blocksizes
Sl no
Blocksize
Latency for restoration
1.
1KB
16074 ms (16.074 seconds)
2.
64KB
5920 ms (5.920 seconds)
3
128KB
4796 ms (4.796 seconds)
4
512KB
4107 ms (4.107 seconds)
5
1024KB
4241 ms (4.241 seconds)
6
2048KB
3880 ms (3.880 seconds)
7
4096KB
3699ms (3.699 seconds)
8
8192KB
3837ms (3.837 seconds)
9
16384
5488 ms (5.488 seconds)



