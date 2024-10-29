runtasks_ref
Linux x86_64
================================================================================
Running task system grading harness... (22 total tests)
  - Detected CPU with 40 execution contexts
  - Task system configured to use at most 8 threads
================================================================================
================================================================================
Executing test: super_super_light...
Reference binary: ./runtasks_ref_linux
Results for: super_super_light
                                        STUDENT   REFERENCE   PERF?
[Serial]                                8.655     12.313      0.70  (OK)
[Parallel + Always Spawn]               8.54      55.785      0.15  (OK)
[Parallel + Thread Pool + Spin]         8.532     29.083      0.29  (OK)
[Parallel + Thread Pool + Sleep]        8.706     28.337      0.31  (OK)
================================================================================
Executing test: super_super_light_async...
Reference binary: ./runtasks_ref_linux
Results for: super_super_light_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                8.756     12.191      0.72  (OK)
[Parallel + Always Spawn]               8.429     55.629      0.15  (OK)
[Parallel + Thread Pool + Spin]         8.556     26.492      0.32  (OK)
[Parallel + Thread Pool + Sleep]        30.866    15.692      1.97  (NOT OK)
================================================================================
Executing test: super_light...
Reference binary: ./runtasks_ref_linux
Results for: super_light
                                        STUDENT   REFERENCE   PERF?
[Serial]                                80.62     95.838      0.84  (OK)
[Parallel + Always Spawn]               80.259    88.368      0.91  (OK)
[Parallel + Thread Pool + Spin]         80.075    29.207      2.74  (NOT OK)
[Parallel + Thread Pool + Sleep]        80.693    36.093      2.24  (NOT OK)
================================================================================
Executing test: super_light_async...
Reference binary: ./runtasks_ref_linux
Results for: super_light_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                81.03     95.452      0.85  (OK)
[Parallel + Always Spawn]               79.448    80.543      0.99  (OK)
[Parallel + Thread Pool + Spin]         80.317    30.917      2.60  (NOT OK)
[Parallel + Thread Pool + Sleep]        37.437    28.054      1.33  (NOT OK)
================================================================================
Executing test: ping_pong_equal...
Reference binary: ./runtasks_ref_linux
Results for: ping_pong_equal
                                        STUDENT   REFERENCE   PERF?
[Serial]                                1297.133  1553.205    0.84  (OK)
[Parallel + Always Spawn]               1300.342  637.235     2.04  (NOT OK)
[Parallel + Thread Pool + Spin]         1298.614  227.654     5.70  (NOT OK)
[Parallel + Thread Pool + Sleep]        1298.222  229.657     5.65  (NOT OK)
================================================================================
Executing test: ping_pong_equal_async...
Reference binary: ./runtasks_ref_linux
Results for: ping_pong_equal_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                1294.45   1544.952    0.84  (OK)
[Parallel + Always Spawn]               1296.49   662.509     1.96  (NOT OK)
[Parallel + Thread Pool + Spin]         1293.489  226.582     5.71  (NOT OK)
[Parallel + Thread Pool + Sleep]        193.945   224.466     0.86  (OK)
================================================================================
Executing test: ping_pong_unequal...
Reference binary: ./runtasks_ref_linux
Results for: ping_pong_unequal
                                        STUDENT   REFERENCE   PERF?
[Serial]                                2423.047  2413.994    1.00  (OK)
[Parallel + Always Spawn]               2424.472  994.564     2.44  (NOT OK)
[Parallel + Thread Pool + Spin]         2415.343  336.256     7.18  (NOT OK)
[Parallel + Thread Pool + Sleep]        2418.192  340.859     7.09  (NOT OK)
================================================================================
Executing test: ping_pong_unequal_async...
Reference binary: ./runtasks_ref_linux
Results for: ping_pong_unequal_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                2429.01   2399.749    1.01  (OK)
[Parallel + Always Spawn]               2407.208  1001.25     2.40  (NOT OK)
[Parallel + Thread Pool + Spin]         2417.762  334.029     7.24  (NOT OK)
[Parallel + Thread Pool + Sleep]        344.299   328.969     1.05  (OK)
================================================================================
Executing test: recursive_fibonacci...
Reference binary: ./runtasks_ref_linux
Results for: recursive_fibonacci
                                        STUDENT   REFERENCE   PERF?
[Serial]                                1586.114  1943.062    0.82  (OK)
[Parallel + Always Spawn]               1583.425  537.562     2.95  (NOT OK)
[Parallel + Thread Pool + Spin]         1579.258  265.764     5.94  (NOT OK)
[Parallel + Thread Pool + Sleep]        1589.12   267.388     5.94  (NOT OK)
================================================================================
Executing test: recursive_fibonacci_async...
Reference binary: ./runtasks_ref_linux
Results for: recursive_fibonacci_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                1581.684  1939.945    0.82  (OK)
[Parallel + Always Spawn]               1585.249  556.636     2.85  (NOT OK)
[Parallel + Thread Pool + Spin]         1584.694  258.648     6.13  (NOT OK)
[Parallel + Thread Pool + Sleep]        220.133   254.85      0.86  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop...
Reference binary: ./runtasks_ref_linux
Results for: math_operations_in_tight_for_loop
                                        STUDENT   REFERENCE   PERF?
