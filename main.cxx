#include "pdfs.cpp"
#include "calcs.cpp"

int main(void) {

	// this is the unif(theta, theta^2) model
	pdf uniform(0.0, 1e10);
	double theta = 2.;
	double refprior = calcs::refprior(uniform, theta);
	std::cout << refprior << std::endl;
}
