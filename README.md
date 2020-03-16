# chudnovski_algorithm
Quick implementation of the Chudnovski algorithm in C++.

The implementation depends on the GNU MP library.

To compile it, run the file compile.sh, it produces the executable `chudnovsky_algorithm.run`.

The options to run the executable are `-m [floating-point precision] -o [file name] -p [precision]`.

The implementation successfully enumerated 1,000,000 digits of pi, with floating-point precision of 4,194,304. It takes a few hours with Linux Mint 17.3 Rosa running on Intel Pentium 2020M with 32 GB of RAM (<2% were used). (I did not measure precisely the time, only focused on the accuracy of the computation).

Thanks to the GNU MP library, the precision of pi that can be achieved only depends on the available RAM.

When the precision for pi increases, so should do the floating-point precision. Maybe a 1-to-3 ratio should be respected, further tests needed (I tried precision 1,000,000 for pi and 1,048,576 for the floating-point precision and obtained only one third of the digits of pi).

The amount of cache and the floating-point precision have a direct impact on the speed of the computation.
