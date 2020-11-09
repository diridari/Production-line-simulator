# HiL_Taktstrasse

HiL welches die Taktstrasse der Veranstaltung "Embedded Systems" simulieren kann.

clone: git clone --recurse-submodules https://github.com/intel/Dependency-Reduction-Unit-Framework.git 

## Compile Error
#### Reason
* Submodules not present
### Appearance

    find: ‘../../lib/SimpleLogging/src’: No such file or directory
    find: ‘../../lib/CPP-Argument-Parser/src’: No such file or directory
#### Solution
This error results by not initialized submodules. To update those sub modules call:

    git submodule init
    git submodule update
