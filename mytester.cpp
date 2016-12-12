#include <iostream>
#include "vector.hpp"
#include <stdlib.h>
#include <time.h>

using std::cout ;
using std::endl;

#define vector_type lni

int main(int argc,char* argv[])
{
	if(argc < 2 )
	{
		cout << "exiting ... " << endl ; exit(1);
	}
	srand(time(NULL));
	vector_type::vector<int> v1;

	cout << "##v1 -> capacity = " << v1.capacity() <<" ,size = " << v1.size() << endl;
	
	int N = atoi(argv[1]);
	for(auto i = 0 ; i < N ; i++ )
	{
		v1.push_back(rand()%100);
		//cout << "v1 -> capacity = " << v1.capacity() <<" ,size = " << v1.size() << endl;
	}
	
	//lni::Print(v1,"v1");
	
	vector_type::vector<int> v2(v1.begin(),v1.end());
	
	cout << "##v2 -> capacity = " << v1.capacity() <<" ,size = " << v1.size() << endl;
	//lni::Print(v2,"v2");
	
	puts("Testing vector<T>::vector(std::initializer_list<T> ...");
	vector_type::vector<int> v3 = {1,2,3,4,5,6,7};
	lni::Print(v3,"v3");
	puts("Testing vector<T>::operator =(std::initializer_list<T> ...");
	v3 = {6,7,8,9};
	lni::Print(v3,"v3");
	
	vector_type::vector<int> v4(5,1.0);
	lni::Print(v4,"v4");
	v4.assign(v3.begin(),v3.end());
	lni::Print(v4,"v4");
	
	v4.assign(10,5);
	lni::Print(v4,"v4");
	
	
	
	
	
	return 0;
}