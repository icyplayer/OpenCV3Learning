/*
 * args_main.cpp
 *
 *  Created on: 2017年2月27日
 *      Author: icyplayer
 */
#include <iostream>
//#include <stdio.h>

using namespace std;


int main(int argc, const char** argv) {
	cout <<argc <<endl;
	cout <<argv[0] << endl;

	for(int i = 0; i < argc; i++){
		cout <<"argv[" <<i <<"]=" <<argv[i];
		cout <<endl;

	}
	return EXIT_SUCCESS;
}
