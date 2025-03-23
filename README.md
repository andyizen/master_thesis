# Master Thesis
This serves as the main container for the code base of the thesis. There are three different modules to this repository:

```
 
/cpp_filter
    # Holds the C++ implementation of the filter
    ...
/filterbook
    # Holds python code for printing filter curves and spectrums 
    ...
/hls_components
    # Holds the HLS components
    ...

```


## Checkout Submodules
Initializing the submodules
``` bash
git submodule update --init --recursive
```

To pull the submodules 
``` bash
git submodule update --remote
```