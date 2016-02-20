The Source code is divided into two main folders, 

    "exact" to keep source code for calculating exact F0 and F2 values.
    "approximate" to keep souce code for calculating the approximations.

The source code has been tested on Mac OSX 10.11.2 with 

clang with c++11
----------------
Apple LLVM version 7.0.2 (clang-700.1.81)
Target: x86_64-apple-darwin15.2.0
Thread model: posix

Python with Numpy
-----------------
Python 2.7.10 :: Anaconda 2.3.0 (x86_64)
Numpy 1.10.1

Access to Bash shell is assumed and a few shell scripts have been used to 
automate the compilation of c++ code and also to run multiple processes. 
So it is adviced to run the script on a server with multiple cores.

Exact value calculation:
------------------------
Single Pass
-----------
    cd soure/exact/single_pass/
    curl -s -N http://dendrite.ics.hut.fi/twitter_words.txt.gz | gunzip -c | python test.py
    
    Alternately
    -----------
    
    g++ -std=c++11 -Ofast test.cpp -o test
    curl -s -N http://dendrite.ics.hut.fi/twitter_words.txt.gz | gunzip -c | ./test

Multi Pass
----------
    cd source/exact/multi_pass/
    
    To run for a subset of the stream ( This compiles the corresponding c++ code and runs for a stream of length 2000000)
    ---------------------------------------------------------------------------------------------------------------------
    bash run_multipass.sh

    To run for the full stream (WARNING:Dumps uncompressed itermediate files. Might require ~10GB free disk space)
    --------------------------------------------------------------------------------------------------------------
    bash run_multipass_full.sh

Approximate Values:
-------------------
    cd source/approximate/
    
    F0 (WARNING : The Below Script Spawns 65 processes)
    ---------------------------------------------------
    bash calculate_f0.sh <hash_function_name> <stream_length>
    
        Possible hash function names (See source/approximate/hashes.cpp) 
        ----------------------------------------------------------------
        poly (Polynomial)
        rsh  (RSHash)
        djb2 (DJB2 Hash)
        paul (paul Hash)
        cpp  (Default C++ String Hash)
        jenkins (Jenkins Hash)
        mm2   (Murmur2 32bit)
        mm64a (Murmur3 64bit)
        
        NOTE: Manual compilation can be done as follows : g++ -std=c++11 -Ofast f0_args.cpp hashes.cpp -o f0_args

    F2
    --
    g++ -std=c++11 -Ofast f2_newv2_1.cpp -o f2_newv2_1
    curl -s -N http://dendrite.ics.hut.fi/twitter_words.txt.gz | gunzip -c | ./f2_newv2_1 ; python mean_of_medians.py f2_values_cpp.txt

    Alternately
    -----------
    curl -s -N http://dendrite.ics.hut.fi/twitter_words.txt.gz | gunzip -c | python f2_new2_2.py

Generating the Plots
--------------------
    cd source/approximate/hash_collisions
    bash get_plots.sh
