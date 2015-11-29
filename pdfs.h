#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random.hpp>
#include <boost/random/uniform_real.hpp>

#include <stdlib.h>
#include <stdio.h>

// wrapper around pdf + sampler
class pdf {
	public:		
		pdf(double low, double high); 
		bool init;	
		double x_low; // lower bound of sample space
		double x_high; // upper bound of sample space
		double par_value; // parameter value (theta)
		double par_high; // parameter space bounds
		double par_low; // parameter space bounds

		std::vector<double> sample;
		void generate_sample(int size);
		void set_parameter(double val);
		double get_pdf(double x); // acts on sample space
		double get_likelihood(double theta); // acts on parameter space
};

		
