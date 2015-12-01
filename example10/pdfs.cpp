#include "pdfs.h"

// pdf for unif(theta, theta^2)

pdf::pdf(long double low, long double high) {
	par_high = high;
	par_low = low;
}

long double pdf::get_pdf(long double x, long double theta) {
	long double x_low = theta;
	long double x_high = theta*theta;
	if(x <= x_high && x >= x_low)
		return 1./(x_high-x_low);
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
	boost::uniform_real<> unif(theta, theta * theta);
	boost::random::mt19937 gen(calls);
	boost::variate_generator< boost::random::mt19937&, boost::uniform_real<> > sampler(gen, unif);
	for(int i=0;i<size;i++) {
		sample.push_back(sampler());

	}

}

