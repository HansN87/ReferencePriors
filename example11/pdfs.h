#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random.hpp>
#include <boost/random/triangle_distribution.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// wrapper around pdf + sampler
class pdf {
	public:		
		pdf(long double low, long double high); 
		long double x_low; // lower bound of sample space
		long double x_high; // upper bound of sample space
		long double par_value; // parameter value (theta)
		long double par_high; // parameter space bounds
		long double par_low; // parameter space bounds

		std::vector<long double> sample;
		void generate_sample(int size, long double theta);
		void set_parameter(long double val);
		long double get_pdf(long double x, long double theta);
		long double get_likelihood(long double theta);
		long double get_loglikelihood(long double theta);
};

		
