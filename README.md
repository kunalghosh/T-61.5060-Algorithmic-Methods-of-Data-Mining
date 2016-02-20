# T-61.5060-Algorithmic-Methods-of-Data-Mining
Course project of the Data Mining course taught by Aris Gionis at Aalto University.

The project was to implement probabilistic counting algorithms, specifically the Flajolet Martin Algorithm [1] 
for approximate F0 (unique elements in a sequence) and to Implement second moment F2 using the AMS [2] useful for
computing statistical properties of the data, such as the Gini coefficient of variation.

## Project Specifics:
In this project we implement exact and approximate implementations of F0 and F2. A separate readme describing how to use the code is present in the source sub-folder.

## Programming Languages used
We have implemented the project in a mix of C++ / Python and Shell (For quick multi-process parallelism) and as glue code.

[1] P. Flajolet and G. N. Martin. Probabilistic counting algorithms for data base applications. Journal
of computer and system sciences, 31(2):182–209, 1985.

[2] N. Alon, Y. Matias, and M. Szegedy. The space complexity of approximating the frequency
moments. In Proceedings of the twenty-eighth annual ACM symposium on theory of computing
(STOC), pages 20–29, 1996.
