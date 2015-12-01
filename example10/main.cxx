#include "pdfs.cpp"
#include "calcs.cpp"

int main(void) {

	// this is the unif(theta, theta^2) model
	pdf uniform(0.0, 1e10);

	for(int i=1;i<26;i++) {
		double theta = 0.0+i*0.05;
		double refprior = calcs::refprior(uniform, pow(10,theta));
		std::cout << pow(10,theta) << " " << refprior << std::endl;
	}

        double theta = 2.0;
        double refprior = calcs::refprior(uniform, theta);
        std::cout << theta << " " << refprior << std::endl;
}
