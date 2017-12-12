# Profiler

A header only profiler. The profiler is intended to detect areas of code that needs to be optimized. It does this by recording the call stack, the time each function/method take, the number of times a function/method is used.

A simple dot file is created for each thread, and due to the nature of dynamic libraries, one for each DLL.
Functions/methods will be highlighted with colors ranging from green to red, with red indicaing that a function/method takes a substantial amount of time when comparing the total time taken for the function/method calling the first. The highlight is meant to give an indication of which functions that needs to be optimized.
