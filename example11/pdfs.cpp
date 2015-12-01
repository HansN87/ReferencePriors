#include "pdfs.h"

// pdf for unif(theta, theta^2)

pdf::pdf(long double low, long double high) {
	par_high = high;
	par_low = low;
}

long double pdf::get_pdf(long double x, long double theta) {
	long double x_low = 0.;
	long double x_high = 1.;
	if(x < x_high && x > x_low) {
		// triangle pdf is defined piecewise
		if(x<=theta) 
			return 2.*x/theta;
		else
			return 2.*(1.-x)/(1-theta);
	}		
	else 	
		return 0.;	
}

long double pdf::get_likelihood(long double theta) {
	// returns the value of the likelihood function for a given theta
	// assumes that a sample has already been generated
       	long double llh = 1.0;
       	for(int i=0; i<sample.size(); i++) 	
		llh*=get_pdf(sample.at(i), theta);	
	return llh;
}

long double pdf::get_loglikelihood(long double theta) {
	// returns the logarithm of the likelihood function
        // assumes that a sample has already been generated 
        long double logllh = 0.0;
        for(int i=0; i<sample.size(); i++) { 
		long double val = get_pdf(sample.at(i), theta);
                logllh+=log(val);
        }
        return logllh;
}

void pdf::generate_sample(int size, long double theta) {
	static unsigned int calls = 0; // use as seed for generator
	calls++; // ensures unique seed in every call
	sample.clear();
	boost::triangle_distribution<> triangle(0., theta, 1.);
	boost::random::mt19937 gen(calls);
	boost::variate_generator< boost::random::mt19937&, boost::triangle_distribution<> > sampler(gen, triangle);
	for(int i=0;i<size;i++) {
		sample.push_back(sampler());

	}

}

