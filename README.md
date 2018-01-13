# Profiler

A header only profiler. The profiler is intended to detect areas of code that needs to be optimized. It does this by recording the call stack, the time each function/method take, the number of times a function/method is used.

A simple dot file is created for each thread, and due to the nature of dynamic libraries, one for each DLL.
Functions/methods will be highlighted with colors ranging from green to red, with red indicaing that a function/method takes a substantial amount of time when comparing the total time taken for the function/method calling the first. The highlight is meant to give an indication of which functions that needs to be optimized.

# Usage
Simply include Profiler.h and write StartProfile at the beginning of a function. This will use the current functions name and record the time, times called and more.
You can also use StartProfileC to give it a custom name, this also allows for nesting in the same function.
For use in lambdas use StartProfileC, otherwise the name will be of the function the lamda is defined in.

Then define the preproccesor definition __PROFILE
