# Binmulator
## A Native Binary Emulator Library and Utility

Most emulators for malware detection are written in Python and fail when certain emulated API functions do not exist. It is fun to emulate Windows binaries on Linux but is it practical?. The goal of `binmulator` is to provide an open-source emulator framework to emulate near-native execution by leveraging the operating system it runs on. This means it can be used to perform advanced behavioral detection and protection with less time invested in development.

# Installing

```bash
git clone --recursive https://github.com/c3rb3ru5d3d53c/binmulator.git
cd binmulator/
# Install Unicorn Emulator
make unicorn threads=4
sudo make unicorn-install
# Install Utility
make threads=4
sudo make install
```

**This is still a WIP, just an idea atm***
