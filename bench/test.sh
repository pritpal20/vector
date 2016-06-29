#! /bin/sh

if [ -z $1 ]; then
	echo "* Please select a bench to test!"
	exit
elif [ ! -e $1.cpp ]; then
	echo "* Bench doesn't exist!"
	exit
fi

printf "* Building ..."
make -s std_$1
make -s lni_$1
echo "Done"
echo ""

echo "* lni::vector"
./lni_$1
echo ""

echo "* std::vector"
./std_$1

