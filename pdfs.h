#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random.hpp>
#include <boost/random/uniform_real.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// wrapper around pdf + sampler
class pdf {
	public:		
		pdf(double low, double high); 
		double x_low; // lower bound of sample space
		double x_high; // upper bound of sample space
		double par_value; // parameter value (theta)
		double par_high; // parameter space bounds
		double par_low; // parameter space bounds

		std::vector<double> sample;
		void generate_sample(int size, double theta);
		void set_parameter(double val);
		double get_pdf(double x, double theta);
		double get_likelihood(double theta);
		double get_loglikelihood(double theta);
};

		
