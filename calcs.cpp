namespace calcs {
	
	double integrate_likelihood(int steps, double theta, pdf &this_pdf) {
		// this is a brute force 1D integration
		double up = this_pdf.par_high;
		double low = this_pdf.par_low;
		//std::cout << "low/up" << low << " " << up << std::endl;

		// estimate "width" of likelihood from 2nd derivative of log-llh
		// define range of integration from -5 to +5 std-deviations (or bounds or parameter space)
		double h=1.e-6;
		double d2logl = this_pdf.get_loglikelihood(theta+h) - 2. * this_pdf.get_loglikelihood(theta) + this_pdf.get_loglikelihood(theta-h);
		d2logl/=h*h;
		double stddev = sqrt(1./d2logl);	

		// catch cases where stddev evaluates to 0
		if(!stddev)
			stddev = 5.;

		//std::cout << "std: " << stddev << std::endl;
		if(theta + 5*stddev < up)
			up = theta + 5*stddev;
		if(theta - 5*stddev > low)
			low = theta - 5*stddev;
		
		//std::cout << "low/up" << low << " " << up << std::endl;
		double dx = 1./steps * (up - low);
		double val = 0.0;
		for(int i=0; i<steps-1; i++)
			val += dx * 0.5*(this_pdf.get_likelihood(low + i*dx) + this_pdf.get_likelihood(low + (i+1)*dx));
		return val;
	}

	double refprior(pdf &this_pdf, double theta) {

		int m = 100; // number of samples to be used to get average log posterior	
		double r = 0;
		for (int i=0; i<m; i++) {
			this_pdf.generate_sample(100, theta);
			double norm = integrate_likelihood(10000, theta, this_pdf);
			//std::cout << "norm:" << norm << std::endl;
			//std::cout << "pdf:" << this_pdf.get_loglikelihood(theta) << std::endl;
			r += this_pdf.get_loglikelihood(theta) - log(norm);
		}
		//std::cout << r << std::endl;
		//std::cout << r/m << std::endl;
		return exp(r/m);	
	}
	
}
