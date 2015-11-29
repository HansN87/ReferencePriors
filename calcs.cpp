namespace calcs {
	
	double integrate_likelihood(int steps, pdf &this_pdf) {
		// this is a brute force 1D integration
		// need to find range of integration first
		double up = 4.0;
		double low = 2.0;

		double dx = 1./steps * (up - low);
		double val = 0.0;
		for(int i=0; i<steps-1; i++)
			val += dx * 0.5*(this_pdf.get_likelihood(low + i*dx) + this_pdf.get_likelihood(low + (i+1)*dx));
		return val;
	}

	double refprior(pdf &this_pdf, double theta) {

		// need to set parameter value before generating a sample
		this_pdf.set_parameter(theta);
		this_pdf.generate_sample(10);

		std::cout << integrate_likelihood(10000, this_pdf) << std::endl;
		return 0.;
	}
	
}
