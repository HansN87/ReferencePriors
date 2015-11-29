#include "pdfs.h"

// pdf for unif(theta, theta^2)

pdf::pdf(double low, double high) {
	init = false;
	par_high = high;
	par_low = low;
}

void pdf::set_parameter(double val) {
	init = true;
	par_value = val;
	x_low = val;
	x_high = val * val;
}

double pdf::get_pdf(double x) {
	// depends on theta through support
	if(x <= x_high && x >= x_low)
		return 1./(x_high-x_low);
	else 
		return 0.;
}

double pdf::get_likelihood(double theta) {
	std::cout << "curr: " << theta << std::endl;
	set_parameter(theta);
       	double llh = 1.0;
       	for(int i=0; i<sample.size(); i++) {
		std::cout << " ** " << sample.at(i) << " " << get_pdf(sample.at(i)) << std::endl;
		llh*=get_pdf(sample.at(i));
	}
	return llh;
}

void pdf::generate_sample(int size) {
	static unsigned int calls = 0; // use as seed for generator
	calls++; // ensures unique seed in every call

	if(!init) {
		std::cout << "*** please initialize parameters first!";
		exit(1);
	}

	sample.clear();
	boost::uniform_real<> unif(x_low, x_high);
	boost::random::mt19937 gen(calls);
	boost::variate_generator< boost::random::mt19937&, boost::uniform_real<> > sampler(gen, unif);
	for(int i=0;i<size;i++)
		sample.push_back(sampler());
}
