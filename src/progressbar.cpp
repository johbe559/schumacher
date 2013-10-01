#include "progressbar.h"
#include <iostream>

ProgressBar *ProgressBar::_instance;

void ProgressBar::printProgBar(int count, int total) {
	int percent = int(100.0f * float(count) / float(total)); 
	if (getInstance()->currProc == percent) return;
	else getInstance()->currProc = percent;
	std::string bar;

	for (int i = 0; i < 50; ++i) {
		if (i < (percent / 2)) {
			bar.replace(i, 1, "=");
		}
		else if( i == (percent / 2)) {
			bar.replace(i, 1, ">");
		}
		else {
			bar.replace(i, 1, " ");
		}
	}
	std::cout << "\r" "[" << bar << "] ";
	std::cout.width(3);
	std::cout << percent;
	if (total > 0)
		std::cout << "% (" << count << "/" << total << ")";
	std::cout << std::flush;
}