namespace calcs {
	
	long double integrate_likelihood(int steps, double theta, pdf &this_pdf) {
		// this is a brute force 1D integration
		// TODO: wrap around GSL
	
		/*
		// estimate "width" of likelihood from 2nd derivative of log-llh
		// define range of integration from -5 to +5 std-deviations (or bounds or parameter space)
		long double h=1.e-7;
		long double d2logl = this_pdf.get_loglikelihood(theta+h) - 2. * this_pdf.get_loglikelihood(theta) + this_pdf.get_loglikelihood(theta-h);
		d2logl/=h*h;
		long double stddev = sqrt(1./d2logl);	

		// catch cases where stddev evaluates to 0
		if(theta + 5*stddev < up)
			up = theta + 5*stddev;
		if(theta - 5*stddev > low)
			low = theta - 5*stddev;
		*/

		// range of integration: theta = sqrt(xN) to theta = x1
		double up = this_pdf.par_high;
		double low = this_pdf.par_low;
		for(int i=0;i<this_pdf.sample.size();i++) {
			if(this_pdf.sample.at(i) < up)
				up = this_pdf.sample.at(i);
			if(this_pdf.sample.at(i) > low)
				low = this_pdf.sample.at(i);
		}

		low = sqrt(low);
			
		long double dx = 1./steps * (up - low);
		long double val = 0.0;
		for(int i=0; i<steps-1; i++)
			val += dx * 0.5*(this_pdf.get_likelihood(low + i*dx) + this_pdf.get_likelihood(low + (i+1)*dx));
		return val;
	}

	long double refprior(pdf &this_pdf, double theta) {

		int m = 200; // number of samples to be generated to get average log posterior	
		long double r = 0;
		for (int i=0; i<m; i++) {
			this_pdf.generate_sample(100, theta); // sample size = 100
			long double norm = integrate_likelihood(10000, theta, this_pdf);
			
			if(isinf(log(norm))) {
				std::cout << "norm divergent!" << std::endl;
				break;	
			}

			r += this_pdf.get_loglikelihood(theta) - log(norm);
		}	
		return exp(r/m);	
	}
	
}
