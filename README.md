<img align="right" width="164" height="164" src="https://i.ibb.co/yFXthX8/Logo.jpg">

#    RL-Bin

### Robust Low-overhead Binary Rewriter

<br/><br/>

RL-Bin differentiates itself from other binary rewriters by
having the capability to robustly rewrite stripped binaries with very low overhead. The overhead added
by RL-Bin itself is negligible (a few percent) and it is proportional to the added instrumentation; hence lightweight instrumentation can be added to applications that are deployed in live systems for monitoring and analysis purposes.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

First, you need to clone the repository to your system.

```
git clone https://github.com/RL-Bin/RLBin.git
```

Then you need to install the prerequisites on your system.

### Prerequisites

#### Visual Studio 2019
For Building RL-Bin, you need to have Visual Studio 2019 installed on your machine. It can be downloaded from microsoft [website](https://visualstudio.microsoft.com/downloads/). If you install it in any path other than the default location, modify `make.bat` accordingly.

#### Python
You need Python 2 to run some of the scripts. Make sure `python` is in your system's path. For Windows, install package is available at
Python [website](http://www.python.org/getit/).

#### Graphviz
In order to generate graphs, you will also need to have [Graphviz](http://www.graphviz.org/) installed. CFGs and callgraph will use `dot` program that comes with graphviz, so make sure it is in your system's path.

### Building
Change your directory to the root of cloned repository and run `make.bat` batch file.

```
./make.bat
```

Also, for removing the binary files for a clean build, you can run `clean.bat` command.
```
./clean.bat
```

No installation is needed for RL-Bin. The software is portable and it can be executed from every path in the system provided that the `bin` folder containing files `inject.dll` and `core.dll`, is in the same path.


## Testing

Separate Tests are written for sample unit testing, and testing with SPEC CPU2017 benchamarks. 

#### Sample Tests

There are three categories of sample hand-written code to do unit testing. They are written in Assembly language, and C++. C++ Applications are either compiled by Visual Studio or GCC. Here is how to run these unit tests. 

```
./scripts/test _a_[0-5].bat
./scripts/test _v_[0-3].bat
./scripts/test _g_[0-4].bat
```

#### SPEC CPU2017 Benchmarks

SPEC Benchmark integer or floating point can be executed with the following command.

```
./scripts/test_spec_int.bat
./scripts/test_spec_fp.bat
```

## Deployment

Add additional notes about how to deploy this on a live system.

To run RL-Bin on any given program, it should be given as a command line parameter to RL-Bin. If the target application needs any input parameter, they need to be given after the name of the target application.

```
./RL-Bin.exe path/to/target/program.exe arg1 arg2 ...
```
Another method to run RL-Bin is to drag and drop the target application over `RL-Bin.exe` binary.

The outputs will be in `analysis` folder created by RL-Bin and will be numbered and put in separate folder for each run.

### Congifuration File

RL-Bin can be customized by reading from the configuration file found at [`./config/config.txt`](./config/config.txt). If the file is not present, default values will be used. In the configurateion file, you can customize the followings:

* Operation Mode (Static or Dynamic)

* Optimization Level

* Turning on/off Features and Log Files

## Documentation

RL-Bin source code is fully documented and the documentation is generated by [Doxygen](http://www.doxygen.nl/) and it can be found in [`./documentaion/html/index.htm`](./documentation/html/index.html).

## Built With

<img align="right" width="100" height="100" src="http://www.capstone-engine.org/img/capstone.png">

* [Capstone](http://www.capstone-engine.org/) - Lightweight disassembly framework.

* [PE-Parse Library](https://github.com/trailofbits/pe-parse) - principled, lightweight parser for windows portable executable files

* [Doxygen](http://www.doxygen.nl/) - Doxygen is the standard tool for generating documentation from C++ sources.

<img align="right" height="40" src="http://www.doxygen.nl/manual/images/doxygen.png">

<br/><br/>


## Contribution
Please follow the coding convention in [`Coding Convention`](./scripts/CodingConvention.md) to add code to the repo.


## Authors

* **Amir Majlesi Kupaei** - [LinkedIn](https://www.linkedin.com/in/amir-majlesi-kupaei/) - [Email]([mailto:amir.majlesi.kupaei@gmail.com)
* **Danny Kim** - [LinkedIn](https://www.linkedin.com/in/dannykim32)
* **Rajeev Barua** - [LinkedIn](https://www.linkedin.com/in/rajeev-barua)


## License

This project is licensed under the The BSD 3-Clause License - see the [LICENSE](LICENSE) file for details


## Publications

* Majlesi-Kupaei, Amir, Danny Kim, and Rajeev Barua. “RL-BIN++: Overcoming Binary Instrumentation Challenges in Presence of Obfuscation Techniques and Problematic Features.” Proceedings of the 2021 10th International Conference on Software and Computer Applications. 2021. 

* Majlesi-Kupaei, Amir, Danny Kim, Kapil Anand, Khaled ElWazeer, Aparna Kotha, and Rajeev Barua. “A Platform For Robust Low-Overhead Binary Instrumentation.” ICSEA 2019. (**Best Paper Award**)

* Majlesi-Kupaei, Amir, Danny Kim, Kapil Anand, Khaled ElWazeer, and Rajeev Barua. "RL-Bin, robust low-overhead binary rewriter." In Proceedings of the 2017 Workshop on Forming an Ecosystem Around Software Transformation, pp. 17-22. ACM, 2017.


## Acknowledgments

* Thanks to Kapil Anand, Khaled Elwazeer, and Aparna Kotha. RL-Bin is partially based on RapidWrite developed by the previous team in University of Maryland, College Park. 
* This research is partially supported by ONR grant N00014-18-1-2772. 

