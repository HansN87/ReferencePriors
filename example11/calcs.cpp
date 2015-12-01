namespace calcs {
	
	long double integrate_likelihood(int steps, double theta, pdf &this_pdf) {
		// this is a brute force 1D integration
		// TODO: wrap around GSL
	
		// range of integration: theta in (0,1)
		double up = 1.0;
		double low = 0.0;
				
		long double dx = 1./steps * (up - low);
		long double val = 0.0;
		for(int i=0; i<steps-1; i++)
			val += dx * 0.5*(this_pdf.get_likelihood(low + i*dx) + this_pdf.get_likelihood(low + (i+1)*dx));
		return val;
	}

	long double refprior(pdf &this_pdf, double theta) {

		int m = 500; // number of samples to be generated to get average log posterior	
		long double r = 0;
		for (int i=0; i<m; i++) {
			this_pdf.generate_sample(1000, theta); // sample size = 100
			long double norm = integrate_likelihood(500, theta, this_pdf);
			
			if(isinf(log(norm))) {
				std::cout << "norm divergent!" << std::endl;
				break;	
			}

			r += this_pdf.get_loglikelihood(theta) - log(norm);
		}	
		return exp(r/m);	
	}
	
}
