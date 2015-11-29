#include "pdfs.h"

// pdf for unif(theta, theta^2)

pdf::pdf(double low, double high) {
	par_high = high;
	par_low = low;
}

double pdf::get_pdf(double x, double theta) {
	double x_low = theta;
	double x_high = theta*theta;
	if(x <= x_high && x >= x_low)
		return 1./(x_high-x_low);
	else {
		//std::cout << x << " " << theta << std::endl;
		return 0.;
	}
}

double pdf::get_likelihood(double theta) {
	// returns the value of the likelihood function for a given theta
	// assumes that a sample has already been generated
	//std::cout << "curr: " << theta << std::endl;
       	double llh = 1.0;
       	for(int i=0; i<sample.size(); i++) {
		//std::cout << " ** " << sample.at(i) << " " << get_pdf(sample.at(i), theta) << std::endl;
		llh*=get_pdf(sample.at(i), theta);
	}
	return llh;
}

double pdf::get_loglikelihood(double theta) {
	// returns the logarithm of the likelihood function
        // assumes that a sample has already been generated 
        double logllh = 0.0;
        for(int i=0; i<sample.size(); i++) { 
		//std::cout << sample.at(i) << " ";
		if(get_pdf(sample.at(i), theta)==0)
			std::cout << "WTF " << sample.at(i) << " " << theta << " ++++++++++++++++++++++++" <<std::endl;
		double val = get_pdf(sample.at(i), theta);
		//if(val)
                logllh+=log(val);
        }
	//std::cout << std::endl;
	//std::cout << logllh << std::endl;
        return logllh;
}

void pdf::generate_sample(int size, double theta) {
	static unsigned int calls = 0; // use as seed for generator
	calls++; // ensures unique seed in every call
	//std::cout << calls << std::endl;
	sample.clear();
	boost::uniform_real<> unif(theta, theta * theta);
	//calls = 24;
	boost::random::mt19937 gen(calls);
	boost::variate_generator< boost::random::mt19937&, boost::uniform_real<> > sampler(gen, unif);
	for(int i=0;i<size;i++) {
		sample.push_back(sampler());
		//std::cout << sample.at(i) << " ";
	}
	//std::cout << std::endl;
	
}
