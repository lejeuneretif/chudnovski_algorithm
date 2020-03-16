#include "chudnovsky_algorithm.hpp"

#include <fstream>
#include <gmpxx.h>
#include <iostream>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char** argv) {
  size_t demanded_precision = 0;
  mp_bitcnt_t precision_mpf = 0;
  std::ofstream output_file;

  int opt;
  while((opt = getopt(argc, argv, "m:o:p:")) != -1) {
    switch(opt) {
      case 'm':
        sscanf( optarg, "%zu", &precision_mpf );
        std::cout << "The precision for the floating-point computations is " << precision_mpf << std::endl;
        break;
      case 'o':
        output_file.open( optarg );
        if( ! output_file.good() ) {
          std::cerr << "Can't open demanded file for writing" << std::endl;
          return -1;
        }
        else {
          std::cout << "File " << optarg << " OK for writing" << std::endl;
        }
        break;
      case 'p':
        sscanf( optarg, "%zu", &demanded_precision );
        std::cout << "The demanded precision for pi is " << demanded_precision << std::endl;
        break;
      default:
        std::cerr << "Usage -m [floating-point precision] -o [file name] -p [precision]" << std::endl;
        return -1;
    }
  }

  std::cout << "Chudnovsky algorithm is running" << std::endl;

  mpf_set_default_prec( precision_mpf );

  mpz_class chud_algo_l( "13591409" );
  mpz_class chud_algo_l_aux( "545140134" );

  mpz_class chud_algo_x( 1 );
  mpz_class chud_algo_x_aux( "-262537412640768000" );

  mpf_class chud_algo_m( 1 );

  mpz_class chud_algo_k( 6 );

  mpf_class chud_algo_sum( (chud_algo_m * chud_algo_l) / chud_algo_x );

  size_t chud_algo_precision = 0;

  mpz_class k( 1 );

  while( chud_algo_precision < demanded_precision ) {
    std::cout << "\rReached precision " << chud_algo_precision;

    chud_algo_l += chud_algo_l_aux;

    chud_algo_x *= chud_algo_x_aux;

    chud_algo_m *= (chud_algo_k * chud_algo_k - 16) * chud_algo_k;
    chud_algo_m /= k*k*k;

    chud_algo_k += 12;

    chud_algo_sum += (chud_algo_m * chud_algo_l) / chud_algo_x;

    chud_algo_precision += 14;

    ++k;
  }

  std::cout << std::endl;

  mpf_class chud_algo_c_aux( 10005 );
  mpf_class chud_algo_c( sqrt( chud_algo_c_aux ) * 426880 );

  mpf_class chud_algo_pi( chud_algo_c / chud_algo_sum );

  std::cout << "Finished computing pi at the demanded precision" << std::endl;

  std::cout << "Writing pi into the output file" << std::endl;

  output_file.precision(demanded_precision);
  output_file << chud_algo_pi;
  output_file.close();

  std::cout << "Finished writing pi into the output file" << std::endl;

  return 0;
}

