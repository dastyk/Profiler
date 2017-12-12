# Profiler

A header only profiler. The profiler is intended to detect areas of code that needs to be optimized. It does this by recording the call stack, the time each function/method take, the number of times a function/method is used.

A simple dot file is created for each thread, and due to the nature of dynamic libraries, one for each DLL.