[Serial]                                808.963   853.519     0.95  (OK)
[Parallel + Always Spawn]               805.988   670.342     1.20  (NOT OK)
[Parallel + Thread Pool + Spin]         808.335   161.619     5.00  (NOT OK)
[Parallel + Thread Pool + Sleep]        808.814   171.624     4.71  (NOT OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_async...
Reference binary: ./runtasks_ref_linux
Results for: math_operations_in_tight_for_loop_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                808.41    856.84      0.94  (OK)
[Parallel + Always Spawn]               811.738   693.496     1.17  (OK)
[Parallel + Thread Pool + Spin]         808.998   145.345     5.57  (NOT OK)
[Parallel + Thread Pool + Sleep]        152.518   142.003     1.07  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_fewer_tasks...
Reference binary: ./runtasks_ref_linux
Results for: math_operations_in_tight_for_loop_fewer_tasks
                                        STUDENT   REFERENCE   PERF?
[Serial]                                812.871   853.427     0.95  (OK)
[Parallel + Always Spawn]               811.959   786.663     1.03  (OK)
[Parallel + Thread Pool + Spin]         808.715   240.807     3.36  (NOT OK)
[Parallel + Thread Pool + Sleep]        810.742   265.32      3.06  (NOT OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_fewer_tasks_async...
Reference binary: ./runtasks_ref_linux
Results for: math_operations_in_tight_for_loop_fewer_tasks_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                812.784   858.997     0.95  (OK)
[Parallel + Always Spawn]               812.874   811.4       1.00  (OK)
[Parallel + Thread Pool + Spin]         810.69    126.379     6.41  (NOT OK)
[Parallel + Thread Pool + Sleep]        122.005   126.256     0.97  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_fan_in...
Reference binary: ./runtasks_ref_linux
Results for: math_operations_in_tight_for_loop_fan_in
                                        STUDENT   REFERENCE   PERF?
[Serial]                                415.747   434.678     0.96  (OK)
[Parallel + Always Spawn]               414.407   191.573     2.16  (NOT OK)
[Parallel + Thread Pool + Spin]         413.572   81.48       5.08  (NOT OK)
[Parallel + Thread Pool + Sleep]        415.206   79.191      5.24  (NOT OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_fan_in_async...
Reference binary: ./runtasks_ref_linux
Results for: math_operations_in_tight_for_loop_fan_in_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                417.681   435.005     0.96  (OK)
[Parallel + Always Spawn]               413.541   244.769     1.69  (NOT OK)
[Parallel + Thread Pool + Spin]         413.021   75.503      5.47  (NOT OK)
[Parallel + Thread Pool + Sleep]        73.391    65.41       1.12  (OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_reduction_tree...
Reference binary: ./runtasks_ref_linux
Results for: math_operations_in_tight_for_loop_reduction_tree
                                        STUDENT   REFERENCE   PERF?
[Serial]                                413.744   435.895     0.95  (OK)
[Parallel + Always Spawn]               414.993   164.013     2.53  (NOT OK)
[Parallel + Thread Pool + Spin]         414.632   76.557      5.42  (NOT OK)
[Parallel + Thread Pool + Sleep]        414.279   77.985      5.31  (NOT OK)
================================================================================
Executing test: math_operations_in_tight_for_loop_reduction_tree_async...
Reference binary: ./runtasks_ref_linux
Results for: math_operations_in_tight_for_loop_reduction_tree_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                413.848   438.395     0.94  (OK)
[Parallel + Always Spawn]               414.925   195.032     2.13  (NOT OK)
[Parallel + Thread Pool + Spin]         414.513   72.565      5.71  (NOT OK)
[Parallel + Thread Pool + Sleep]        59.153    65.233      0.91  (OK)
================================================================================
Executing test: spin_between_run_calls...
Reference binary: ./runtasks_ref_linux
Results for: spin_between_run_calls
                                        STUDENT   REFERENCE   PERF?
[Serial]                                541.173   688.211     0.79  (OK)
[Parallel + Always Spawn]               539.27    365.127     1.48  (NOT OK)
[Parallel + Thread Pool + Spin]         541.293   371.862     1.46  (NOT OK)
[Parallel + Thread Pool + Sleep]        538.816   363.776     1.48  (NOT OK)
================================================================================
Executing test: spin_between_run_calls_async...
Reference binary: ./runtasks_ref_linux
Results for: spin_between_run_calls_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                539.15    688.619     0.78  (OK)
[Parallel + Always Spawn]               538.996   367.152     1.47  (NOT OK)
[Parallel + Thread Pool + Spin]         541.122   366.567     1.48  (NOT OK)
[Parallel + Thread Pool + Sleep]        288.853   365.048     0.79  (OK)
================================================================================
Executing test: mandelbrot_chunked...
Reference binary: ./runtasks_ref_linux
Results for: mandelbrot_chunked
                                        STUDENT   REFERENCE   PERF?
[Serial]                                529.357   539.994     0.98  (OK)
[Parallel + Always Spawn]               528.02    84.585      6.24  (NOT OK)
[Parallel + Thread Pool + Spin]         530.109   84.197      6.30  (NOT OK)
[Parallel + Thread Pool + Sleep]        528.762   84.839      6.23  (NOT OK)
================================================================================
Executing test: mandelbrot_chunked_async...
Reference binary: ./runtasks_ref_linux
Results for: mandelbrot_chunked_async
                                        STUDENT   REFERENCE   PERF?
[Serial]                                529.21    540.383     0.98  (OK)
[Parallel + Always Spawn]               529.572   79.375      6.67  (NOT OK)
[Parallel + Thread Pool + Spin]         532.618   84.158      6.33  (NOT OK)
[Parallel + Thread Pool + Sleep]        84.221    84.636      1.00  (OK)
================================================================================
Overall performance results
[Serial]                                : All passed Perf
[Parallel + Always Spawn]               : Perf did not pass all tests
[Parallel + Thread Pool + Spin]         : Perf did not pass all tests
[Parallel + Thread Pool + Sleep]        : Perf did not pass all tests
