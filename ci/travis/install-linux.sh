sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

sudo apt-get install -qq g++-7
sudo apt-get install -qq gcc-7

sudo apt install valgrind
sudo apt install cppcheck
pip install --user cpp-coveralls
