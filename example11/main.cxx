#include "pdfs.cpp"
#include "calcs.cpp"

int main(void) {

	// this is the triangle pdf model
	pdf triangle(0.0, 1.0); // parameter space is open interval (0,1)

	for(int i=0;i<26;i++) {
		double theta = 0.01+i*0.0392;
		double refprior = calcs::refprior(triangle, theta);
		std::cout << theta << " " << refprior << std::endl;
	}

        double theta = 0.5;
        double refprior = calcs::refprior(triangle, theta);
        std::cout << theta << " " << refprior << std::endl;
}
